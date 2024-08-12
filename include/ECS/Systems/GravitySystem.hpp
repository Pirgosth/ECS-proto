#ifndef GRAVITYSYSTEM_H_INCLUDED
#define GRAVITYSYSTEM_H_INCLUDED

#include "../Engine.hpp"
#include "../System.hpp"
#include "../Components/Body.hpp"
#include "../Components/Transform.hpp"

class GravitySystem : public System<Transform, Body>
{
private:
    Engine &m_engine;
public:
    GravitySystem(Engine &engine);
    virtual void update(ArchetypeGraph::CompositeArchetypeView<std::shared_ptr<Transform>, std::shared_ptr<Body>> &entities) override;
};

#endif // GRAVITYSYSTEM_H_INCLUDED