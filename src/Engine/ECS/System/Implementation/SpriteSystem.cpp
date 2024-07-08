#include "SpriteSystem.hpp"

void SpriteSystem::update(const float &deltaTime, std::unordered_map<EntityId, std::tuple<std::shared_ptr<Transform>, std::shared_ptr<Sprite>>> &entities)
{
    for (auto [_, components] : entities)
    {
        auto [transform, sprite] = components;
        sprite->m_sprite.setPosition(transform->m_position);
        m_window.draw(sprite->m_sprite);
    }
}

void SpriteSystem::draw(const sf::RenderWindow &window, std::unordered_map<EntityId, std::tuple<std::shared_ptr<Transform>, std::shared_ptr<Sprite>>> &entities)
{
    
}

SpriteSystem::SpriteSystem(sf::RenderWindow &window): m_window(window) {}
