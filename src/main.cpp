#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Engine/ECS/Engine.hpp"
#include "Engine/ECS/System/Implementation/SpriteSystem.hpp"
#include "Engine/ECS/System/Implementation/AnimatedSpriteSystem.hpp"
#include "Engine/ECS/Component/AnimatedSprite.hpp"

#include "Engine/ECS/System/MonoSystem.hpp"

class DummyComponent: public Component
{

};

class DummySystem: public MonoSystem<DummyComponent>
{
    virtual void update(std::map<EntityId, std::shared_ptr<DummyComponent>> entities) override
    {
        for (auto [entityId, dummy]: entities)
        {
            std::cout << "Dummy component detected for entity id: " << entityId << std::endl;
        }
    }
};

int main()
{
    Engine engine;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "ECS", sf::Style::Default);

    engine.registerSystem(new SpriteSystem(window));
    engine.registerSystem(new AnimatedSpriteSystem(window));
    engine.registerSystem(new DummySystem());

    auto dummy = engine.makeEntity();
    engine.addComponent(dummy, new DummyComponent());

    for (int i = 0; i < 12; i++)
    {
        auto sprite = engine.makeEntity();

        engine.addComponent(sprite, new Transform(sf::Vector2f(50 + 40 * i, 300)));
        engine.addComponent(sprite, new AnimatedSprite("assets/spritesheets/green.json", 6));
    }

    auto testEntity = engine.makeEntity();
    engine.addComponent(testEntity, new DummyComponent());
    engine.addComponent(testEntity, new Transform(sf::Vector2f(0, 0)));
    engine.addComponent(testEntity, new AnimatedSprite("assets/spritesheets/green.json", 6));

    bool isRunning = true;

    while (isRunning)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                isRunning = false;
        }

        window.clear();
        engine.update();
        window.display();
    }

    return 0;
}
