#include "ArchetypeNode.hpp"

// FIX: Asymetrical insertion, causing loss of some results in getAllCompatibleArchetypes.
// I.e: A -> B exists, means that systems that requires A or AB are ok, but the ones that requires B are not because B -> A does not exists.
ArchetypeNode *ArchetypeNode::getOrCreateArchetypeNode(ArchetypeSignature signature)
{
    // TODO: move signature sorting in add or remove component.
    std::sort(signature.begin(), signature.end());
    auto currentNode = this;
    for (auto componentId: signature)
    {
        if (currentNode->m_branches.count(componentId) == 0)
        {
            currentNode->m_branches.emplace(componentId, std::make_shared<ArchetypeNode>());
        }

        currentNode = currentNode->m_branches.at(componentId).get();
    }

    return currentNode;
}

Archetype &ArchetypeNode::getOrCreateArchetype(ArchetypeSignature signature)
{
    return getOrCreateArchetypeNode(signature)->m_archetype;
}

std::vector<Archetype *> ArchetypeNode::getAllCompatibleArchetypes(ArchetypeSignature signature)
{
    std::vector<Archetype *> compatibleArchetypes;
    auto perfectNodeMatch = getOrCreateArchetypeNode(signature);
    compatibleArchetypes.push_back(&perfectNodeMatch->m_archetype);

    std::vector<ArchetypeNode *> nextNodesToVisit;
    nextNodesToVisit.push_back(perfectNodeMatch);

    do
    {
        std::vector<ArchetypeNode *> newNodesToVisit;
        for (auto node: nextNodesToVisit)
        {
            for (auto [_, childNode]: node->m_branches)
            {
                newNodesToVisit.push_back(childNode.get());
                compatibleArchetypes.push_back(&childNode->m_archetype);
            }
        }
        nextNodesToVisit = newNodesToVisit;
    } while (nextNodesToVisit.size() > 0);

    return compatibleArchetypes;
}
