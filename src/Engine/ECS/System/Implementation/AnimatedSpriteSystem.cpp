#include "AnimatedSpriteSystem.hpp"

void AnimatedSpriteSystem::init(EntityId entityId, std::tuple<std::shared_ptr<Transform>, std::shared_ptr<AnimatedSprite>> components)
{
    auto [transform, animatedSprite] = components;
    auto activeSprite = getOrCreateSprite(entityId, *animatedSprite);
    activeSprite->sprite.setPosition(transform->m_position);
}

void AnimatedSpriteSystem::update(std::unordered_map <EntityId, std::tuple<std::shared_ptr<Transform>, std::shared_ptr<AnimatedSprite>>> &entities)
{
    for (auto [entityId, components] : entities)
    {
        auto [transform, animatedSprite] = components;
        auto activeSprite = getSprite(entityId, *animatedSprite);

        if (activeSprite->clock.getElapsedTime().asMilliseconds() >= (1000.0f / animatedSprite->m_ips))
        {
            activeSprite->currentIndex = (activeSprite->currentIndex + 1) % (*animatedSprite->m_spritesheet).size();
            activeSprite->sprite.setTextureRect((*animatedSprite->m_spritesheet)[activeSprite->currentIndex]);
            activeSprite->clock.restart();
        }

        activeSprite->sprite.setPosition(transform->m_position);
        m_window.draw(activeSprite->sprite);
    }
}

std::shared_ptr<ActiveSprite> AnimatedSpriteSystem::getOrCreateSprite(EntityId id, AnimatedSprite &animatedSprite)
{
    if (m_activeSprites.count(id) == 0)
    {
        sf::Sprite sprite;
        sprite.setTexture(*animatedSprite.m_spritesheetTexture);
        sprite.setTextureRect((*animatedSprite.m_spritesheet)[0]);
        m_activeSprites.emplace(id, std::make_shared<ActiveSprite>(sprite));
    }

    return m_activeSprites.at(id);
}

std::shared_ptr<ActiveSprite> AnimatedSpriteSystem::getSprite(EntityId id, AnimatedSprite &animatedSprite)
{
    return m_activeSprites.at(id);
}

AnimatedSpriteSystem::AnimatedSpriteSystem(sf::RenderWindow &window) : m_window(window) {}