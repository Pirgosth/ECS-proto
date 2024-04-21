#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include <memory>
#include <vector>

#include "Engine/ECS/ArchetypeGraph.hpp"
#include "Engine/ECS/Component.hpp"
#include "Engine/ECS/ComponentManager.hpp"
#include "Engine/ECS/System.hpp"

class Engine
{
private:
    static EntityId g_EntitiesCount;

    ArchetypeGraph m_archetypeGraph;
    std::vector<std::shared_ptr<BaseSystem>> m_systems;

public:
    void update();
    void registerSystem(BaseSystem *system);
    EntityId makeEntity();
    template <typename T>
    void addComponent(EntityId, T *component);
};

template <typename T>
inline void Engine::addComponent(EntityId id, T *component)
{
    m_archetypeGraph.addComponent(id, component);
}

#endif // ENGINE_H_INCLUDED
