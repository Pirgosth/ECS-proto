#ifndef ANIMATEDSPRITESYSTEM_H_INCLUDED
#define ANIMATEDSPRITESYSTEM_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "../Components/AnimatedSprite.hpp"
#include "../Components/Sprite.hpp"
#include "../System.hpp"

class AnimatedSpriteSystem : public System<Sprite, AnimatedSprite>
{

public:
    virtual void update(ArchetypeGraph::CompositeArchetypeView<std::shared_ptr<Sprite>, std::shared_ptr<AnimatedSprite>> &entities) override;
};

#endif // ANIMATEDSPRITESYSTEM_H_INCLUDED