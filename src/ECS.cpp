#include "ECS.hpp"

void ECS::update()
{
    for (auto system : m_systems)
    {
        system->notifyUpdate(m_archetypeGraph);
    }
}

ECS::ECS(): m_entityCounter(0) {}

void ECS::deleteEntity(EntityId id)
{
    m_archetypeGraph.deleteEntity(id);
}

void ECS::registerSystem(BaseSystem *system)
{
    m_systems.push_back(std::shared_ptr<BaseSystem>(system));
}
