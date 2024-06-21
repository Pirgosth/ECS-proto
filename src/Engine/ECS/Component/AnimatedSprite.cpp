#include "AnimatedSprite.hpp"

TextureManager AnimatedSprite::g_textureManager;

AnimatedSprite::AnimatedSprite(std::string spritesheetPath, float ips): m_ips(ips)
{
    std::ifstream jsonFile(spritesheetPath);
    json jsonSpriteSheet = json::parse(jsonFile);

    std::string spritePath = jsonSpriteSheet["path"];
    m_spritesheetTexture = *g_textureManager.getOrCreateTexture(spritePath);

    json sprites = jsonSpriteSheet["sprites"];
    for (auto& it : sprites.items()) {
        std::vector<int> jsonSpriteRect = it.value().get<std::vector<int>>();
        if (jsonSpriteRect.size() != 4)
            continue;
        m_spritesheet.push_back({jsonSpriteRect[0], jsonSpriteRect[1], jsonSpriteRect[2], jsonSpriteRect[3]});
    }
}
