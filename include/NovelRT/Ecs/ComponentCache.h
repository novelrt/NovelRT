// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ECS_COMPONENTCACHE_H
#define NOVELRT_ECS_COMPONENTCACHE_H

#include "EcsUtils.h"
#include "ComponentBuffer.h"

namespace NovelRT::Ecs
{
    class ComponentCache
    {
        public:
        template<typename T>
        static ComponentBuffer<T>& GetComponentBuffer(size_t catalogueId) noexcept
        {
            static std::vector<ComponentBuffer<T>> buffer = std::vector<ComponentBuffer<T>>();
            while (buffer.size() <= catalogueId)
            {
                buffer.push_back(ComponentBuffer<T>());
            }

            return buffer.at(catalogueId);
        }
    };
}

#endif //!NOVELRT_ECS_COMPONENTCACHE_H