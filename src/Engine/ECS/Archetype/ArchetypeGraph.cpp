#include "ArchetypeGraph.hpp"

std::vector<Archetype *> ArchetypeGraph::getCompatibleArchetypes(ArchetypeSignature signature)
{
    return m_graph.getAllCompatibleArchetypes(signature);
}

void ArchetypeGraph::createEntity(EntityId id)
{
    if (m_entitiesSignatures.count(id) == 0)
    {
        m_entitiesSignatures.emplace(id, ArchetypeSignature());
    }

    auto entitySignature = m_entitiesSignatures.at(id);

    Archetype &archetype = m_graph.getOrCreateArchetype(entitySignature);
    if (!archetype.doesContainsEntity(id))
        archetype.addEntity(id, std::map<EntityId, std::shared_ptr<Component>>());
}

void ArchetypeGraph::addComponent(EntityId id, ComponentId componentId, Component *component)
{
    // In this case, entity id is invalid or entity does not exists.
    if (m_entitiesSignatures.count(id) == 0)
        return;

    ArchetypeSignature &entitySignature = m_entitiesSignatures.at(id);
    std::map<ComponentId, std::shared_ptr<Component>> components;

    Archetype &oldArchetype = m_graph.getOrCreateArchetype(entitySignature);
    if (oldArchetype.doesContainsEntity(id))
    {
        components = oldArchetype.getComponents(id);
        oldArchetype.removeEntity(id);
    }

    entitySignature.push_back(componentId);
    components.emplace(componentId, std::shared_ptr<Component>(component));

    Archetype &newArchetype = m_graph.getOrCreateArchetype(entitySignature);
    newArchetype.addEntity(id, components);
}
