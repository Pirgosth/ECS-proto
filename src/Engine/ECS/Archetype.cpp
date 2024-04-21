#include "Archetype.hpp"

unsigned int Archetype::g_ArchetypeCount = 0;

Archetype::Archetype(ArchetypeSignature signature): m_id(++g_ArchetypeCount), m_signature(std::move(signature))
{
    std::sort(m_signature.begin(), m_signature.end());

    if (m_signature.size() == 0)
    {
        m_components.emplace(-1, std::map<EntityId, std::shared_ptr<Component>>());
    }
}

int Archetype::getId() const
{
    return m_id;
}

bool Archetype::doesContainsEntity(EntityId id) const
{
    if (m_signature.size() == 0)
    {
        return m_components.at(-1).count(id) != 0;
    }

    return m_components.at(m_signature[0]).count(id) != 0;
}

void Archetype::addEntity(EntityId id, std::map<ComponentId, std::shared_ptr<Component>> components)
{
    if (m_signature.size() == 0)
    {
        m_components[-1].emplace(id, std::shared_ptr<Component>());
        return;
    }

    for (auto componentId: m_signature)
    {
        if (m_components.count(componentId) == 0)
            m_components.emplace(componentId, std::map<EntityId, std::shared_ptr<Component>>());

        m_components[componentId].emplace(id, components.at(componentId));
    }
}

bool Archetype::removeEntity(EntityId id)
{
    if (!doesContainsEntity(id))
        return false;

    for (auto componentId: m_signature)
    {
        m_components[componentId].erase(id);
    }

    return true;
}

ArchetypeSignature Archetype::getSignature() const
{
    return m_signature;
}

std::map<EntityId, std::map<ComponentId, std::shared_ptr<Component>>> Archetype::getEntities()
{
    std::map<EntityId, std::map<ComponentId, std::shared_ptr<Component>>> entities;

    if (m_signature.size() == 0)
        return entities;

    for (auto [entityId, _]: m_components[m_signature[0]])
    {
        entities.emplace(entityId, std::map<ComponentId, std::shared_ptr<Component>>());
        for (auto componentId: m_signature)
        {
            entities.at(entityId).emplace(componentId, m_components[componentId][entityId]);
        }
    }

    return entities;
}

std::map<ComponentId, std::shared_ptr<Component>> Archetype::getComponents(EntityId id)
{
    std::map<ComponentId, std::shared_ptr<Component>> components;

    if (!doesContainsEntity(id))
        return components;

    for (auto componentId: m_signature)
    {
        components.emplace(componentId, m_components[componentId][id]);
    }

    return components;
}
