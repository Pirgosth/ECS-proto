#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include <tuple>

#include "ArchetypeGraph.hpp"

class ECS;

class BaseSystem
{
    friend ECS;
    virtual void notifyUpdate(ArchetypeGraph &graph) = 0;
};

template <typename... Components>
class System: public BaseSystem
{
private:
    virtual void notifyUpdate(ArchetypeGraph &graph) override;
public:
    virtual void update(ArchetypeGraph::CompositeArchetypeView<std::shared_ptr<Components>...> &entities) = 0;
};

template <typename... Components>
inline void System<Components...>::notifyUpdate(ArchetypeGraph &graph)
{
    auto entities = graph.query<std::shared_ptr<Components>...>();
    update(entities);
}

#endif // SYSTEM_H_INCLUDED
