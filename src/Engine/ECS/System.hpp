#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include <algorithm>
#include <memory>
#include <tuple>
#include <vector>

#include "Engine/ECS/Archetype.hpp"
#include "Engine/ECS/Component.hpp"
#include "Engine/ECS/ComponentManager.hpp"
#include "Engine/ECS/Types.hpp"

template <typename Last>
ArchetypeSignature computeComponentsIds()
{
    return ArchetypeSignature{ComponentManager::getId<Last>()};
}

template <typename First, typename Second, typename... Args>
ArchetypeSignature computeComponentsIds()
{
    auto previousIds = computeComponentsIds<Second, Args...>();
    previousIds.push_back(ComponentManager::getId<First>());
    return previousIds;
}

class Engine;

class BaseSystem
{
    friend Engine;

protected:
    virtual void notifyUpdate(std::vector<Archetype> archetypes) = 0;
    virtual ArchetypeSignature getSignature() const = 0;
};

template <typename T>
std::shared_ptr<T> parseRawComponent(std::map<ComponentId, std::shared_ptr<Component>> rawComponents)
{
    std::shared_ptr<Component> t = rawComponents.at(ComponentManager::getId<T>());
    return std::static_pointer_cast<T>(t);
}

template <typename... Components>
class System : public BaseSystem
{
private:
    std::vector<std::shared_ptr<Component>> m_components;
    ArchetypeSignature m_componentsIds;
    virtual void notifyUpdate(std::vector<Archetype> archetypes) override;
    virtual ArchetypeSignature getSignature() const override;
    static std::tuple<std::shared_ptr<Components>...> parseRawComponents(std::map<ComponentId, std::shared_ptr<Component>> rawComponents);

protected:
    virtual void update(std::map<EntityId, std::tuple<std::shared_ptr<Components>...>> entities) = 0;
    template <typename T>
    static std::shared_ptr<T> getComponent(std::tuple<std::shared_ptr<Components>...> components);

public:
    System();
};

template <typename... Components>
inline void System<Components...>::notifyUpdate(std::vector<Archetype> archetypes)
{
    for (auto archetype : archetypes)
    {
        std::map<EntityId, std::tuple<std::shared_ptr<Components>...>> entites;

        for (auto [entityId, rawComponents] : archetype.getEntities())
            entites.emplace(entityId, parseRawComponents(rawComponents));

        update(entites);
    }
}

template <typename... Components>
System<Components...>::System() : m_componentsIds(computeComponentsIds<Components...>())
{
    std::sort(m_componentsIds.begin(), m_componentsIds.end());
}

template <typename... Components>
inline ArchetypeSignature System<Components...>::getSignature() const
{
    return m_componentsIds;
}

template <typename... Components>
inline std::tuple<std::shared_ptr<Components>...> System<Components...>::parseRawComponents(std::map<ComponentId, std::shared_ptr<Component>> rawComponents)
{
    return std::make_tuple(parseRawComponent<Components>(rawComponents)...);
}

template <typename... Components>
template <typename T>
inline std::shared_ptr<T> System<Components...>::getComponent(std::tuple<std::shared_ptr<Components>...> components)
{
    return std::get<std::shared_ptr<T>>(components);
}

#endif // SYSTEM_H_INCLUDED
