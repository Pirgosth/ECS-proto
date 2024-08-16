#include "Components/AnimatedSprite.hpp"

std::unordered_map<std::string, std::shared_ptr<SpritesheetRecord>> AnimatedSprite::g_spritesheetCache;

const std::shared_ptr<SpritesheetRecord> AnimatedSprite::getOrLoadSpritesheet(std::string path)
{
    std::ifstream jsonFile(path);
    json jsonSpriteSheet = json::parse(jsonFile);
    if (jsonSpriteSheet.count("version") == 0)
        return getOrLoadSpritesheetV1(path);

    else if (jsonSpriteSheet["version"] == 2)
        return getOrLoadSpritesheetV2(path);

    return nullptr;
}

const std::shared_ptr<SpritesheetRecord> AnimatedSprite::getOrLoadSpritesheetV1(std::string path)
{
    SpritesheetRecord record;
    record.usePivots = false;

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
const std::shared_ptr<SpritesheetRecord> AnimatedSprite::getOrLoadSpritesheetV2(std::string path)
{
    SpritesheetRecord record;
    record.usePivots = true;

    if (g_spritesheetCache.count(path) == 0)
    {
        std::ifstream jsonFile(path);
        json jsonSpriteSheet = json::parse(jsonFile);

        std::string spritePath = jsonSpriteSheet["path"];
        json sprites = jsonSpriteSheet["sprites"];

        record.path = spritePath;

        for (auto &it : sprites.items())
        {
            std::vector<int> jsonSpriteRect = it.value()["rect"].get<std::vector<int>>();
            if (jsonSpriteRect.size() != 4)
                continue;
            float jsonSpritePivotX = it.value()["pivot"]["x"];
            float jsonSpritePivotY = it.value()["pivot"]["y"];
            record.sprites.push_back({jsonSpriteRect[0], jsonSpriteRect[1], jsonSpriteRect[2], jsonSpriteRect[3]});
            record.pivots.push_back(sf::Vector2f(jsonSpritePivotX, jsonSpritePivotY));
        }

        g_spritesheetCache.emplace(path, std::make_shared<SpritesheetRecord>(record));
    }

    return g_spritesheetCache.at(path);
}
AnimatedSprite::AnimatedSprite(std::string spritesheetPath, float ips, unsigned int startIndex) : m_elapsedTime(ips != 0 ? 1.0f / ips + 1 : 0), m_ips(ips), m_activeSpriteIndex(ips != 0 ? startIndex - 1 : startIndex)
{
    setSprite(spritesheetPath);
}

void AnimatedSprite::setSprite(std::string spritesheetPath)
{
    auto spriteSheet = getOrLoadSpritesheet(spritesheetPath);
    m_spritesheet = spriteSheet;
}
