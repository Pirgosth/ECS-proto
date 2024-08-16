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
    std::vector<sf::Vector2f> pivots;
    bool usePivots;
}; typedef struct SpritesheetRecord SpritesheetRecord;

class AnimatedSprite
{
private:
    static std::unordered_map<std::string, std::shared_ptr<SpritesheetRecord>> g_spritesheetCache;
    
    const static std::shared_ptr<SpritesheetRecord> getOrLoadSpritesheet(std::string path);
    const static std::shared_ptr<SpritesheetRecord> getOrLoadSpritesheetV1(std::string path);
    const static std::shared_ptr<SpritesheetRecord> getOrLoadSpritesheetV2(std::string path);
public:
    float m_elapsedTime;
    float m_ips;
    std::shared_ptr<SpritesheetRecord> m_spritesheet;
    int m_activeSpriteIndex;
    
    AnimatedSprite(std::string spritesheetPath, float ips, unsigned int startIndex = 0);
    void setSprite(std::string spritesheetPath);
};


#endif // ANIMATEDSPRITE_H_INCLUDED