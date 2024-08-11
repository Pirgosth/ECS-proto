#include "HeterogeneousContainer.hpp"

HeterogeneousContainer::HeterogeneousContainer(): m_elementCount(0), m_lastElementErased(0), m_erasedCount(0) {}

HeterogeneousContainer::HeterogeneousContainer(const HeterogeneousContainer &x): HeterogeneousContainer()
{
    m_containers = x.clone().m_containers;
}

HeterogeneousContainer HeterogeneousContainer::clone() const
{
    HeterogeneousContainer cloneContainer;
    for (auto [id, container]: m_containers)
        cloneContainer.m_containers.emplace(id, std::shared_ptr<BaseContainer>(container->clone()));

    return cloneContainer;
}

unsigned int HeterogeneousContainer::push_back(HeterogeneousContainer &from, unsigned int componentIndex)
{
    auto insertedId = m_elementCount++;
    for (auto [typeId, container] : m_containers)
    {
        assert (from.m_containers.count(typeId) != 0 && "These containers are not copy compatible");
        auto fromContainer = from.m_containers.at(typeId);

        container->copy(*fromContainer, componentIndex);
    }
    return insertedId;
}

bool HeterogeneousContainer::isAlive(unsigned int index)
{
    return m_erasedCount == 0 || (m_lastElementErased != index && m_elements[index] == index);
}

bool HeterogeneousContainer::erase(unsigned int index)
{
    if (index >= m_elements.size())
        return false;

    if (m_erasedCount != 0)
    {
        m_elements[index] = m_lastElementErased;
        m_elements[m_lastElementErased] = index;
    }

    m_lastElementErased = index;
    m_erasedCount++;

    return true;
}

void HeterogeneousContainer::copy(const HeterogeneousContainer &from, int index)
{
    for (auto [id, container]: from.m_containers)
    {
        assert(m_containers.count(id) != 0);
        m_containers[id]->copy(*container, index);
    }
}

unsigned int HeterogeneousContainer::size() const
{
    if (m_containers.size() == 0)
        return -1;

    return m_containers.begin()->second->size();
}

ArchetypeSignature HeterogeneousContainer::computeSignature()
{
    ArchetypeSignature signature;

    for (auto [typeId, _] : m_containers)
        signature.emplace(typeId);

    return signature;
}
