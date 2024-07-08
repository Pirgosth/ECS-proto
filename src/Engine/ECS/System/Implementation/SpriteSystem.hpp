#include "Engine/ECS/System/System.hpp"
#include "Engine/ECS/Component/Sprite.hpp"
#include "Engine/ECS/Component/Transform.hpp"

class SpriteSystem : public System<Transform, Sprite>
{
private:
    sf::RenderWindow &m_window;
    virtual void update(const float &deltaTime, std::unordered_map<EntityId, std::tuple<std::shared_ptr<Transform>, std::shared_ptr<Sprite>>> &entities) override;
    virtual void draw(const sf::RenderWindow &window, std::unordered_map<EntityId, std::tuple<std::shared_ptr<Transform>, std::shared_ptr<Sprite>>> &entities) override;

public:
    SpriteSystem(sf::RenderWindow &window);
};