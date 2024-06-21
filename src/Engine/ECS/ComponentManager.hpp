#ifndef COMPONENTMANAGER_H_INCLUDED
#define COMPONENTMANAGER_H_INCLUDED

#include <iostream>
#include <memory>
#include <type_traits>
#include <unordered_map>
#include <vector>

#include "Engine/ECS/Component/Component.hpp"
#include "Engine/ECS/Types.hpp"

class BaseComponentPool
{
};

template <typename T>
class ComponentPool : public BaseComponentPool
{
public:
    std::vector<std::shared_ptr<T>> components;
};

class ComponentManager
{
private:
    static ComponentId g_componentCount;
    template <typename T>
    static ComponentId _getId();
    ComponentManager() = default;
    std::unordered_map<int, std::shared_ptr<BaseComponentPool>> m_components;

public:
    template <typename T>
    static ComponentId getId();
    template <typename T>
    static ComponentId getId(T);
    static ComponentManager &getInstance();
    template <typename T>
    void addComponent(T *t);
    template <typename T>
    std::vector<std::shared_ptr<T>> &getComponents();
};

template <typename T>
inline ComponentId ComponentManager::_getId()
{
    static int componentId = ++g_componentCount;
    return componentId;
}

template <typename T>
inline ComponentId ComponentManager::getId()
{
    return _getId<std::remove_cv_t<std::remove_reference_t<T>>>();
}

template <typename T>
inline ComponentId ComponentManager::getId(T)
{
    return getId<T>();
}

template <typename T>
inline void ComponentManager::addComponent(T *t)
{
    ComponentId id = getId<T>();

    if (m_components.count(id) == 0)
    {
        m_components.emplace(id, std::make_shared<ComponentPool<T>>());
    }

    BaseComponentPool &rawPool = *m_components.at(id);

    ComponentPool<T> &componentPool = static_cast<ComponentPool<T> &>(rawPool);

    componentPool.components.push_back(std::shared_ptr<T>(t));
}

template <typename T>
inline std::vector<std::shared_ptr<T>> &ComponentManager::getComponents()
{
    BaseComponentPool &rawPool = *m_components.at(getId<T *>());
    return static_cast<ComponentPool<T> &>(rawPool).components;
}

#endif // COMPONENTMANAGER_H_INCLUDED