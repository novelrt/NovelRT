// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/EcsUtils.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/Ecs/NrtEntityIdVector.h>

#include <algorithm>
#include <vector>

using namespace NovelRT::Ecs;

extern "C"
{
    NrtEntityIdVectorHandle Nrt_EntityIdVector_Create()
    {
        return reinterpret_cast<NrtEntityIdVectorHandle>(new std::vector<EntityId>());
    }

    NrtResult Nrt_EntityIdVector_Insert(NrtEntityIdVectorHandle vector, NrtEntityId entity)
    {
        if (vector == nullptr)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        reinterpret_cast<std::vector<EntityId>*>(vector)->emplace_back(entity);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_EntityIdVector_Remove(NrtEntityIdVectorHandle vector, NrtEntityId entity)
    {
        if (vector == nullptr)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        auto vecPtr = reinterpret_cast<std::vector<EntityId>*>(vector);
        size_t lengthBefore = vecPtr->size();
        static_cast<void>(std::remove_if(vecPtr->begin(), vecPtr->end(),
                                         [=](EntityId val) { return val == static_cast<NovelRT::Atom>(entity); }));

        if (vecPtr->size() == lengthBefore)
        {
            return NRT_DATA_NOT_MODIFIED;
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_EntityIdVector_Delete(NrtEntityIdVectorHandle vector)
    {
        if (vector == nullptr)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        delete reinterpret_cast<std::vector<EntityId>*>(vector);

        return NRT_SUCCESS;
    }
}
