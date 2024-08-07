#ifndef ANIMATEDSPRITESYSTEM_H_INCLUDED
#define ANIMATEDSPRITESYSTEM_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "Components/AnimatedSprite.hpp"
#include "Components/Transform.hpp"
#include "System.hpp"

class AnimatedSpriteSystem : public System<AnimatedSprite, Transform>
{

public:
    virtual void update(ArchetypeGraph::CompositeArchetypeView<std::shared_ptr<AnimatedSprite>, std::shared_ptr<Transform>> &entities) override;
};

#endif // ANIMATEDSPRITESYSTEM_H_INCLUDED