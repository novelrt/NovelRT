// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/NrtEntityIdVector.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT/Ecs/Ecs.h>

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
            Nrt_setErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        reinterpret_cast<std::vector<EntityId>*>(vector)->emplace_back(entity);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_EntityIdVector_Remove(NrtEntityIdVectorHandle vector, NrtEntityId entity)
    {
        if (vector == nullptr)
        {
            Nrt_setErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto vecPtr = reinterpret_cast<std::vector<EntityId>*>(vector);
        size_t lengthBefore = vecPtr->size();
        static_cast<void>(std::remove_if(vecPtr->begin(), vecPtr->end(),
                                         [=](EntityId val) { return val == static_cast<NovelRT::Core::Atom>(entity); }));

        if (vecPtr->size() == lengthBefore)
        {
            return NRT_DATA_NOT_MODIFIED;
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_EntityIdVector_Destroy(NrtEntityIdVectorHandle vector)
    {
        if (vector == nullptr)
        {
            Nrt_setErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        delete reinterpret_cast<std::vector<EntityId>*>(vector);

        return NRT_SUCCESS;
    }
}
