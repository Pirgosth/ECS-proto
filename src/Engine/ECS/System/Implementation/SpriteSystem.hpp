#include "Engine/ECS/System/MonoSystem.hpp"
#include "Engine/ECS/Component/Sprite.hpp"

class SpriteSystem : public MonoSystem<Sprite>
{
private:
    sf::RenderWindow &m_window;
    virtual void update(std::map<EntityId, std::shared_ptr<Sprite>> entities) override;

public:
    SpriteSystem(sf::RenderWindow &window);
};