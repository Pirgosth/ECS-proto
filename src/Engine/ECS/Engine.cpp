#include "Engine.hpp"

EntityId Engine::g_EntitiesCount = 0;

void Engine::update()
{
    for (auto system: m_systems)
    {
        system->notifyUpdate();
    }
}

void Engine::registerSystem(BaseSystem *system)
{
    m_systems.push_back(std::shared_ptr<BaseSystem>(system));
}

EntityId Engine::makeEntity()
{
    EntityId id = g_EntitiesCount++;

    if (m_entitiesSignatures.count(id) == 0)
    {
        m_entitiesSignatures.emplace(id, ArchetypeSignature());
    }

    auto signature = m_entitiesSignatures.at(id);

    m_archetypeGraph.createEntity(id, signature);

    return id;
}
