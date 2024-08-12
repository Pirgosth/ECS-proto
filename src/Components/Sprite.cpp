#include "Sprite.hpp"

TextureManager Sprite::g_textureManager;

Sprite::Sprite(std::string texturePath)
{
    setTexture(texturePath); 
}

void Sprite::setTexture(std::string texturePath)
{
    m_texture = g_textureManager.getOrCreateTexture(texturePath);
    m_sprite.setTexture(*m_texture);
}
