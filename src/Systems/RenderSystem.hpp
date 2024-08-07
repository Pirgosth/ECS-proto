#ifndef RENDERSYSTEM_H_INCLUDED
#define RENDERSYSTEM_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "Components/AnimatedSprite.hpp"
#include "System.hpp"

class RenderSystem: public System<AnimatedSprite>
{
private:
    sf::RenderWindow &m_window;
public:
    RenderSystem(sf::RenderWindow &window);
    virtual void update(ArchetypeGraph::CompositeArchetypeView<std::shared_ptr<AnimatedSprite>> &entities) override;
};

#endif // RENDERSYSTEM_H_INCLUDED