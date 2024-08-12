#include "Systems/DummySystem.hpp"

void DummySystem::update(ArchetypeGraph::CompositeArchetypeView<std::shared_ptr<int>> &entities)
{
    for (auto [i] : entities)
    {
        std::cout << *i << std::endl;
    }
}