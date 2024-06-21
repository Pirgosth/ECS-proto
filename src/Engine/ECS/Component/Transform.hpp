#ifndef TRANSFORM_H_INCLUDED
#define TRANSFORM_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "Component.hpp"

class SpriteSystem;
class AnimatedSpriteSystem;

class Transform : public Component
{
    friend SpriteSystem;
    friend AnimatedSpriteSystem;

private:
    sf::Vector2f m_position;
public:
    Transform(sf::Vector2f position);
    void setPosition(sf::Vector2f position);
};

#endif //TRANSFORM_H_INCLUDED