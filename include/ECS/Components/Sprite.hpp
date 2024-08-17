#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include <SFML/Graphics.hpp>

#include <string>

#include "../TextureManager.hpp"

class Sprite
{
private:
    static TextureManager g_textureManager;
    std::shared_ptr<sf::Texture> m_texture;
public:
    Sprite(std::string texturePath, int zIndex = 0, bool enabled = true);
    Sprite(std::shared_ptr<sf::Texture> texture, int zIndex = 0, bool enabled = true);
    sf::Sprite m_sprite;
    int m_zIndex;
    bool m_enabled;

    void setTexture(std::string texturePath);
    void setTexture(std::shared_ptr<sf::Texture> texture);
};

#endif // SPRITE_H_INCLUDED