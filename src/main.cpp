#include <iostream>

#include <SFML/Graphics.hpp>

#include "Engine/ECS/ComponentManager.hpp"
#include "Engine/ECS/System.hpp"

class Test: public Component {
public:
    int health;

    Test(int health = 100): health(health) {}
};

class SubTest: public Test {
public:
    SubTest(int health): Test(health) {}
};

int main()
{
    ComponentManager manager = ComponentManager::getInstance();
    manager.addComponent(new Test());
    manager.addComponent(new Test(50));
    manager.addComponent(new SubTest(-120));

    manager.addComponent(new Test(30));

    // for (auto component : manager.getComponents<Test>())
    // {
    //     std::cout << component->health << std::endl;
    // }

    // for (auto component : manager.getComponents<SubTest>())
    // {
    //     std::cout << component->health << std::endl;
    // }

    System<Test*, SubTest*> SystemA;
    System<SubTest*> SystemB;
    // std::cout << SystemA.getId() << std::endl;
    // std::cout << SystemA.getId() << std::endl;

    // std::cout << SystemB.getId() << std::endl;

    for (auto componentId : SystemA.getComponentIds())
    {
        std::cout << componentId << "; ";
    }

    std::cout << std::endl;

    for (auto componentId : SystemB.getComponentIds())
    {
        std::cout << componentId << "; ";
    }


    return 0;
}