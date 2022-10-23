// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_RESOURCEMANAGEMENT_NRTRESOURCEMANAGEMENTTYPEDEFS_H
#define NOVELRT_INTEROP_RESOURCEMANAGEMENT_NRTRESOURCEMANAGEMENTTYPEDEFS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <stdint.h>

    typedef struct NrtBinaryMemberMetadata* NrtBinaryMemberMetadataHandle;
    typedef struct NrtBinaryPackage* NrtBinaryPackageHandle;
    typedef struct NrtResourceLoader* NrtResourceLoaderHandle;
    typedef struct NrtShaderMetadata* NrtShaderMetadataHandle;
    typedef struct NrtTextureMetadata* NrtTextureMetadataHandle;
    typedef struct NrtBinaryMemberMetadataVector* NrtBinaryMemberMetadataVectorHandle;
    typedef struct NrtUint8Vector* NrtUint8VectorHandle;
    typedef const struct NrtUuidFilePathMap* NrtUuidFilePathMapHandle;
    typedef const struct NrtFilePathUuidMap* NrtFilePathUuidMapHandle;

    typedef struct
    {
        uint8_t zero;
        uint8_t one;
        uint8_t two;
        uint8_t three;
        uint8_t four;
        uint8_t five;
        uint8_t six;
        uint8_t seven;
        uint8_t eight;
        uint8_t nine;
        uint8_t ten;
        uint8_t eleven;
        uint8_t twelve;
        uint8_t thirteen;
        uint8_t fourteen;
        uint8_t fifteen;
    } NrtUuid;

    typedef enum
    {
        NRT_BINTYPE_NULLORUNKNOWN = 0,
        NRT_BINTYPE_BOOLEAN = 1,
        NRT_BINTYPE_INT32 = 2,
        NRT_BINTYPE_INT64 = 3,
        NRT_BINTYPE_UINT32 = 4,
        NRT_BINTYPE_UINT64 = 5,
        NRT_BINTYPE_DOUBLE = 6,
        NRT_BINTYPE_STRING = 7,
        NRT_BINTYPE_BINARY = 8
    } NrtBinaryDataType;

    typedef struct
    {
        const char* name;
        NrtBinaryDataType type;
        size_t location;
        size_t sizeOfTypeInBytes;
        size_t length;
        size_t sizeOfSerialisedDataInBytes;
    } NrtBinaryMemberMetadataCreateInfo;

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_RESOURCEMANAGEMENT_NRTRESOURCEMANAGEMENTTYPEDEFS_H
