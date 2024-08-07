#include "ECS.hpp"

EntityId ECS::g_entityCounter = 0;

void ECS::update()
{
    for (auto system : m_systems)
    {
        system->notifyUpdate(m_archetypeGraph);
    }
}

void ECS::registerSystem(BaseSystem *system)
{
    m_systems.emplace(std::shared_ptr<BaseSystem>(system));
}
