#ifndef ARCHETYPE_H_INCLUDED
#define ARCHETYPE_H_INCLUDED

#include <vector>

class Archetype
{
private:
    static unsigned int g_ArchetypeCount;
    const unsigned int m_id;
    
    std::vector<int> m_componentIds;

public:
    Archetype(std::vector<int> componentIds);
    int getId() const;
};

#endif // ARCHETYPE_H_INCLUDED