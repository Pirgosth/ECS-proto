#ifndef ANIMATEDSPRITE_H_INCLUDED
#define ANIMATEDSPRITE_H_INCLUDED

#include <fstream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include "Component.hpp"
#include "Engine/ECS/TextureManager.hpp"

using json = nlohmann::json;

class AnimatedSpriteSystem;

class AnimatedSprite: public Component
{
    friend AnimatedSpriteSystem;
private:
    static TextureManager g_textureManager;
    std::vector<sf::IntRect> m_spritesheet;
    sf::Texture m_spritesheetTexture;
    float m_ips;
public:
    AnimatedSprite(std::string spritesheetPath, float ips);
};

#endif //ANIMATEDSPRITE_H_INCLUDED