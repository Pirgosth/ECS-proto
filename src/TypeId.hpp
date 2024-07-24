#ifndef TYPEID_H_INCLUDED
#define TYPEID_H_INCLUDED

#include <memory>

#include "Types.hpp"

class Type
{
public:
    static TypeId g_typeCounter;
    template <typename T>
    static TypeId getId();
    template <typename... Components>
    static ArchetypeSignature getSignature();
};

template <typename T>
inline TypeId Type::getId()
{
    static TypeId id = g_typeCounter++;
    return id;
}

template <typename... Components>
inline ArchetypeSignature Type::getSignature()
{
    return ArchetypeSignature({Type::getId<Components>()...});
}

#endif // TYPEID_H_INCLUDED
