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
    unsigned int m_elementCount;
    std::vector<unsigned int> m_elements;

    unsigned int m_lastElementErased;
    unsigned int m_erasedCount;

    std::unordered_map<TypeId, std::shared_ptr<BaseContainer>> m_containers;

public:
    HeterogeneousContainer();
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
            HeterogeneousContainer *m_parent;
            unsigned int m_currentIndex;

        public:
            explicit iterator(HeterogeneousContainer *_parent, unsigned int currentIndex) : m_parent(_parent), m_currentIndex(currentIndex) {}
            
            iterator &operator++()
            {
                ++m_currentIndex;
                while (m_currentIndex < m_parent->m_elementCount && !m_parent->isAlive(m_currentIndex))
                {
                    ++m_currentIndex;
                    continue;
                }
                return *this;
            }
            iterator operator++(int)
            {
                iterator retval = *this;
                ++(*this);
                return retval;
            }
            bool operator==(iterator &other) const { return m_parent == other.m_parent && m_currentIndex == other.m_currentIndex; }
            bool operator!=(iterator &other) const { return !(*this == other); }
            std::tuple<Components &...> operator*() { return std::forward_as_tuple(m_parent->get<Components>()[m_currentIndex]...); }
        };

    public:
        HeterogeneousContainerView(HeterogeneousContainer &parent) : parent(parent) {};
        iterator begin() { return iterator(&parent, 0); }
        iterator end() { return iterator(&parent, parent.size()); }
    };

    template <typename T>
    void addContainer();

    template <typename T>
    void removeContainer();

    template <typename T>
    std::vector<T> &get();

    template <typename ...Types>
    unsigned int push_back(Types... values);

    unsigned int push_back(HeterogeneousContainer &from, unsigned int componentIndex);

    bool isAlive(unsigned int index);

    bool erase(unsigned int index);

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

template <typename... Types>
inline unsigned int HeterogeneousContainer::push_back(Types... values)
{
    auto insertedId = m_elementCount++;
    (get<Types>().push_back(values), ...);
    m_elements.push_back(insertedId);
    return insertedId;
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
