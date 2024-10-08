#include "Systems/SpriteRenderSystem.hpp"

void SpriteRenderSystem::insertSorted(std::vector<std::tuple<std::shared_ptr<Sprite>, std::shared_ptr<Transform>>> &result, std::tuple<std::shared_ptr<Sprite>, std::shared_ptr<Transform>> toInsert)
{
    auto [insertSprite, _] = toInsert;

    if (!insertSprite->m_enabled)
            return;

    for (unsigned int i = 0; i < result.size(); i++)
    {   
        auto [nextSprite, _] = result[i];

        if (insertSprite->m_zIndex <= nextSprite->m_zIndex)
        {
            result.insert(result.begin() + i, toInsert);
            return;
        }
    }

    result.push_back(toInsert);
}

SpriteRenderSystem::SpriteRenderSystem(sf::RenderWindow &window) : m_window(window) {}

void SpriteRenderSystem::update(ArchetypeGraph::CompositeArchetypeView<std::shared_ptr<Sprite>, std::shared_ptr<Transform>> &entities)
{
    std::vector<std::tuple<std::shared_ptr<Sprite>, std::shared_ptr<Transform>>> sortedSprites;

    for (auto entity : entities)
    {
        insertSorted(sortedSprites, entity);
    }

    for (auto [sprite, transform] : sortedSprites)
    {
        sprite->m_sprite.setPosition(transform->m_position);
        m_window.draw(sprite->m_sprite);
    }
}
