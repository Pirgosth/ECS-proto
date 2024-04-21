#ifndef ARCHETYPE_H_INCLUDED
#define ARCHETYPE_H_INCLUDED

#include <algorithm>
#include <map>
#include <memory>
#include <vector>

#include "Engine/ECS/Component.hpp"
#include "Engine/ECS/Types.hpp"

class Archetype
{
private:
    static unsigned int g_ArchetypeCount;
    const unsigned int m_id;

    ArchetypeSignature m_signature;
    std::map<EntityId, std::map<ComponentId, std::shared_ptr<Component>>> m_entities;

public:
    Archetype(ArchetypeSignature signature);
    int getId() const;
    bool doesContainsEntity(EntityId id) const;
    void addEntity(EntityId id, std::map<ComponentId, std::shared_ptr<Component>> components);
    bool removeEntity(EntityId id);
    ArchetypeSignature getSignature() const;
    std::map<EntityId, std::map<ComponentId, std::shared_ptr<Component>>> &getEntities();
    std::map<ComponentId, std::shared_ptr<Component>> getComponents(EntityId id);
};

#endif // ARCHETYPE_H_INCLUDED