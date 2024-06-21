#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED

#include <unordered_map>
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

class TextureManager
{
private:
    std::unordered_map<std::string, std::shared_ptr<sf::Texture>> m_textures;
public:
    std::shared_ptr<sf::Texture> getOrCreateTexture(std::string texturePath);
};

#endif //TEXTUREMANAGER_H_INCLUDED