#include "ArchetypeNode.hpp"

ArchetypeNode *ArchetypeNode::getOrCreateArchetypeNode(ArchetypeSignature signature)
{
    // TODO: move signature sorting in add or remove component.
    std::sort(signature.begin(), signature.end());
    auto currentNode = this;
    ArchetypeSignature currentSignature;

    for (auto componentId: signature)
    {
        currentSignature.push_back(componentId);
        if (currentNode->m_branches.count(componentId) == 0)
        {
            currentNode->m_branches.emplace(componentId, std::make_shared<ArchetypeNode>(currentSignature));
        }

        currentNode = currentNode->m_branches.at(componentId).get();
    }

    return currentNode;
}

ArchetypeNode::ArchetypeNode(ArchetypeSignature signature): m_signature(std::move(signature)) {}

Archetype &ArchetypeNode::getOrCreateArchetype(ArchetypeSignature signature)
{
    return getOrCreateArchetypeNode(signature)->m_archetype;
}

bool ArchetypeNode::canHandle(ArchetypeSignature signature)
{
    for (auto componentId: signature)
    {
        if (std::find(m_signature.begin(), m_signature.end(), componentId) == m_signature.end())
            return false;
    }

    return true;
}
