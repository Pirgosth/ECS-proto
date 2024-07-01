#include "GravitySystem.hpp"

void GravitySystem::init(EntityId entityId, std::tuple<std::shared_ptr<Body>, std::shared_ptr<Transform>> components)
{
    auto [body, _] = components;
    // Acceleration in pixels per second, not meters !!
    body->m_acceleration.y = 9.81 * 100;
}

void GravitySystem::update(const float &deltaTime, std::unordered_map<EntityId, std::tuple<std::shared_ptr<Body>, std::shared_ptr<Transform>>> &entities)
{
    for (auto [_, components]: entities)
    {
        auto [body, transform] = components;
        body->m_speed += body->m_acceleration * deltaTime;
        transform->setPosition(transform->m_position + body->m_speed * deltaTime);
    }
}
