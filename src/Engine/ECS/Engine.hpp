#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include <unordered_map>
#include <memory>
#include <thread>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Engine/ECS/Archetype/ArchetypeGraph.hpp"
#include "Engine/ECS/Component/Component.hpp"
#include "Engine/ECS/ComponentManager.hpp"
#include "Engine/ECS/System/BaseSystem.hpp"

class Engine
{
private:
    static EntityId g_EntitiesCount;

    bool m_isRunning;
    ArchetypeGraph m_archetypeGraph;
    std::unordered_map<EntityId, ArchetypeSignature> m_entitiesSignatures;
    std::vector<std::shared_ptr<BaseSystem>> m_systems;
    std::thread m_updateThread;

public:
    Engine();
    void start();
    void update();
    void stop();
    bool isRunning();
    void draw(sf::RenderWindow &window);
    void registerSystem(BaseSystem *system);
    EntityId makeEntity();
    template <typename T>
    void addComponent(EntityId id, T *component);
    template <typename T>
    std::shared_ptr<T> getComponent(EntityId id);
};

template <typename T>
inline void Engine::addComponent(EntityId id, T *component)
{
    // In this case, entity id is invalid or entity does not exist anymore.
    if (m_entitiesSignatures.count(id) == 0)
        return;

    auto &signature = m_entitiesSignatures.at(id);
    auto rawComponents = m_archetypeGraph.addComponent(id, component, signature);

    for (auto system : m_systems)
    {
        if (system->canHandle(signature))
        {
            system->updateEntity(id, rawComponents);
            system->notifyInit(id, rawComponents);
        }
    }
}

template <typename T>
inline std::shared_ptr<T> Engine::getComponent(EntityId id)
{
    return m_archetypeGraph.getComponent<T>(id);
}

#endif // ENGINE_H_INCLUDED
