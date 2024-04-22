#ifndef ARCHETYPEGRAPH_H_INCLUDED
#define ARCHETYPEGRAPH_H_INCLUDED

#include <map>
#include <vector>

#include "Engine/ECS/Archetype/Archetype.hpp"
#include "Engine/ECS/Archetype/ArchetypeNode.hpp"
#include "Engine/ECS/ComponentManager.hpp"
#include "Engine/ECS/Types.hpp"

class ArchetypeGraph
{
private:
    ArchetypeNode m_graph;
    std::map<EntityId, ArchetypeSignature> m_entitiesSignatures;
    void addComponent(EntityId id, ComponentId componentId, Component *component);

public:
    std::vector<Archetype *> getCompatibleArchetypes(ArchetypeSignature signature);
    void createEntity(EntityId id);
    template <typename T>
    void addComponent(EntityId id, T *component);
};

template <typename T>
inline void ArchetypeGraph::addComponent(EntityId id, T *component)
{
    addComponent(id, ComponentManager::getId<T>(), component);
}

#endif // ARCHETYPEGRAPH_H_INCLUDED
