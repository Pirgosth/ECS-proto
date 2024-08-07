#include "Archetype.hpp"

ArchetypeSignature Archetype::computeSignature()
{
    return m_components.computeSignature();
}
