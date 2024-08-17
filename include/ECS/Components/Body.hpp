#ifndef BODY_H_INCLUDED
#define BODY_H_INCLUDED

#include <SFML/Graphics.hpp>

class Body
{
public:
    sf::Vector2f m_acceleration;
    sf::Vector2f m_speed;
};

#endif // BODY_H_INCLUDED