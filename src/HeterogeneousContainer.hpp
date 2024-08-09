#ifndef HETEROGENEOUSCONTAINER_H_INCLUDED
#define HETEROGENEOUSCONTAINER_H_INCLUDED

#include "TypeId.hpp"

#include <cassert>
#include <memory>
#include <unordered_map>
#include <vector>

template <typename T>
class Container;

class BaseContainer
{
public:
    virtual ~BaseContainer() {};
    template <typename T>
    std::vector<T> &get();
    virtual void copy(const BaseContainer &from, int index) = 0;
    virtual BaseContainer *clone() const = 0;
    virtual int size() const = 0;
};

template <typename T>
inline std::vector<T> &BaseContainer::get()
{
    return dynamic_cast<Container<T> &>(*this).get();
}

template <typename T>
class Container : public BaseContainer
{
private:
    std::vector<T> m_container;

public:
    std::vector<T> &get();
    virtual BaseContainer *clone() const override;
    virtual void copy(const BaseContainer &from, int index) override;
    virtual int size() const override;
};

template <typename T>
inline std::vector<T> &Container<T>::get()
{
    return m_container;
}

template <typename T>
inline BaseContainer *Container<T>::clone() const
{
    return new Container<T>();
}

template <typename T>
inline void Container<T>::copy(const BaseContainer &from, int index)
{
    const Container<T> &castedFrom = dynamic_cast<const Container<T> &>(from);
    T value = castedFrom.m_container.at(index);
    m_container.push_back(value);
}

template <typename T>
inline int Container<T>::size() const
{
    return m_container.size();
}

class HeterogeneousContainer
{
private:
    std::unordered_map<TypeId, std::shared_ptr<BaseContainer>> m_containers;

public:
    HeterogeneousContainer() = default;
    HeterogeneousContainer(const HeterogeneousContainer &x);
    HeterogeneousContainer clone() const;
    template <typename... Components>
    class HeterogeneousContainerView
    {
        HeterogeneousContainer &parent;

    public:
        class iterator : public std::iterator<
                             std::input_iterator_tag,    // iterator_category
                             std::tuple<Components &...> // value_type
                             >
        {
        private:
            std::tuple<std::shared_ptr<typename std::vector<Components>::iterator>...> current;

            template <typename T>
            void incrementContainerIterator(std::shared_ptr<typename std::vector<T>::iterator> &iterator)
            {
                ++(*iterator);
            }

            void incrementContainerIterators(std::shared_ptr<typename std::vector<Components>::iterator> &...containerIterators)
            {
                (incrementContainerIterator<Components>(containerIterators), ...);
            }

            template <typename T>
            T &retrieveValue(std::shared_ptr<typename std::vector<T>::iterator> &iterator)
            {
                return *(*iterator);
            }

            std::tuple<Components &...> retrieveValues()
            {
                return std::forward_as_tuple(retrieveValue<Components>(std::get<std::shared_ptr<typename std::vector<Components>::iterator>>(current))...);
            }

        public:
            explicit iterator(std::tuple<std::shared_ptr<typename std::vector<Components>::iterator>...> _current) : current(_current) {}
            iterator &operator++()
            {
                incrementContainerIterators(std::get<std::shared_ptr<typename std::vector<Components>::iterator>>(current)...);
                return *this;
            }
            iterator operator++(int)
            {
                iterator retval = *this;
                ++(*this);
                return retval;
            }
            bool operator==(iterator &other) const { return *(std::get<0>(current)) == *(std::get<0>(other.current)); }
            bool operator!=(iterator &other) const { return !(*this == other); }
            std::tuple<Components &...> operator*() { return retrieveValues(); }
        };

    private:
        template <typename T>
        std::shared_ptr<typename std::vector<T>::iterator> _begin()
        {
            auto beg = parent.template get<T>().begin();
            return std::make_shared<typename std::vector<T>::iterator>(beg);
        }

        std::tuple<std::shared_ptr<typename std::vector<Components>::iterator>...> _begin()
        {
            auto tuple = std::make_tuple(_begin<Components>()...);
            return tuple;
        }

        template <typename T>
        std::shared_ptr<typename std::vector<T>::iterator> _end()
        {
            auto end = parent.template get<T>().end();
            return std::make_shared<typename std::vector<T>::iterator>(end);
        }

        std::tuple<std::shared_ptr<typename std::vector<Components>::iterator>...> _end()
        {
            return std::make_tuple(_end<Components>()...);
        }

    public:
        HeterogeneousContainerView(HeterogeneousContainer &parent) : parent(parent) {};
        iterator begin() { return iterator(_begin()); }
        iterator end() { return iterator(_end()); }
    };

    template <typename T>
    void addContainer();

    template <typename T>
    void removeContainer();

    template <typename T>
    std::vector<T> &get();

    template <typename... Types>
    HeterogeneousContainerView<Types...> getView();

    void copy(const HeterogeneousContainer &from, int index);
    unsigned int size() const;
    ArchetypeSignature computeSignature();
};

template <typename T>
inline void HeterogeneousContainer::addContainer()
{
    auto id = Type::getId<T>();

    if (this->m_containers.count(id) != 0)
        return;

    m_containers.emplace(id, std::make_shared<Container<T>>());
}

template <typename T>
inline std::vector<T> &HeterogeneousContainer::get()
{
    auto id = Type::getId<T>();

    assert(m_containers.count(id) != 0);
    return m_containers.at(id)->template get<T>();
}

template <typename T>
inline void HeterogeneousContainer::removeContainer()
{
    auto id = Type::getId<T>();

    assert(m_containers.count(id) != 0 && "No container with provided type!");

    m_containers.erase(id);
}

template <typename... Types>
inline HeterogeneousContainer::HeterogeneousContainerView<Types...> HeterogeneousContainer::getView()
{
    return HeterogeneousContainerView<Types...>(*this);
}

#endif // HETEROGENEOUSCONTAINER_H_INCLUDED
