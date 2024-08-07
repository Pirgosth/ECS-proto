#ifndef ECS_H_INCLUDED
#define ECS_H_INCLUDED

#include "ArchetypeGraph.hpp"
#include "System.hpp"

#include <memory>

class ECS
{
private:
    static EntityId g_entityCounter;
    ArchetypeGraph m_archetypeGraph;
    std::set<std::shared_ptr<BaseSystem>> m_systems;

public:
    template <typename... Components>
    EntityId createEntity(Components... components);
    void registerSystem(BaseSystem *system);
    void update();
};

template <typename... Components>
inline EntityId ECS::createEntity(Components... components)
{
    auto entityId = g_entityCounter++;
    m_archetypeGraph.addEntity(entityId, components...);
    return entityId;
}

#endif // ECS_H_INCLUDED
