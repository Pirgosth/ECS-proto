#include "HeterogeneousContainer.hpp"

HeterogeneousContainer::HeterogeneousContainer(const HeterogeneousContainer &x)
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
