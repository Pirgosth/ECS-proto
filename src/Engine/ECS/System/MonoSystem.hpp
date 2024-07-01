#ifndef MONOSYSTEM_H_INCLUDED
#define MONOSYSTEM_H_INCLUDED

#include <algorithm>
#include <memory>
#include <tuple>
#include <vector>

#include "Engine/ECS/Archetype/Archetype.hpp"
#include "Engine/ECS/Component/Component.hpp"
#include "Engine/ECS/ComponentManager.hpp"
#include "Engine/ECS/Types.hpp"
#include "Engine/ECS/System/System.hpp"

//TODO: Complete rework or abandon of this class

template <typename SingleComponent>
class MonoSystem : public System<SingleComponent>
{
protected:
    virtual void update(const float &deltaTime, std::unordered_map<EntityId, std::tuple<std::shared_ptr<SingleComponent>>> &entities) override;
    virtual void update(std::map<EntityId, std::shared_ptr<SingleComponent>> entities) = 0;
};


template <typename SingleComponent>
inline void MonoSystem<SingleComponent>::update(const float &deltaTime, std::unordered_map<EntityId, std::tuple<std::shared_ptr<SingleComponent>>> &entities)
{
    std::map<EntityId, std::shared_ptr<SingleComponent>> monoEntities;
    for (auto [id, components]: entities)
    {
        auto [component] = components;
        monoEntities.emplace(id, component);
    }
    update(deltaTime, monoEntities);
}

#endif // MONOSYSTEM_H_INCLUDED
