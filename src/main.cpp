#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Engine/ECS/Engine.hpp"
#include "Engine/ECS/System/Implementation/SpriteSystem.hpp"
#include "Engine/ECS/System/Implementation/AnimatedSpriteSystem.hpp"
#include "Engine/ECS/System/Implementation/BasicCollisionSystem.hpp"
#include "Engine/ECS/System/Implementation/GravitySystem.hpp"

class DummyComponent : public Component
{
};

int main()
{
    Engine engine;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "ECS", sf::Style::Default);

    engine.registerSystem(new SpriteSystem(window));
    engine.registerSystem(new AnimatedSpriteSystem(window));
    engine.registerSystem(new BasicCollisionSystem());
    engine.registerSystem(new GravitySystem());

    for (int i = 0; i < 27; i++)
    {
        auto testEntity = engine.makeEntity();
        engine.addComponent(testEntity, new Transform(sf::Vector2f(100 + 40 * i, 150 - 10 * i)));
        engine.addComponent(testEntity, new AnimatedSprite("assets/spritesheets/green.json", 6));
        engine.addComponent(testEntity, new Body());
    }

    engine.start();

    while (engine.isRunning())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {  
            if (event.type == sf::Event::Closed)
                engine.stop();
        }

        window.clear();
        engine.draw(window);
        window.display();
    }

    return 0;
}
