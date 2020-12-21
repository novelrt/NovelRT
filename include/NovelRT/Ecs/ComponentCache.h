// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ECS_COMPONENTCACHE_H
#define NOVELRT_ECS_COMPONENTCACHE_H

#include "EcsUtils.h"
#include "ComponentBuffer.h"
#include <unordered_map>

namespace NovelRT::Ecs
{
    class ComponentCache
    {
        private:
        std::unordered_map<ComponentTypeId, void*, AtomHashFunction> _componentMap;

        size_t _poolSize;

        public:
        ComponentCache(size_t poolSize) noexcept : _componentMap(std::unordered_map<ComponentTypeId, void*, AtomHashFunction>{}), _poolSize(poolSize)
        {

        }

        template<typename T>
        void RegisterComponentType()
        {
            auto ptr = malloc(sizeof(ComponentBuffer<T>));
            
            if (ptr == nullptr)
            {
                throw std::runtime_error("Out of memory");
            }

            *reinterpret_cast<ComponentBuffer<T>*>(ptr) = ComponentBuffer<T>(_poolSize);
            _componentMap.emplace(newRecord.componentTypeId, ptr);
        }

        template<typename T>
        ComponentBuffer<T>& GetComponentBuffer() noexcept
        {
            return *reinterpret_cast<ComponentBuffer<T>*>(_componentMap.at(GetComponentTypeId<T>()));
        }

        ~ComponentCache() noexcept
        {
            for (auto&& pair : _componentMap)
            {
                free(pair.second);
            }
        }
    };
}

#endif //!NOVELRT_ECS_COMPONENTCACHE_H