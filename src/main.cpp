#include <iostream>

#include <SFML/Graphics.hpp>

#include "ECS.hpp"
#include "Engine.hpp"
#include "System.hpp"
#include "Systems/AnimatedSpriteSystem.hpp"
#include "Systems/BasicCollisionSystem.hpp"
#include "Systems/GravitySystem.hpp"
#include "Systems/RenderSystem.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "ECS", sf::Style::Default);

    ECS ecs;
    Engine engine;

    ecs.registerSystem(new AnimatedSpriteSystem());
    ecs.registerSystem(new BasicCollisionSystem());
    ecs.registerSystem(new GravitySystem(engine));
    ecs.registerSystem(new RenderSystem(window));

    ecs.createEntity(1, 4.248f);
    ecs.createEntity(478, true, 'a', 92.32f);
    ecs.createEntity(-24, "Hello World", 27.68f);

    for (int i = 0; i < 27; i++)
    {
        ecs.createEntity(AnimatedSprite("assets/spritesheets/green.json", 6), Transform(sf::Vector2f(100 + 40 * i, 150 - 10 * i)), Body());
    }

    sf::Clock timer;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        timer.restart();
        ecs.update();

        engine.m_deltaTimeInSec = timer.restart().asMicroseconds() / 1000000.0f;
        std::cout << engine.m_deltaTimeInSec * 1000.0f << std::endl;

        window.display();
    }

    return 0;
}
