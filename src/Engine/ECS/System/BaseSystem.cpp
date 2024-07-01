#include "BaseSystem.hpp"

bool BaseSystem::canHandle(ArchetypeSignature signature)
{
    const auto systemSignature = getSignature();
    for (auto componentId: systemSignature)
    {
        if (std::find(signature.begin(), signature.end(), componentId) == signature.end())
            return false;
    }

    return true;
}