#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include <algorithm>
#include <cassert>
#include <memory>
#include <unordered_map>
#include <tuple>
#include <vector>

#include "Engine/ECS/Archetype/Archetype.hpp"
#include "Engine/ECS/Component/Component.hpp"
#include "Engine/ECS/ComponentManager.hpp"
#include "Engine/ECS/Types.hpp"
#include "Engine/ECS/System/BaseSystem.hpp"

template <typename... Components>
class System : public BaseSystem
{
private:
    template <typename Last>
    static ComponentId computeComponentId();
    template <typename First, typename Second, typename... Args>
    static ArchetypeSignature computeSignature();
    template <typename T>
    static std::shared_ptr<T> parseRawComponent(std::map<ComponentId, std::shared_ptr<Component>> &rawComponents);
    static std::tuple<std::shared_ptr<Components>...> parseRawComponents(std::map<ComponentId, std::shared_ptr<Component>> &rawComponents);
    std::unordered_map<EntityId, std::tuple<std::shared_ptr<Components>...>> m_entitiesCacheMap;

    ArchetypeSignature m_componentsIds;
    virtual void notifyInit(EntityId entityId, std::map<ComponentId, std::shared_ptr<Component>> &components) override;
    virtual void notifyUpdate(const float &deltaTime) override;
    virtual void updateEntity(EntityId entityId, std::map<ComponentId, std::shared_ptr<Component>> components) override;
    virtual ArchetypeSignature getSignature() const override;

protected:
    virtual void init(EntityId entityId, std::tuple<std::shared_ptr<Components>...> components);
    virtual void update(const float &deltaTime, std::unordered_map<EntityId, std::tuple<std::shared_ptr<Components>...>> &entities) = 0;
    template <typename T>
    static std::shared_ptr<T> getComponent(std::tuple<std::shared_ptr<Components>...> components);

public:
    System();
};

template <typename... Components>
template <typename Last>
ComponentId System<Components...>::computeComponentId()
{
    return ComponentManager::getId<Last>();
}

template <typename... Components>
template <typename First, typename Second, typename... Args>
ArchetypeSignature System<Components...>::computeSignature()
{
    return ArchetypeSignature({computeComponentId<Components>()...});
}

template <typename... Components>
template <typename T>
inline std::shared_ptr<T> System<Components...>::parseRawComponent(std::map<ComponentId, std::shared_ptr<Component>> &rawComponents)
{
    assert(rawComponents.count(ComponentManager::getId<T>()) != 0 && "Invalid entities provided to this system");
    std::shared_ptr<Component> t = rawComponents.at(ComponentManager::getId<T>());
    return std::static_pointer_cast<T>(t);
}

template <typename... Components>
inline std::tuple<std::shared_ptr<Components>...> System<Components...>::parseRawComponents(std::map<ComponentId, std::shared_ptr<Component>> &rawComponents)
{
    return std::make_tuple(parseRawComponent<Components>(rawComponents)...);
}

template <typename... Components>
inline void System<Components...>::notifyInit(EntityId entityId, std::map<ComponentId, std::shared_ptr<Component>> &rawComponents)
{
    std::tuple<std::shared_ptr<Components>...> components = parseRawComponents(rawComponents);
    init(entityId, components);
}

template <typename... Components>
inline void System<Components...>::notifyUpdate(const float &deltaTime)
{
    update(deltaTime, m_entitiesCacheMap);
}

template <typename... Components>
inline void System<Components...>::updateEntity(EntityId entityId, std::map<ComponentId, std::shared_ptr<Component>> components)
{
    if (m_entitiesCacheMap.count(entityId) == 0)
    {
        m_entitiesCacheMap.emplace(entityId, parseRawComponents(components));
    }
}

template <typename... Components>
System<Components...>::System() : m_componentsIds(computeSignature<Components...>())
{
    std::sort(m_componentsIds.begin(), m_componentsIds.end());
}

template <typename... Components>
inline ArchetypeSignature System<Components...>::getSignature() const
{
    return m_componentsIds;
}

template <typename... Components>
inline void System<Components...>::init(EntityId entityId, std::tuple<std::shared_ptr<Components>...> components) {}

template <typename... Components>
template <typename T>
inline std::shared_ptr<T> System<Components...>::getComponent(std::tuple<std::shared_ptr<Components>...> components)
{
    return std::get<std::shared_ptr<T>>(components);
}

#endif // SYSTEM_H_INCLUDED
