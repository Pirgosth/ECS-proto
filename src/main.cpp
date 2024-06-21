#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Engine/ECS/Engine.hpp"
#include "Engine/ECS/System/Implementation/SpriteSystem.hpp"

int main()
{
    Engine engine;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "ECS", sf::Style::Default);

    engine.registerSystem(new SpriteSystem(window));

    EntityId entity = engine.makeEntity();

    engine.addComponent(entity, new Sprite("assets/spritesheet.png"));

    bool isRunning = true;

    while (isRunning)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                isRunning = false;
        }
        engine.update();
    }

    return 0;
}
