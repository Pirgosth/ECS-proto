#include "Transform.hpp"

Transform::Transform(sf::Vector2f position): m_position(position) {}

void Transform::setPosition(sf::Vector2f position)
{
    m_position = position;
}
