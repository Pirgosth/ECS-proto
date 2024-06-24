#include "ArchetypeGraph.hpp"

ArchetypeGraph::ArchetypeGraph(): m_graph({}) {}

std::vector<Archetype *> ArchetypeGraph::getCompatibleArchetypes(ArchetypeSignature signature)
{
    std::vector<Archetype *> compatibleArchetypes;

    for (auto componentId: signature)
    {
        if (m_componentArchetypes.count(componentId) == 0)
            continue;
        for (auto archetype: m_componentArchetypes.at(componentId))
        {
            if (archetype->canHandle(signature))
                compatibleArchetypes.push_back(&archetype->m_archetype);
        }
    }

    return compatibleArchetypes;
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

    auto newArchetypeNode = m_graph.getOrCreateArchetypeNode(signature);
    for (auto componentId: signature)
    {
        if (m_componentArchetypes.count(componentId) == 0)
        {
            m_componentArchetypes.emplace(componentId, std::move(std::unordered_set<ArchetypeNode *>()));
        }
        auto &archetypeNodes = m_componentArchetypes.at(componentId);
        archetypeNodes.emplace(newArchetypeNode);
    }
    newArchetypeNode->m_archetype.addEntity(id, components);
}
