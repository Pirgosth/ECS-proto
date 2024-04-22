#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Engine/ECS/Engine.hpp"
#include "Engine/ECS/System/MonoSystem.hpp"
#include "Engine/ECS/System/System.hpp"

class SpriteSystem;

class Sprite : public Component
{
    friend SpriteSystem;

private:
    sf::Texture m_texture;
    sf::Sprite m_sprite;

public:
    void setSprite(std::string spritePath)
    {
        m_texture.loadFromFile(spritePath);
        m_sprite.setTexture(m_texture);
    }

    Sprite(std::string spritePath)
    {
        setSprite(spritePath);
    }
};

class Test : public Component
{
public:
    int health;
    Test(int health = 100) : health(health)
    {
    }
};

class TestSystem : public MonoSystem<Test>
{
    virtual void update(std::map<EntityId, std::shared_ptr<Test>> entities) override
    {
        for (auto [_, test] : entities)
        {
            if (test->health >= 0)
            {
                std::cout << test->health << std::endl;
                test->health--;
            }
        }
    }
};

class SpriteSystem : public MonoSystem<Sprite>
{
private:
    sf::RenderWindow &m_window;
    virtual void update(std::map<EntityId, std::shared_ptr<Sprite>> entities) override
    {
        m_window.clear();

        for (auto [_, sprite] : entities)
        {
            m_window.draw(sprite->m_sprite);
        }

        m_window.display();
    }

public:
    SpriteSystem(sf::RenderWindow &window) : m_window(window)
    {
    }
};

int main()
{
    Engine engine;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "ECS", sf::Style::Default);

    engine.registerSystem(new SpriteSystem(window));
    engine.registerSystem(new TestSystem());

    std::cout << ComponentManager::getId<Test>() << std::endl;
    std::cout << ComponentManager::getId<Sprite>() << std::endl;

    EntityId entity = engine.makeEntity();

    engine.addComponent(entity, new Test(42));
    engine.addComponent(entity, new Sprite("assets/spritesheet.png"));

    while (true)
    {
        engine.update();
    }

    return 0;
}
