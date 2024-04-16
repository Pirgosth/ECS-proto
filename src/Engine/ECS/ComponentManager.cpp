#include "ComponentManager.hpp"

int ComponentManager::g_componentCount = 0;

ComponentManager &ComponentManager::getInstance()
{
    static ComponentManager instance;
    return instance;
}
