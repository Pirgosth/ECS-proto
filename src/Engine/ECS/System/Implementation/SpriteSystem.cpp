#include "SpriteSystem.hpp"

void SpriteSystem::update(std::map<EntityId, std::shared_ptr<Sprite>> entities)
{
    m_window.clear();

    for (auto [_, sprite] : entities)
    {
        m_window.draw(sprite->m_sprite);
    }

    m_window.display();
}

SpriteSystem::SpriteSystem(sf::RenderWindow &window): m_window(window) {}
