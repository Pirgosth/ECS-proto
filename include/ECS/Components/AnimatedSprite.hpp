#ifndef ANIMATEDSPRITE_H_INCLUDED
#define ANIMATEDSPRITE_H_INCLUDED

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class AnimatedSpriteSystem;

struct SpritesheetRecord
{   
    std::string path;
    std::vector<sf::IntRect> sprites;
}; typedef struct SpritesheetRecord SpritesheetRecord;

class AnimatedSprite
{
private:
    static std::unordered_map<std::string, std::shared_ptr<SpritesheetRecord>> g_spritesheetCache;
    const static std::shared_ptr<SpritesheetRecord> getOrLoadSpritesheet(std::string path);
public:
    float m_ips;
    std::vector<sf::IntRect> *m_spritesheet;
    int m_activeSpriteIndex;
    sf::Clock m_clock;

    AnimatedSprite(std::string spritesheetPath, float ips);
    void setSprite(std::string spritesheetPath);
};


#endif // ANIMATEDSPRITE_H_INCLUDED