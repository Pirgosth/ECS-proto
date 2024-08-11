#include <iostream>

#include <SFML/Graphics.hpp>

#include "ECS.hpp"
#include "Engine.hpp"
#include "System.hpp"
#include "Systems/AnimatedSpriteSystem.hpp"
#include "Systems/BasicCollisionSystem.hpp"
#include "Systems/GravitySystem.hpp"
#include "Systems/RenderSystem.hpp"

#include "SoftDeleteContainer.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "ECS", sf::Style::Default);

    ECS ecs;
    Engine engine;

    ecs.registerSystem(new AnimatedSpriteSystem());
    ecs.registerSystem(new BasicCollisionSystem());
    ecs.registerSystem(new GravitySystem(engine));
    ecs.registerSystem(new RenderSystem(window));

    for (int i = 0; i < 27; i++)
    {
        ecs.createEntity(AnimatedSprite("assets/spritesheets/green.json", 6), Transform(sf::Vector2f(100 + 40 * i, 150 - 10 * i)), Body());
    }

    sf::Clock timer;

    for (unsigned int i = 0; i < 27; i++)
    {
        if (i % 2 == 1)
            ecs.deleteComponent<std::shared_ptr<Body>>(i);
        
        if (i % 4 == 1)
            ecs.deleteEntity(i);
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

// int main()
// {
//     SoftDeleteContainer<int> container;
//     std::cout << container.push_back(1) << std::endl;
//     std::cout << container.push_back(3) << std::endl;
//     std::cout << container.push_back(45) << std::endl;
//     std::cout << container.push_back(7) << std::endl;

//     container.erase(1);
//     container.erase(0);

//     for (unsigned int i = 0; i < container.size(); i++)
//         std::cout << "Is " << i << " alive: " << container.isAlive(i) << std::endl;

//     std::cout << container.push_back(2149) << std::endl;
//     std::cout << container.push_back(5) << std::endl;

//     std::cout << "Container size: " << container.size() << std::endl;

//     for (unsigned int i = 0; i < container.size(); i++)
//         std::cout << "Is " << i << " alive: " << container.isAlive(i) << std::endl;

//     for (auto el : container.getElements())
//     {
//         std::cout << el << std::endl;
//     }

//     return 0;
// }