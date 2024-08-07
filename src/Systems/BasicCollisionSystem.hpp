#ifndef BASICCOLLISIONSYSTEM_H_INCLUDED
#define BASICCOLLISIONSYSTEM_H_INCLUDED

#include "System.hpp"
#include "Components/Body.hpp"
#include "Components/Transform.hpp"

class BasicCollisionSystem: public System<Transform, Body>
{
public:
    virtual void update(ArchetypeGraph::CompositeArchetypeView<std::shared_ptr<Transform>, std::shared_ptr<Body>> &entities) override;
};

#endif // BASICCOLLISIONSYSTEM_H_INCLUDED