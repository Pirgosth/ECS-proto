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

    ecs.registerSystem(new AnimatedSpriteSystem(engine.m_deltaTimeInSec));
    ecs.registerSystem(new BasicCollisionSystem());
    ecs.registerSystem(new GravitySystem(engine));
    ecs.registerSystem(new RenderSystem(window));

    for (int i = 0; i < 27; i++)
    {
        ecs.createEntity(Sprite("assets/green.png", 1), AnimatedSprite("assets/spritesheets/green.json", 6), Transform(sf::Vector2f(100 + 40 * i, 150 - 10 * i)), Body());
    }

    ecs.createEntity(Sprite("assets/background.png"), Transform(sf::Vector2f(0, 0)));

    sf::Clock timer;

    for (unsigned int i = 0; i < 27; i++)
    {
        if (i % 2 == 0)
        {
            auto sprite = ecs.getComponent<std::shared_ptr<Sprite>>(i);
            sprite->setTexture("assets/red.png");
        }

        if (i % 2 == 1)
            ecs.deleteComponent<std::shared_ptr<Body>>(i);
        
        if (i % 4 == 1)
            ecs.deleteEntity(i);
    }

    for (unsigned int i = 0; i < 27; i++)
    {
        if (i % 2 != 0)
            continue;

        auto animetedSprite = ecs.getComponent<std::shared_ptr<AnimatedSprite>>(i);
        animetedSprite->setSprite("assets/spritesheets/red.json");
    }

    bool pause = false;

    while (window.isOpen())
    {
        if (!pause)
        {
            engine.m_deltaTimeInSec = timer.restart().asMicroseconds() / 1000000.0f;
            std::cout << engine.m_deltaTimeInSec * 1000.0f << std::endl;
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::P)
            {
                pause = !pause;
                if (pause)
                    engine.m_deltaTimeInSec = 0;
                timer.restart();
            }
        }

        window.clear();

        ecs.update();

        window.display();
    }

    return 0;
}
