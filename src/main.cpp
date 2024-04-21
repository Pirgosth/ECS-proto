#include <iostream>

#include <SFML/Graphics.hpp>

#include "Engine/ECS/Engine.hpp"
#include "Engine/ECS/System.hpp"

class Health : public Component
{
public:
    int health;

    Health(int health) : health(health) {}
};

class HealthSystem : public System<Health>
{
    virtual void update(std::map<EntityId, std::tuple<std::shared_ptr<Health>>> entities) override
    {
        std::cout << "Update from HealthSystem !" << std::endl;
        for (auto [entity, components] : entities)
        {
            auto healthComponent = getComponent<Health>(components);
            healthComponent->health--;
            std::cout << entity << "; " << healthComponent->health << std::endl;
        }
    }
}; 

int main()
{
    Engine engine;
    engine.registerSystem(new HealthSystem());

    engine.addComponent(engine.makeEntity(), new Health(60));
    engine.addComponent(engine.makeEntity(), new Health(150));
    engine.addComponent(engine.makeEntity(), new Health(80));

    engine.update();
    engine.update();

    return 0;
}
