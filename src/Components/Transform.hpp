#ifndef TRANSFORM_H_INCLUDED
#define TRANSFORM_H_INCLUDED

#include <SFML/Graphics.hpp>

class Transform
{
public:
    sf::Vector2f m_position;
    Transform(sf::Vector2f position);
};

#endif // TRANSFORM_H_INCLUDED