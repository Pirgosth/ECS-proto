#include "ArchetypeGraph.hpp"

Node Node::root()
{
    auto rootBuilder = Node();
    rootBuilder.m_archetype = std::make_shared<Archetype>(Archetype::build());
    return rootBuilder;
}

std::shared_ptr<Node> Node::getNode(TypeId id)
{
    assert(m_leaves.count(id) != 0 && "This node does not have a subnode with this id");
    return m_leaves.at(id);
}

std::shared_ptr<Archetype> Node::getArchetype()
{
    return m_archetype;
}

ArchetypeGraph::ArchetypeGraph() : m_root(std::make_shared<Node>(Node::root())) {}

std::shared_ptr<Archetype> ArchetypeGraph::getArchetype(const ArchetypeSignature &signature)
{
    auto currentNode = m_root;
    for (auto componentId : signature)
    {
        currentNode = currentNode->getNode(componentId);
    }
    return currentNode->getArchetype();
}
