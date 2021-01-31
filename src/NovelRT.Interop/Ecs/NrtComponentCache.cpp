// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/NrtComponentCache.h>
#include <NovelRT/Ecs/ComponentCache.h>

using namespace NovelRT::Ecs;

extern "C"
{
    NrtComponentCache Nrt_ComponentCache_Create(size_t poolSize)
    {
        return reinterpret_cast<NrtComponentCache>(new ComponentCache(poolSize));
    }

    NrtResult Nrt_ComponentCache_GetComponentBufferById(NrtComponentCache componentCache,
                                                        NrtComponentTypeId id,
                                                        NrtComponentBufferMemoryContainer* outputResult)
    {
        if (componentCache == nullptr || outputResult == nullptr)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        *outputResult = reinterpret_cast<NrtComponentBufferMemoryContainer>(
            reinterpret_cast<ComponentCache*>(componentCache)->GetComponentBufferById(id).get());

        return NRT_SUCCESS;
    }

    void Nrt_ComponentCache_PrepAllBuffersForNextFrame(NrtComponentCache componentCache,
                                                       NrtEntityIdVector entitiesToDelete)
    {
        reinterpret_cast<ComponentCache*>(componentCache)
            ->PrepAllBuffersForNextFrame(*reinterpret_cast<std::vector<EntityId>*>(entitiesToDelete));
    }

    NrtResult Nrt_ComponentCache_Delete(NrtComponentCache componentCache)
    {
        if (componentCache == nullptr)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        delete reinterpret_cast<ComponentCache*>(componentCache);

        return NRT_SUCCESS;
    }
}