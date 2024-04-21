#include "ComponentManager.hpp"

ComponentId ComponentManager::g_componentCount = 0u;

ComponentManager &ComponentManager::getInstance()
{
    static ComponentManager instance;
    return instance;
}
