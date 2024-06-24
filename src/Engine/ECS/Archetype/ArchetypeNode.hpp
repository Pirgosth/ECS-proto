#ifndef ARCHETYPENODE_H_INCLUDED
#define ARCHETYPENODE_H_INCLUDED

#include <memory>
#include <map>

#include "Engine/ECS/Archetype/Archetype.hpp"
#include "Engine/ECS/Types.hpp"

class ArchetypeNode;
class ArchetypeGraph;

class ArchetypeNode
{
    friend ArchetypeGraph;
private:
    ArchetypeSignature m_signature;
    Archetype m_archetype;
    std::map<ComponentId, std::shared_ptr<ArchetypeNode>> m_branches;
    ArchetypeNode *getOrCreateArchetypeNode(ArchetypeSignature signature);

public:
    ArchetypeNode(ArchetypeSignature signature);
    Archetype &getOrCreateArchetype(ArchetypeSignature signature);
    bool canHandle(ArchetypeSignature signature);
};

#endif // ARCHETYPENODE_H_INCLUDED