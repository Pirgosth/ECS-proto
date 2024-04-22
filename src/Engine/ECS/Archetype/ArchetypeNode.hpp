#ifndef ARCHETYPENODE_H_INCLUDED
#define ARCHETYPENODE_H_INCLUDED

#include <memory>
#include <map>

#include "Engine/ECS/Archetype/Archetype.hpp"
#include "Engine/ECS/Types.hpp"

class ArchetypeNode;

class ArchetypeNode
{
private:
    Archetype m_archetype;
    std::map<ComponentId, std::shared_ptr<ArchetypeNode>> m_branches;
    ArchetypeNode *getOrCreateArchetypeNode(ArchetypeSignature signature);

public:
    Archetype &getOrCreateArchetype(ArchetypeSignature signature);
    std::vector<Archetype *> getAllCompatibleArchetypes(ArchetypeSignature signature);
};

#endif // ARCHETYPENODE_H_INCLUDED