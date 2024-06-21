#include "ArchetypeGraph.hpp"

std::vector<Archetype *> ArchetypeGraph::getCompatibleArchetypes(ArchetypeSignature signature)
{
    return m_graph.getAllCompatibleArchetypes(signature);
}

void ArchetypeGraph::createEntity(EntityId id, ArchetypeSignature signature)
{
    Archetype &archetype = m_graph.getOrCreateArchetype(signature);
    archetype.addEntity(id, std::map<EntityId, std::shared_ptr<Component>>());
}

void ArchetypeGraph::addComponent(EntityId id, ComponentId componentId, Component *component, ArchetypeSignature &signature)
{
    std::map<ComponentId, std::shared_ptr<Component>> components;

    Archetype &oldArchetype = m_graph.getOrCreateArchetype(signature);
    if (oldArchetype.doesContainsEntity(id))
    {
        components = oldArchetype.getComponents(id);
        oldArchetype.removeEntity(id);
    }

    signature.push_back(componentId);
    components.emplace(componentId, std::shared_ptr<Component>(component));

    Archetype &newArchetype = m_graph.getOrCreateArchetype(signature);
    newArchetype.addEntity(id, components);
}
