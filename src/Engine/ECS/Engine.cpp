#include "Engine.hpp"

EntityId Engine::g_EntitiesCount = 0;

Engine::Engine() : m_isRunning(false) {}

void Engine::start()
{
    m_isRunning = true;
    m_updateThread = std::thread(&Engine::update, this);
}

void Engine::update()
{
    static sf::Clock m_deltaTimeClock;
    while(m_isRunning)
    {
        const float deltaTime = m_deltaTimeClock.restart().asMicroseconds() / 1000000.0f;
        for (auto system : m_systems)
        {
            system->notifyUpdate(deltaTime);
        }
    }
}

void Engine::stop()
{
    m_isRunning = false;
    m_updateThread.join();
}

bool Engine::isRunning()
{
    return m_isRunning;
}

void Engine::draw(sf::RenderWindow &window)
{
    for (auto system : m_systems)
    {
        system->notifyDraw(window);
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
