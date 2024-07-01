#ifndef BASICCOLLISIONSYSTEM_H_INCLUDED
#define BASICCOLLISIONSYSTEM_H_INCLUDED

#include "Engine/ECS/System/System.hpp"
#include "Engine/ECS/Component/Body.hpp"
#include "Engine/ECS/Component/Transform.hpp"

class BasicCollisionSystem: public System<Transform, Body>
{
public:
    virtual void update(const float &deltaTime, std::unordered_map<EntityId, std::tuple<std::shared_ptr<Transform>, std::shared_ptr<Body>>> &entities) override;
};

#endif // BASICCOLLISIONSYSTEM_H_INCLUDED