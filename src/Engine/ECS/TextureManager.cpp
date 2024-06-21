#include "TextureManager.hpp"

std::shared_ptr<sf::Texture> TextureManager::getOrCreateTexture(std::string texturePath)
{
    if (m_textures.count(texturePath) == 0)
    {
        auto texture = std::make_shared<sf::Texture>();
        texture->loadFromFile(texturePath);
        m_textures.emplace(texturePath, texture);
    }

    return m_textures.at(texturePath);
}
