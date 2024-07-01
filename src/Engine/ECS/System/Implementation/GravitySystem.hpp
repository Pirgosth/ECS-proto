#ifndef GRAVITYSYSTEM_H_INCLUDED
#define GRAVITYSYSTEM_H_INCLUDED

#include "Engine/ECS/System/System.hpp"
#include "Engine/ECS/Component/Body.hpp"
#include "Engine/ECS/Component/Transform.hpp"

class GravitySystem : public System<Body, Transform>
{
public:
    virtual void init(EntityId entityId, std::tuple<std::shared_ptr<Body>, std::shared_ptr<Transform>> components) override;
    virtual void update(const float &deltaTime, std::unordered_map<EntityId, std::tuple<std::shared_ptr<Body>, std::shared_ptr<Transform>>> &entities) override;
};

#endif // GRAVITYSYSTEM_H_INCLUDED