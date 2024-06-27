#ifndef ARCHETYPEGRAPH_H_INCLUDED
#define ARCHETYPEGRAPH_H_INCLUDED

#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Engine/ECS/Archetype/Archetype.hpp"
#include "Engine/ECS/Archetype/ArchetypeNode.hpp"
#include "Engine/ECS/ComponentManager.hpp"
#include "Engine/ECS/Types.hpp"

class ArchetypeGraph
{
private:
    ArchetypeNode m_graph;
    std::unordered_map<ComponentId, std::unordered_set<ArchetypeNode *>> m_componentArchetypes;
    std::map<ComponentId, std::shared_ptr<Component>> addComponent(EntityId id, ComponentId componentId, Component *component, ArchetypeSignature &signature);

public:
    ArchetypeGraph();
    std::vector<Archetype *> getCompatibleArchetypes(ArchetypeSignature signature);
    void createEntity(EntityId id, ArchetypeSignature signature);
    template <typename T>
    std::map<ComponentId, std::shared_ptr<Component>> addComponent(EntityId id, T *component, ArchetypeSignature &signature);
};

template <typename T>
inline std::map<ComponentId, std::shared_ptr<Component>> ArchetypeGraph::addComponent(EntityId id, T *component, ArchetypeSignature &signature)
{
    return addComponent(id, ComponentManager::getId<T>(), component, signature);
}

#endif // ARCHETYPEGRAPH_H_INCLUDED
