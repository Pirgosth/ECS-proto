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
    virtual void notifyInit(EntityId entityId, std::map<ComponentId, std::shared_ptr<Component>> &components) = 0;
    virtual void notifyUpdate(const float &deltaTime) = 0;
    virtual void updateEntity(EntityId entityId, std::map<ComponentId, std::shared_ptr<Component>> components) = 0;
    virtual ArchetypeSignature getSignature() const = 0;
public:
    bool canHandle(ArchetypeSignature signature);
};

#endif // BASESYSTEM_H_INCLUDED
