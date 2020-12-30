// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ECS_COMPONENTCACHE_H
#define NOVELRT_ECS_COMPONENTCACHE_H

#include <unordered_map>
#include <functional>
#include <vector>
#include "ComponentBuffer.h"
#include "EcsUtils.h"
#include "../Utilities/Event.h"
#include "../Exceptions/OutOfMemoryException.h"

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
        ComponentCache(size_t poolSize) noexcept;

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
            _bufferPrepEvent += [bufferPtr] (auto arg) { bufferPtr->PrepComponentBufferForFrame(arg); };
            _componentMap.emplace(GetComponentTypeId<T>(), ptr);
        }

        template<typename T>
        [[nodiscard]] ComponentBuffer<T>& GetComponentBuffer() noexcept
        {
            return *reinterpret_cast<ComponentBuffer<T>*>(_componentMap.at(GetComponentTypeId<T>()));
        }

        void PrepAllBuffersForNextFrame(const std::vector<EntityId>& entitiesToDelete) noexcept;

        ~ComponentCache() noexcept;

    };
}

#endif //!NOVELRT_ECS_COMPONENTCACHE_H