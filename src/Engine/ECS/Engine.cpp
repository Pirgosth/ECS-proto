#include "Engine.hpp"

EntityId Engine::g_EntitiesCount = 0;

void Engine::update()
{
    for (auto system: m_systems)
    {
        ArchetypeSignature signature = system->getSignature();
        system->notifyUpdate(m_archetypeGraph.getCompatibleArchetypes(signature));
    }
}

void Engine::registerSystem(BaseSystem *system)
{
    m_systems.push_back(std::shared_ptr<BaseSystem>(system));
}

EntityId Engine::makeEntity()
{
    EntityId id = g_EntitiesCount++;
    m_archetypeGraph.createEntity(id);
    return id;
}
