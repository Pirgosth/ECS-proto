#include <SFML/Graphics.hpp>

#include "Component.hpp"
#include "Engine/ECS/TextureManager.hpp"

class SpriteSystem;

class Sprite : public Component
{
    friend SpriteSystem;

private:
    static TextureManager g_texturesManager;
    sf::Sprite m_sprite;

public:
    void setSprite(std::string spritePath);
    Sprite(std::string spritePath);
};