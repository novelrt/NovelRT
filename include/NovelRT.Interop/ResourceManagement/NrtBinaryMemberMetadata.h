// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_RESOURCEMANAGEMENT_BINARYMEMBERMETADATA_H
#define NOVELRT_INTEROP_RESOURCEMANAGEMENT_BINARYMEMBERMETADATA_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtBinaryMemberMetadataHandle Nrt_BinaryMemberMetadata_Create(NrtBinaryMemberMetadataCreateInfo createInfo);

    NrtResult Nrt_BinaryMemberMetadata_Destroy(NrtBinaryMemberMetadataHandle memberMetadata);

    const char* Nrt_BinaryMemberMetadata_GetName(NrtBinaryMemberMetadataHandle memberMetadata);

    NrtBinaryDataType Nrt_BinaryMemberMetadata_GetBinaryDataType(NrtBinaryMemberMetadataHandle memberMetadata);

    size_t Nrt_BinaryMemberMetadata_GetDataLocation(NrtBinaryMemberMetadataHandle memberMetadata);

    size_t Nrt_BinaryMemberMetadata_GetSizeOfTypeInBytes(NrtBinaryMemberMetadataHandle memberMetadata);

    size_t Nrt_BinaryMemberMetadata_GetLength(NrtBinaryMemberMetadataHandle memberMetadata);

    size_t Nrt_BinaryMemberMetadata_GetSizeOfSerialisedDataInBytes(NrtBinaryMemberMetadataHandle memberMetadata);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_RESOURCEMANAGEMENT_BINARYMEMBERMETADATA_H
