#include "Systems/AnimatedSpriteSystem.hpp"

#include <iostream>

AnimatedSpriteSystem::AnimatedSpriteSystem(const float &deltaTime) : m_deltaTime(deltaTime){}

void AnimatedSpriteSystem::update(ArchetypeGraph::CompositeArchetypeView<std::shared_ptr<Sprite>, std::shared_ptr<AnimatedSprite>> &entities)
{
    for (auto [sprite, animatedSprite] : entities)
    {
        animatedSprite->m_elapsedTime += m_deltaTime;
        if (animatedSprite->m_ips == 0 || animatedSprite->m_elapsedTime >= (1.0f / std::abs(animatedSprite->m_ips)))
        {
            auto ipsSign = animatedSprite->m_ips > 0 ? 1 : -1;
            if (animatedSprite->m_activeSpriteIndex >= 0)
                animatedSprite->m_activeSpriteIndex = ((int)animatedSprite->m_activeSpriteIndex + ipsSign) % animatedSprite->m_spritesheet->sprites.size();
            else
                animatedSprite->m_activeSpriteIndex = 0;
            auto currentSprite = animatedSprite->m_spritesheet->sprites[animatedSprite->m_activeSpriteIndex];
            
            if (currentSprite.width < 0)
            {
                sprite->m_sprite.setScale(sprite->m_sprite.getScale().x, -1);
                currentSprite.width *= -1;
            }
            else
                sprite->m_sprite.setScale(sprite->m_sprite.getScale().x, 1);

            if (currentSprite.height < 0)
            {
                sprite->m_sprite.setScale(-1, sprite->m_sprite.getScale().y);
                currentSprite.height *= -1;
            }
            else
                sprite->m_sprite.setScale(1, sprite->m_sprite.getScale().y);

            sprite->m_sprite.setTextureRect(currentSprite);

            if (animatedSprite->m_spritesheet->usePivots)
            {
                auto pivot = animatedSprite->m_spritesheet->pivots[animatedSprite->m_activeSpriteIndex];
                sprite->m_sprite.setOrigin(pivot - sf::Vector2f(currentSprite.left, currentSprite.top));
            }

            animatedSprite->m_elapsedTime = 0;
        }
    }
}
