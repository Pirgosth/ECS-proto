#include "RenderSystem.hpp"

RenderSystem::RenderSystem(sf::RenderWindow &window): m_window(window) {}

void RenderSystem::update(ArchetypeGraph::CompositeArchetypeView<std::shared_ptr<AnimatedSprite>> &entities)
{
    for (auto [animatedSprite] : entities)
    {
        m_window.draw(animatedSprite->m_activeSprite);
    }
}
