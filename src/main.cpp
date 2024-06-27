#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Engine/ECS/Engine.hpp"
#include "Engine/ECS/System/Implementation/SpriteSystem.hpp"
#include "Engine/ECS/System/Implementation/AnimatedSpriteSystem.hpp"
#include "Engine/ECS/Component/AnimatedSprite.hpp"

#include "Engine/ECS/System/MonoSystem.hpp"

int main()
{
    Engine engine;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "ECS", sf::Style::Default);

    engine.registerSystem(new SpriteSystem(window));
    engine.registerSystem(new AnimatedSpriteSystem(window));

    for (int j = 0; j < 10; j++)
    {
        for (int i = 0; i < 200; i++)
        {
            auto sprite = engine.makeEntity();

            engine.addComponent(sprite, new Transform(sf::Vector2f(50 + 40 * i, 300 + (32 + 10) * j)));
            engine.addComponent(sprite, new AnimatedSprite("assets/spritesheets/green.json", 6));
        }
    }

    auto testEntity = engine.makeEntity();
    auto transformComponent = new Transform(sf::Vector2f(0, 0));
    engine.addComponent(testEntity, transformComponent);
    engine.addComponent(testEntity, new AnimatedSprite("assets/spritesheets/green.json", 6));

    bool isRunning = true;

    transformComponent->setPosition(sf::Vector2f(500, 0));

    sf::Clock delta;

    while (isRunning)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                isRunning = false;
        }

        window.clear();

        delta.restart();
        engine.update();
        const auto fps = delta.getElapsedTime().asMicroseconds() / 1000.0f;
        std::cout << "Engine time: " << fps << "ms" << std::endl;
        window.display();
    }

    return 0;
}
