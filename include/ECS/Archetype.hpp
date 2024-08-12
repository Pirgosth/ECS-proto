#ifndef ARCHETYPE_H_INCLUDED
#define ARCHETYPE_H_INCLUDED

#include <memory>

#include "HeterogeneousContainer.hpp"
#include "Types.hpp"

class Archetype
{
private:
    HeterogeneousContainer m_components;
    Archetype() = default;

public:
    template <typename ...Components>
    static Archetype build(); 
    template <typename Component>
    std::vector<Component> &getComponents();
    template <typename ...Components>
    typename HeterogeneousContainer::HeterogeneousContainerView<Components...> getPartialEntities();
    template <typename Component>
    Archetype extend();
    template <typename Component>
    Archetype reduce();

    unsigned int transfertEntity(Archetype &target, unsigned int componentId);

    template <typename ...Components>
    unsigned int push_back(Components... components);
    bool erase(unsigned int componentIndex);
    ArchetypeSignature computeSignature();
};

template <typename... Components>
inline Archetype Archetype::build()
{
    Archetype builder;
    (builder.m_components.addContainer<Components>(), ...);

    return builder;
}

template <typename Component>
inline std::vector<Component> &Archetype::getComponents()
{
    return m_components.template get<Component>();
}

template <typename... Components>
inline typename HeterogeneousContainer::HeterogeneousContainerView<Components...> Archetype::getPartialEntities()
{
    return m_components.template getView<Components...>();
}

template <typename Component>
inline Archetype Archetype::extend()
{
    auto extended = Archetype();
    extended.m_components = m_components.clone();
    extended.m_components.addContainer<Component>();

    return extended;
}

template <typename Component>
inline Archetype Archetype::reduce()
{
    auto reduced = Archetype();
    reduced.m_components = m_components.clone();
    reduced.m_components.removeContainer<Component>();

    return reduced;
}

template <typename... Components>
inline unsigned int Archetype::push_back(Components... components)
{
    return m_components.push_back<Components...>(components...);
}

#endif // ARCHETYPE_H_INCLUDED
