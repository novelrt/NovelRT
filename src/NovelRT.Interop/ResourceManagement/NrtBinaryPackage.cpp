// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/ResourceManagement/NrtResourceManagement.h>
#include <NovelRT/ResourceManagement/ResourceManagement.h>
#include <NovelRT.Interop/NrtErrorHandling.h>

using namespace NovelRT::ResourceManagement;

extern "C"
{
    NrtResult Nrt_BinaryPackage_Destroy(NrtBinaryPackageHandle package)
    {
        if (package == nullptr)
        {
            Nrt_setErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        delete reinterpret_cast<BinaryPackage*>(package);

        return NRT_SUCCESS;
    }

    NrtBinaryMemberMetadataVectorHandle Nrt_BinaryPackage_GetMemberMetadata(NrtBinaryPackageHandle package)
    {
        return reinterpret_cast<NrtBinaryMemberMetadataVectorHandle>(
            &reinterpret_cast<BinaryPackage*>(package)->memberMetadata);
    }

    NrtUint8VectorHandle Nrt_BinaryPackage_GetData(NrtBinaryPackageHandle package)
    {
        return reinterpret_cast<NrtUint8VectorHandle>(&reinterpret_cast<BinaryPackage*>(package)->data);
    }

    NrtUuid Nrt_BinaryPackage_GetDatabaseHandle(NrtBinaryPackageHandle package)
    {
        return *reinterpret_cast<NrtUuid*>(&reinterpret_cast<BinaryPackage*>(package)->databaseHandle);
    }
}
