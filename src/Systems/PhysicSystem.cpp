#include "Systems/PhysicSystem.hpp"

PhysicSystem::PhysicSystem(const float & deltaTime): m_deltaTime(deltaTime) {}

void PhysicSystem::update(ArchetypeGraph::CompositeArchetypeView<std::shared_ptr<Body>, std::shared_ptr<Transform>> &entities)
{
    for (auto [body, transform]: entities)
    {
        body->m_speed += body->m_acceleration * m_deltaTime;
        transform->m_position += body->m_speed * m_deltaTime;
    }
}
