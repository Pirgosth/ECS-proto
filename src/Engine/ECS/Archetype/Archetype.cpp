#include "Archetype.hpp"

unsigned int Archetype::g_ArchetypeCount = 0;

Archetype::Archetype(ArchetypeSignature signature) : m_id(++g_ArchetypeCount), m_signature(std::move(signature))
{
    std::sort(m_signature.begin(), m_signature.end());
}

int Archetype::getId() const
{
    return m_id;
}

bool Archetype::doesContainsEntity(EntityId id) const
{
    return m_entities.count(id) != 0;
}

void Archetype::addEntity(EntityId id, std::map<ComponentId, std::shared_ptr<Component>> components)
{
    if (doesContainsEntity(id))
        return;

    m_entities.emplace(id, components);
}

bool Archetype::removeEntity(EntityId id)
{
    if (!doesContainsEntity(id))
        return false;

    m_entities.erase(id);

    return true;
}

ArchetypeSignature Archetype::getSignature() const
{
    return m_signature;
}

std::map<EntityId, std::map<ComponentId, std::shared_ptr<Component>>> &Archetype::getEntities()
{
    return m_entities;
}

std::map<ComponentId, std::shared_ptr<Component>> Archetype::getComponents(EntityId id)
{
    if (!doesContainsEntity(id))
        return std::map<ComponentId, std::shared_ptr<Component>>();

    return m_entities.at(id);
}
