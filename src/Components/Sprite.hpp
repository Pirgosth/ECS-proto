#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include <SFML/Graphics.hpp>

#include <string>

#include "TextureManager.hpp"

class Sprite
{
private:
    static TextureManager g_textureManager;
    std::shared_ptr<sf::Texture> m_texture;
public:
    Sprite(std::string texturePath);
    sf::Sprite m_sprite;
    void setTexture(std::string texturePath);
};

#endif // SPRITE_H_INCLUDED