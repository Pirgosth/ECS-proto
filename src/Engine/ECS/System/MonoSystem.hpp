#ifndef MONOSYSTEM_H_INCLUDED
#define MONOSYSTEM_H_INCLUDED

#include <algorithm>
#include <memory>
#include <tuple>
#include <vector>

#include "Engine/ECS/Archetype/Archetype.hpp"
#include "Engine/ECS/Component.hpp"
#include "Engine/ECS/ComponentManager.hpp"
#include "Engine/ECS/Types.hpp"
#include "Engine/ECS/System/BaseSystem.hpp"

template <typename SingleComponent>
class MonoSystem : public BaseSystem
{
private:
    static ArchetypeSignature computeSignature();

    ArchetypeSignature m_componentsIds;
    virtual void notifyUpdate(std::vector<Archetype *> archetypes) override;
    virtual ArchetypeSignature getSignature() const override;
    std::shared_ptr<SingleComponent> parseRawComponent(std::map<ComponentId, std::shared_ptr<Component>> rawComponents);

protected:
    virtual void update(std::map<EntityId, std::shared_ptr<SingleComponent>> entities) = 0;

public:
    MonoSystem();
};

template <typename SingleComponent>
inline ArchetypeSignature MonoSystem<SingleComponent>::computeSignature()
{
    return {ComponentManager::getId<SingleComponent>()};
}

template <typename SingleComponent>
inline void MonoSystem<SingleComponent>::notifyUpdate(std::vector<Archetype *> archetypes)
{
    std::map<EntityId, std::shared_ptr<SingleComponent>> entites;
    for (auto archetype : archetypes)
    {
        for (auto [entityId, rawComponents] : archetype->getEntities())
            entites.emplace(entityId, parseRawComponent(rawComponents));
    }
    update(entites);
}

template <typename SingleComponent>
inline ArchetypeSignature MonoSystem<SingleComponent>::getSignature() const
{
    return m_componentsIds;
}

template <typename SingleComponent>
inline std::shared_ptr<SingleComponent> MonoSystem<SingleComponent>::parseRawComponent(std::map<ComponentId, std::shared_ptr<Component>> rawComponents)
{
    std::shared_ptr<Component> t = rawComponents.at(ComponentManager::getId<SingleComponent>());
    return std::static_pointer_cast<SingleComponent>(t);
}

template <typename SingleComponent>
inline MonoSystem<SingleComponent>::MonoSystem(): m_componentsIds(computeSignature())
{
}

#endif // MONOSYSTEM_H_INCLUDED
