#include "AnimatedSprite.hpp"

TextureManager AnimatedSprite::g_textureManager;
std::unordered_map<std::string, std::shared_ptr<SpritesheetRecord>> AnimatedSprite::g_spritesheetCache;

const std::shared_ptr<SpritesheetRecord> AnimatedSprite::getOrLoadSpritesheet(std::string path)
{
    SpritesheetRecord record;

    if (g_spritesheetCache.count(path) == 0)
    {
        std::ifstream jsonFile(path);
        json jsonSpriteSheet = json::parse(jsonFile);

        std::string spritePath = jsonSpriteSheet["path"];
        json sprites = jsonSpriteSheet["sprites"];

        record.path = spritePath;

        for (auto &it : sprites.items())
        {
            std::vector<int> jsonSpriteRect = it.value().get<std::vector<int>>();
            if (jsonSpriteRect.size() != 4)
                continue;
            record.sprites.push_back({jsonSpriteRect[0], jsonSpriteRect[1], jsonSpriteRect[2], jsonSpriteRect[3]});
        }

        g_spritesheetCache.emplace(path, std::make_shared<SpritesheetRecord>(record));
    }

    return g_spritesheetCache.at(path);
}

AnimatedSprite::AnimatedSprite(std::string spritesheetPath, float ips) : m_ips(ips)
{
    auto jsonSpriteSheet = getOrLoadSpritesheet(spritesheetPath);
    m_spritesheetTexture = g_textureManager.getOrCreateTexture(jsonSpriteSheet->path);
    m_spritesheet = &jsonSpriteSheet->sprites;
}
