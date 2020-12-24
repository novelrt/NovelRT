// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ECS_COMPONENTCACHE_H
#define NOVELRT_ECS_COMPONENTCACHE_H

#include "EcsUtils.h"
#include "ComponentBuffer.h"
#include "../Exceptions/OutOfMemoryException.h"
#include <unordered_map>
#include "../Utilities/Event.h"

namespace NovelRT::Ecs
{
    class ComponentCache
    {
        private:
        std::unordered_map<ComponentTypeId, void*, AtomHashFunction> _componentMap;
        std::vector<std::function<void()>> _destructorFunctions;
        size_t _poolSize;
        Utilities::Event<const std::vector<EntityId>&> _bufferPrepEvent;
        

        public:
        ComponentCache(size_t poolSize) noexcept : _componentMap(std::unordered_map<ComponentTypeId, void*, AtomHashFunction>{}), _poolSize(poolSize), _bufferPrepEvent(Utilities::Event<const std::vector<EntityId>&>())
        {

        }

        template<typename T>
        void RegisterComponentType(T deleteInstructionState)
        {
            auto ptr = malloc(sizeof(ComponentBuffer<T>));
            
            if (ptr == nullptr)
            {
                throw Exceptions::OutOfMemoryException("Could not allocate component buffer for new component registration!");
            }
            auto bufferPtr = new(ptr)ComponentBuffer<T>(_poolSize, deleteInstructionState);
            _destructorFunctions.push_back([bufferPtr](){bufferPtr->~ComponentBuffer<T>();});
            _bufferPrepEvent += [bufferPtr] (auto arg) { bufferPtr->PrepComponentBuffersForFrame(arg); };
            _componentMap.emplace(GetComponentTypeId<T>(), ptr);
        }

        template<typename T>
        [[nodiscard]] ComponentBuffer<T>& GetComponentBuffer() noexcept
        {
            return *reinterpret_cast<ComponentBuffer<T>*>(_componentMap.at(GetComponentTypeId<T>()));
        }

        void PrepAllBuffersForNextFrame(const std::vector<EntityId>& entitiesToDelete) noexcept
        {
            _bufferPrepEvent(entitiesToDelete);
        }

        ~ComponentCache() noexcept
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
    };
}

#endif //!NOVELRT_ECS_COMPONENTCACHE_H