// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_RESOURCEMANAGEMENT_BINARYPACKAGE_H
#define NOVELRT_INTEROP_RESOURCEMANAGEMENT_BINARYPACKAGE_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_BinaryPackage_Destroy(NrtBinaryPackageHandle package);

    NrtBinaryMemberMetadataVectorHandle Nrt_BinaryPackage_GetMemberMetadata(NrtBinaryPackageHandle package);

    NrtUint8VectorHandle Nrt_BinaryPackage_GetData(NrtBinaryPackageHandle package);

    NrtUuid Nrt_BinaryPackage_GetDatabaseHandle(NrtBinaryPackageHandle package);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_RESOURCEMANAGEMENT_BINARYPACKAGE_H
