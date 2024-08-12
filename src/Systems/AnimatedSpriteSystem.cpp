#include "AnimatedSpriteSystem.hpp"

void AnimatedSpriteSystem::update(ArchetypeGraph::CompositeArchetypeView<std::shared_ptr<Sprite>, std::shared_ptr<AnimatedSprite>> &entities)
{
    for (auto [sprite, animatedSprite] : entities)
    {
        if (animatedSprite->m_activeSpriteIndex == -1 || animatedSprite->m_clock.getElapsedTime().asMilliseconds() >= (1000.0f / animatedSprite->m_ips))
        {
            animatedSprite->m_activeSpriteIndex = (animatedSprite->m_activeSpriteIndex + 1) % (*animatedSprite->m_spritesheet).size();
            sprite->m_sprite.setTextureRect((*animatedSprite->m_spritesheet)[animatedSprite->m_activeSpriteIndex]);
            animatedSprite->m_clock.restart();
        }
    }
}
