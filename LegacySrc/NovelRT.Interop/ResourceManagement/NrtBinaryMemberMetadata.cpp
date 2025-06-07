// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/ResourceManagement/NrtResourceManagement.h>
#include <NovelRT/ResourceManagement/ResourceManagement.h>

using namespace NovelRT::ResourceManagement;

extern "C"
{
    NrtBinaryMemberMetadataHandle Nrt_BinaryMemberMetadata_Create(NrtBinaryMemberMetadataCreateInfo createInfo)
    {
        return reinterpret_cast<NrtBinaryMemberMetadataHandle>(new BinaryMemberMetadata{
            std::string(createInfo.name), static_cast<BinaryDataType>(createInfo.type), createInfo.location,
            createInfo.sizeOfTypeInBytes, createInfo.length, createInfo.sizeOfSerialisedDataInBytes});
    }

    NrtResult Nrt_BinaryMemberMetadata_Destroy(NrtBinaryMemberMetadataHandle memberMetadata)
    {
        if (memberMetadata == nullptr)
        {
            Nrt_setErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        delete reinterpret_cast<BinaryMemberMetadata*>(memberMetadata);

        return NRT_SUCCESS;
    }

    const char* Nrt_BinaryMemberMetadata_GetName(NrtBinaryMemberMetadataHandle memberMetadata)
    {
        return reinterpret_cast<BinaryMemberMetadata*>(memberMetadata)->name.c_str();
    }

    NrtBinaryDataType Nrt_BinaryMemberMetadata_GetBinaryDataType(NrtBinaryMemberMetadataHandle memberMetadata)
    {
        return static_cast<NrtBinaryDataType>(reinterpret_cast<BinaryMemberMetadata*>(memberMetadata)->type);
    }

    size_t Nrt_BinaryMemberMetadata_GetDataLocation(NrtBinaryMemberMetadataHandle memberMetadata)
    {
        return reinterpret_cast<BinaryMemberMetadata*>(memberMetadata)->location;
    }

    size_t Nrt_BinaryMemberMetadata_GetSizeOfTypeInBytes(NrtBinaryMemberMetadataHandle memberMetadata)
    {
        return reinterpret_cast<BinaryMemberMetadata*>(memberMetadata)->sizeOfTypeInBytes;
    }

    size_t Nrt_BinaryMemberMetadata_GetLength(NrtBinaryMemberMetadataHandle memberMetadata)
    {
        return reinterpret_cast<BinaryMemberMetadata*>(memberMetadata)->length;
    }

    size_t Nrt_BinaryMemberMetadata_GetSizeOfSerialisedDataInBytes(NrtBinaryMemberMetadataHandle memberMetadata)
    {
        return reinterpret_cast<BinaryMemberMetadata*>(memberMetadata)->sizeOfSerialisedDataInBytes;
    }
}
