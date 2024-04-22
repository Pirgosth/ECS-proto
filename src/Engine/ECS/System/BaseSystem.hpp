#ifndef BASESYSTEM_H_INCLUDED
#define BASESYSTEM_H_INCLUDED

#include <algorithm>
#include <memory>
#include <tuple>
#include <vector>

#include "Engine/ECS/Archetype/Archetype.hpp"
#include "Engine/ECS/Types.hpp"

class Engine;

class BaseSystem
{
    friend Engine;

protected:
    virtual void notifyUpdate(std::vector<Archetype *> archetypes) = 0;
    virtual ArchetypeSignature getSignature() const = 0;
};

#endif // BASESYSTEM_H_INCLUDED
