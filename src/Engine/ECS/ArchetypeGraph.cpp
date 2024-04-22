#include "ArchetypeGraph.hpp"

Archetype &ArchetypeGraph::getOrCreateArchetype(ArchetypeSignature signature)
{
    if (m_archetypes.count(signature) == 0)
        m_archetypes.emplace(signature, std::move(Archetype(signature)));

    return m_archetypes.at(signature);
}

std::vector<Archetype> ArchetypeGraph::getCompatibleArchetypes(ArchetypeSignature signature)
{
    std::vector<Archetype> archetypes;
    if (m_archetypes.count(signature) != 0)
        archetypes.push_back(m_archetypes.at(signature));

    return archetypes;
}

void ArchetypeGraph::createEntity(EntityId id)
{
    Archetype &archetype = getOrCreateArchetype(ArchetypeSignature());
    if (!archetype.doesContainsEntity(id))
        archetype.addEntity(id, std::map<EntityId, std::shared_ptr<Component>>());
}

void ArchetypeGraph::addComponent(EntityId id, ComponentId componentId, Component *component)
{
    ArchetypeSignature signature;
    std::map<ComponentId, std::shared_ptr<Component>> components;

    for (auto &[_, archetype] : m_archetypes)
    {
        if (archetype.doesContainsEntity(id))
        {
            signature = archetype.getSignature();
            components = archetype.getComponents(id);
            archetype.removeEntity(id);
            break;
        }
    }

    signature.push_back(componentId);
    components.emplace(componentId, std::shared_ptr<Component>(component));

    Archetype &matchingArchetype = getOrCreateArchetype(signature);
    matchingArchetype.addEntity(id, components);
}
