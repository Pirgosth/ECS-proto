#include "Archetype.hpp"

unsigned int Archetype::g_ArchetypeCount = 0;

Archetype::Archetype(): m_id(++g_ArchetypeCount)
{
}

int Archetype::getId() const
{
    return m_id;
}
