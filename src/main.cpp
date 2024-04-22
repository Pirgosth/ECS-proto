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

class TestSystem : public System<Sprite, Test>
{
    virtual void update(std::map<EntityId, std::tuple<std::shared_ptr<Sprite>, std::shared_ptr<Test>>> entities) override
    {
        for (auto [_, components] : entities)
        {
            auto test = getComponent<Test>(components);
            std::cout << test->health << std::endl;
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

    engine.addComponent(engine.makeEntity(), new Sprite("assets/spritesheet.png"));
    // engine.addComponent(0, new Test(42));

    while (true)
    {
        engine.update();
    }

    return 0;
}
