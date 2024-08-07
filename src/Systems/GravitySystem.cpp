#include "GravitySystem.hpp"

GravitySystem::GravitySystem(Engine &engine): m_engine(engine) {}

void GravitySystem::update(ArchetypeGraph::CompositeArchetypeView<std::shared_ptr<Transform>, std::shared_ptr<Body>> &entities)
{
    for (auto [transform, body]: entities)
    {
        body->m_speed += body->m_acceleration * m_engine.m_deltaTimeInSec;
        transform->m_position += body->m_speed * m_engine.m_deltaTimeInSec;
    }
}