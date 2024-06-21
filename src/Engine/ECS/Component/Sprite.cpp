#include "Sprite.hpp"

TextureManager Sprite::g_texturesManager;

void Sprite::setSprite(std::string spritePath)
{
    m_sprite.setTexture(*g_texturesManager.getOrCreateTexture(spritePath));
}

Sprite::Sprite(std::string spritePath)
{
    setSprite(spritePath);
}
