// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/ResourceManagement/NrtResourceManagement.h>
#include <NovelRT/ResourceManagement/ResourceManagement.h>
#include <NovelRT.Interop/NrtErrorHandling.h>

using namespace NovelRT::ResourceManagement;

extern "C"
{
    NrtUint8VectorHandle Nrt_Uint8Vector_Create()
    {
        return reinterpret_cast<NrtUint8VectorHandle>(new std::vector<uint8_t>());
    }

    NrtResult Nrt_Uint8Vector_Destroy(NrtUint8VectorHandle vector)
    {
        if (vector == nullptr)
        {
            Nrt_setErrIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        delete reinterpret_cast<std::vector<uint8_t>*>(vector);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_Uint8Vector_Insert(NrtUint8VectorHandle vector, uint8_t value)
    {
        if (vector == nullptr)
        {
            Nrt_setErrIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        reinterpret_cast<std::vector<uint8_t>*>(vector)->emplace_back(value);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_Uint8Vector_Remove(NrtUint8VectorHandle vector, uint8_t value)
    {
        if (vector == nullptr)
        {
            Nrt_setErrIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto vecPtr = reinterpret_cast<std::vector<uint8_t>*>(vector);
        size_t lengthBefore = vecPtr->size();
        static_cast<void>(std::remove(vecPtr->begin(), vecPtr->end(), value));

        if (vecPtr->size() == lengthBefore)
        {
            return NRT_DATA_NOT_MODIFIED;
        }

        return NRT_SUCCESS;
    }
}