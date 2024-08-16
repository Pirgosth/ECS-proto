#ifndef ECS_H_INCLUDED
#define ECS_H_INCLUDED

#include "ArchetypeGraph.hpp"
#include "System.hpp"

#include <memory>

class ECS
{
private:
    EntityId m_entityCounter;
    ArchetypeGraph m_archetypeGraph;
    std::set<std::shared_ptr<BaseSystem>> m_systems;

public:
    ECS();
    template <typename... Components>
    EntityId createEntity(Components... components);
    template <typename Component>
    Component &getComponent(EntityId id);
    template <typename Component>
    void deleteComponent(EntityId id);
    void deleteEntity(EntityId id);
    void registerSystem(BaseSystem *system);
    void update();
};

template <typename... Components>
inline EntityId ECS::createEntity(Components... components)
{
    auto entityId = m_entityCounter++;
    m_archetypeGraph.addEntity(entityId, components...);
    return entityId;
}

template <typename Component>
inline Component &ECS::getComponent(EntityId id)
{
    return m_archetypeGraph.getComponent<Component>(id);
}

template <typename Component>
inline void ECS::deleteComponent(EntityId id)
{
    m_archetypeGraph.deleteComponent<Component>(id);
}

#endif // ECS_H_INCLUDED
