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

}

void ECS::registerSystem(BaseSystem *system)
{
    m_systems.emplace(std::shared_ptr<BaseSystem>(system));
}
