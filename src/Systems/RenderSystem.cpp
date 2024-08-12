#include "RenderSystem.hpp"

RenderSystem::RenderSystem(sf::RenderWindow &window): m_window(window) {}

void RenderSystem::update(ArchetypeGraph::CompositeArchetypeView<std::shared_ptr<Sprite>, std::shared_ptr<Transform>> &entities)
{
    for (auto [sprite, transform] : entities)
    {
        sprite->m_sprite.setPosition(transform->m_position);
        m_window.draw(sprite->m_sprite);
    }
}
