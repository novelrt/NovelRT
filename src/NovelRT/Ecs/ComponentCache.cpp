// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT/Ecs/ComponentCache.h>

namespace NovelRT::Ecs
{   
    ComponentCache::ComponentCache(size_t poolSize) noexcept : _componentMap(std::unordered_map<ComponentTypeId, void*, AtomHashFunction>{}), _poolSize(poolSize), _bufferPrepEvent(Utilities::Event<const std::vector<EntityId>&>())
    {

    }

    void ComponentCache::PrepAllBuffersForNextFrame(const std::vector<EntityId>& entitiesToDelete) noexcept
    {
        _bufferPrepEvent(entitiesToDelete);
    }

    ComponentCache::~ComponentCache() noexcept
    {
        for (auto&& destructor : _destructorFunctions)
        {
            destructor();
        }
        
        for (auto&& pair : _componentMap)
        {
            free(pair.second);
        }
    }
}