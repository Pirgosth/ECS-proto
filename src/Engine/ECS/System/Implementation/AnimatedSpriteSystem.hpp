#ifndef ANIMATEDSPRITESYSTEM_H_INCLUDED
#define ANIMATEDSPRITESYSTEM_H_INCLUDED

#include "Engine/ECS/System/System.hpp"
#include "Engine/ECS/Component/AnimatedSprite.hpp"
#include "Engine/ECS/Component/Transform.hpp"

#include <memory>
#include <unordered_map>

struct ActiveSprite {

    ActiveSprite(sf::Sprite sprite)
    {
        this->sprite = sprite;
    }

    sf::Sprite sprite;
    unsigned int currentIndex = 0;
    sf::Clock clock;
}; typedef struct ActiveSprite ActiveSprite;

class AnimatedSpriteSystem : public System<Transform, AnimatedSprite>
{
private:
    sf::RenderWindow &m_window;
    std::unordered_map<EntityId, std::shared_ptr<ActiveSprite>> m_activeSprites;
    virtual void init(EntityId entityId, std::tuple<std::shared_ptr<Transform>, std::shared_ptr<AnimatedSprite>> components) override;
    virtual void update(const float &deltaTime, std::unordered_map<EntityId, std::tuple<std::shared_ptr<Transform>, std::shared_ptr<AnimatedSprite>>> &entities) override;
    std::shared_ptr<ActiveSprite> getOrCreateSprite(EntityId id, AnimatedSprite &animatedSprite);
    std::shared_ptr<ActiveSprite> getSprite(EntityId id, AnimatedSprite &animatedSprite);
public:
    AnimatedSpriteSystem(sf::RenderWindow &window);
};

#endif //ANIMATEDSPRITESYSTEM_H_INCLUDED