#include "Components/Sprite.hpp"

TextureManager Sprite::g_textureManager;

Sprite::Sprite(std::string texturePath, int zIndex, bool enabled): m_zIndex(zIndex), m_enabled(enabled)
{
    setTexture(texturePath); 
}

Sprite::Sprite(std::shared_ptr<sf::Texture> texture, int zIndex, bool enabled): m_zIndex(zIndex), m_enabled(enabled)
{
    setTexture(texture);
}
void Sprite::setTexture(std::string texturePath)
{
    m_texture = g_textureManager.getOrCreateTexture(texturePath);
    m_sprite.setTexture(*m_texture);
}

void Sprite::setTexture(std::shared_ptr<sf::Texture> texture)
{
    if (texture)
        m_sprite.setTexture(*texture);
}
