#ifndef ANIMATEDSPRITE_H_INCLUDED
#define ANIMATEDSPRITE_H_INCLUDED

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include "Component.hpp"
#include "Engine/ECS/TextureManager.hpp"

using json = nlohmann::json;

class AnimatedSpriteSystem;

struct SpritesheetRecord
{   
    std::string path;
    std::vector<sf::IntRect> sprites;
}; typedef struct SpritesheetRecord SpritesheetRecord;

class AnimatedSprite: public Component
{
    friend AnimatedSpriteSystem;
private:
    static TextureManager g_textureManager;
    static std::unordered_map<std::string, std::shared_ptr<SpritesheetRecord>> g_spritesheetCache;
    
    std::vector<sf::IntRect> *m_spritesheet;
    std::shared_ptr<sf::Texture> m_spritesheetTexture;
    float m_ips;

    const static std::shared_ptr<SpritesheetRecord> getOrLoadSpritesheet(std::string path);
public:
    AnimatedSprite(std::string spritesheetPath, float ips);
};

#endif //ANIMATEDSPRITE_H_INCLUDED