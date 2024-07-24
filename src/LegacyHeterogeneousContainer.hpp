#ifndef HETEROGENEOUS_H_INCLUDED
#define HETEROGENEOUS_H_INCLUDED

#include <memory>
#include <vector>

template <typename... Types>
class HeterogeneousContainer : public HeterogeneousContainer<Types>...
{
public:
    template <typename... Components>
    class HeterogeneousContainerView
    {
        HeterogeneousContainer &parent;
        class iterator : public std::iterator<
                             std::input_iterator_tag, // iterator_category
                             std::tuple<Components...>  // value_type
                             >
        {
        private:
            std::tuple<std::shared_ptr<typename std::vector<Components>::iterator>...> current;

            template <typename T>
            void incrementContainerIterator(std::shared_ptr<typename std::vector<T>::iterator> &iterator)
            {
                ++(*iterator);
            }

            void incrementContainerIterators(std::shared_ptr<typename std::vector<Components>::iterator>... containerIterators)
            {
                (incrementContainerIterator<Components>(containerIterators), ...);
            }

            template <typename T>
            T retrieveValue(std::shared_ptr<typename std::vector<T>::iterator> iterator)
            {
                return *(*iterator);
            }

            std::tuple<Components...> retrieveValues()
            {
                return std::make_tuple(retrieveValue<Components>(std::get<std::shared_ptr<typename std::vector<Components>::iterator>>(current))...);
            }

            template <typename First, typename... Tail>
            bool equals(iterator other) const
            {
                return *(std::get<0>(current)) == *(std::get<0>(other.current));
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
            bool operator==(iterator other) const { return equals<Components...>(other); }
            bool operator!=(iterator other) const { return !(*this == other); }
            std::tuple<Components...> operator*() { return retrieveValues(); }
        };

    private:
        template <typename T>
        std::shared_ptr<typename std::vector<T>::iterator> _begin()
        {
            auto beg = parent.HeterogeneousContainer<T>::get().begin();
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
            auto end = parent.HeterogeneousContainer<T>::get().end();
            return std::make_shared<typename std::vector<T>::iterator>(end);
        }

        std::tuple<std::shared_ptr<typename std::vector<Components>::iterator>...> _end()
        {
            return std::make_tuple(_end<Components>()...);
        }

    public:
        HeterogeneousContainerView(HeterogeneousContainer &parent) : parent(parent){};
        iterator begin() { return iterator(_begin()); }
        iterator end() { return iterator(_end()); }
    };

private:
public:
    template <typename Type>
    std::vector<Type> &get();

    template <typename First, typename Second, typename... Components>
    HeterogeneousContainerView<First, Second, Components...> get();
};

template <typename... Types>
template <typename Type>
inline std::vector<Type> &HeterogeneousContainer<Types...>::get()
{
    return HeterogeneousContainer<Type>::get();
}

template <typename... Types>
template <typename First, typename Second, typename... Components>
inline HeterogeneousContainer<Types...>::HeterogeneousContainerView<First, Second, Components...> HeterogeneousContainer<Types...>::get()
{
    return HeterogeneousContainerView<First, Second, Components...>(*this);
}

template <typename Type>
class HeterogeneousContainer<Type>
{
protected:
    std::vector<Type> m_container;

public:
    std::vector<Type> &get();
};

template <typename Type>
inline std::vector<Type> &HeterogeneousContainer<Type>::get()
{
    return m_container;
}

#endif // HETEROGENEOUS_H_INCLUDED
