#include "Systems/BasicCollisionSystem.hpp"

void BasicCollisionSystem::update(ArchetypeGraph::CompositeArchetypeView<std::shared_ptr<Transform>,std::shared_ptr<Body>>& entities)
{
    for (auto [transform, body]: entities)
    {
        if (transform->m_position.y > 720 - 32)
        {
            body->m_speed = -body->m_speed;
            transform->m_position.y = 720 - 32;
        }
    }
}