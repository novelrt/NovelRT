// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/ResourceManagement/NrtResourceManagement.h>
#include <NovelRT/ResourceManagement/ResourceManagement.h>

using namespace NovelRT::ResourceManagement;

extern "C"
{
    NrtInt16VectorHandle Nrt_Int16Vector_Create()
    {
        return reinterpret_cast<NrtInt16VectorHandle>(new std::vector<int16_t>());
    }

    NrtResult Nrt_Int16Vector_Destroy(NrtInt16VectorHandle vector)
    {
        if (vector == nullptr)
        {
            Nrt_setErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        delete reinterpret_cast<std::vector<int16_t>*>(vector);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_Int16Vector_Insert(NrtInt16VectorHandle vector, int16_t value)
    {
        if (vector == nullptr)
        {
            Nrt_setErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        reinterpret_cast<std::vector<int16_t>*>(vector)->emplace_back(value);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_Int16Vector_Remove(NrtInt16VectorHandle vector, int16_t value)
    {
        if (vector == nullptr)
        {
            Nrt_setErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto vecPtr = reinterpret_cast<std::vector<int16_t>*>(vector);
        size_t lengthBefore = vecPtr->size();
        static_cast<void>(std::remove(vecPtr->begin(), vecPtr->end(), value));

        if (vecPtr->size() == lengthBefore)
        {
            return NRT_DATA_NOT_MODIFIED;
        }

        return NRT_SUCCESS;
    }
}
