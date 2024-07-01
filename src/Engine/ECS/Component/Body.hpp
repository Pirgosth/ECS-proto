#ifndef BODY_H_INCLUDED
#define BODY_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "Engine/ECS/Component/Component.hpp"

class BasicCollisionSystem;
class GravitySystem;

class Body: public Component
{
    friend BasicCollisionSystem;
    friend GravitySystem;

private:
    float m_weight;
    sf::Vector2f m_acceleration;
    sf::Vector2f m_speed;
};

#endif // BODY_H_INCLUDED