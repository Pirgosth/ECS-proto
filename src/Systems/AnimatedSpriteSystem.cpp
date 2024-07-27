#include "AnimatedSpriteSystem.hpp"

AnimatedSpriteSystem::AnimatedSpriteSystem(sf::RenderWindow &window): m_window(window) {

}

void AnimatedSpriteSystem::update(ArchetypeGraph::CompositeArchetypeView<std::shared_ptr<AnimatedSprite>, std::shared_ptr<Transform>> entities)
{
    for (auto [animatedSprite, transform] : entities)
    {
        auto &activeSprite = animatedSprite->m_activeSprite;

        if (animatedSprite->m_clock.getElapsedTime().asMilliseconds() >= (1000.0f / animatedSprite->m_ips))
        {
            animatedSprite->m_activeSpriteIndex = (animatedSprite->m_activeSpriteIndex + 1) % (*animatedSprite->m_spritesheet).size();
            activeSprite.setTextureRect((*animatedSprite->m_spritesheet)[animatedSprite->m_activeSpriteIndex]);
            animatedSprite->m_clock.restart();
        }

        activeSprite.setPosition(transform->m_position);
        m_window.draw(activeSprite);
    }
}
