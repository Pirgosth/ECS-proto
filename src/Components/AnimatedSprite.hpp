#ifndef ANIMATEDSPRITE_H_INCLUDED
#define ANIMATEDSPRITE_H_INCLUDED

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include "TextureManager.hpp"

using json = nlohmann::json;

class AnimatedSpriteSystem;

struct SpritesheetRecord
{   
    std::string path;
    std::vector<sf::IntRect> sprites;
}; typedef struct SpritesheetRecord SpritesheetRecord;

class AnimatedSprite
{
    friend AnimatedSpriteSystem;
private:
    static TextureManager g_textureManager;
    static std::unordered_map<std::string, std::shared_ptr<SpritesheetRecord>> g_spritesheetCache;
    
    std::vector<sf::IntRect> *m_spritesheet;
    std::shared_ptr<sf::Texture> m_spritesheetTexture;
    sf::Sprite m_activeSprite;
    unsigned int m_activeSpriteIndex;
    sf::Clock m_clock;
    
    float m_ips;

    const static std::shared_ptr<SpritesheetRecord> getOrLoadSpritesheet(std::string path);
public:
    AnimatedSprite(std::string spritesheetPath, float ips);
};


#endif // ANIMATEDSPRITE_H_INCLUDED