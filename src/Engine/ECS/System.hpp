#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include <algorithm>
#include <memory>
#include <vector>

#include "Engine/ECS/Component.hpp"
#include "Engine/ECS/ComponentManager.hpp"

template <typename Last>
std::vector<int> computeComponentsIds()
{
    return std::vector<int>{ComponentManager::getId<Last>()};
}

template <typename First, typename Second, typename... Args>
std::vector<int> computeComponentsIds()
{
    std::vector<int> previousIds = computeComponentsIds<Second, Args...>();
    previousIds.push_back(ComponentManager::getId<First>());
    return previousIds;
}

template <typename... Components>
class System
{
private:
    std::vector<std::shared_ptr<Component>> m_components;
    std::vector<int> m_componentsIds;

public:
    System();
    const std::vector<int> &getComponentIds() const;
};

template <typename... Components>
System<Components...>::System() : m_componentsIds(computeComponentsIds<Components...>())
{
    std::sort(m_componentsIds.begin(), m_componentsIds.end());
}

template <typename... Components>
inline const std::vector<int> &System<Components...>::getComponentIds() const
{
    return m_componentsIds;
}

#endif // SYSTEM_H_INCLUDED
