#include "Archetype.hpp"

unsigned int Archetype::transfertEntity(Archetype &target, unsigned int componentId)
{
    return target.m_components.push_back(m_components, componentId);
}

bool Archetype::erase(unsigned int componentIndex)
{
    return m_components.erase(componentIndex);
}

ArchetypeSignature Archetype::computeSignature()
{
    return m_components.computeSignature();
}
