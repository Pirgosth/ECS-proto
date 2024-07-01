#ifndef TRANSFORM_H_INCLUDED
#define TRANSFORM_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "Component.hpp"

class AnimatedSpriteSystem;
class BasicCollisionSystem;
class GravitySystem;
class SpriteSystem;

class Transform : public Component
{
    friend AnimatedSpriteSystem;
    friend BasicCollisionSystem;
    friend GravitySystem;
    friend SpriteSystem;

private:
    sf::Vector2f m_position;

public:
    Transform(sf::Vector2f position);
    void setPosition(sf::Vector2f position);
};

#endif // TRANSFORM_H_INCLUDED