#ifndef PHYSICSYSTEM_H_INCLUDED
#define PHYSICSYSTEM_H_INCLUDED

#include "../Components/Body.hpp"
#include "../Components/Transform.hpp"
#include "../System.hpp"

class PhysicSystem : public System<Body, Transform>
{
private:
    const float &m_deltaTime;
public:
    PhysicSystem(const float &deltaTime);
    virtual void update(ArchetypeGraph::CompositeArchetypeView<std::shared_ptr<Body>, std::shared_ptr<Transform>> &entities) override;
};

#endif // PHYSICSYSTEM_H_INCLUDED