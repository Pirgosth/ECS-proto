#include "Systems/AnimatedSpriteSystem.hpp"

void AnimatedSpriteSystem::update(ArchetypeGraph::CompositeArchetypeView<std::shared_ptr<Sprite>, std::shared_ptr<AnimatedSprite>> &entities)
{
    for (auto [sprite, animatedSprite] : entities)
    {
        if (animatedSprite->m_activeSpriteIndex == -1 || animatedSprite->m_ips == 0 || animatedSprite->m_clock.getElapsedTime().asMilliseconds() >= (1000.0f / animatedSprite->m_ips))
        {
            animatedSprite->m_activeSpriteIndex = (animatedSprite->m_activeSpriteIndex + 1) % animatedSprite->m_spritesheet->sprites.size();
            auto currentSprite = animatedSprite->m_spritesheet->sprites[animatedSprite->m_activeSpriteIndex];
            sprite->m_sprite.setTextureRect(currentSprite);

            if (animatedSprite->m_spritesheet->usePivots)
            {
                auto pivot = animatedSprite->m_spritesheet->pivots[animatedSprite->m_activeSpriteIndex];
                sprite->m_sprite.setOrigin(pivot - sf::Vector2f(currentSprite.left, currentSprite.top));
            }
            
            animatedSprite->m_clock.restart();
        }
    }
}
