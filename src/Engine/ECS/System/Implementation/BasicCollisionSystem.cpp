#include "BasicCollisionSystem.hpp"

void BasicCollisionSystem::update(const float &deltaTime, std::unordered_map<EntityId, std::tuple<std::shared_ptr<Transform>, std::shared_ptr<Body>>> &entities)
{
    for (auto [_, components]: entities)
    {
        auto [transform, body] = components;
        if (transform->m_position.y > 720 - 32)
        {
            body->m_speed = -body->m_speed;
            transform->m_position.y = 720 - 32;
        }
    }
}
