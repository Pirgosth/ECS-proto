#ifndef RENDERSYSTEM_H_INCLUDED
#define RENDERSYSTEM_H_INCLUDED

#include <tuple>

#include <SFML/Graphics.hpp>

#include "../Components/Sprite.hpp"
#include "../Components/Transform.hpp"
#include "../System.hpp"

class RenderSystem : public System<Sprite, Transform>
{
private:
    sf::RenderWindow &m_window;
    static void insertSorted(std::vector<std::tuple<std::shared_ptr<Sprite>, std::shared_ptr<Transform>>> &result, std::tuple<std::shared_ptr<Sprite>, std::shared_ptr<Transform>> toInsert);

public:
    RenderSystem(sf::RenderWindow &window);
    virtual void update(ArchetypeGraph::CompositeArchetypeView<std::shared_ptr<Sprite>, std::shared_ptr<Transform>> &entities) override;
};

#endif // RENDERSYSTEM_H_INCLUDED