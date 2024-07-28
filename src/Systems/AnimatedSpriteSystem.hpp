#ifndef ANIMATEDSPRITESYSTEM_H_INCLUDED
#define ANIMATEDSPRITESYSTEM_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "Components/AnimatedSprite.hpp"
#include "Components/Transform.hpp"
#include "System.hpp"

class AnimatedSpriteSystem : public System<AnimatedSprite, Transform>
{
private:
    sf::RenderWindow &m_window;
public:
    AnimatedSpriteSystem(sf::RenderWindow &window);
    virtual void update(ArchetypeGraph::CompositeArchetypeView<std::shared_ptr<AnimatedSprite>, std::shared_ptr<Transform>> &entities) override;
};

#endif // ANIMATEDSPRITESYSTEM_H_INCLUDED