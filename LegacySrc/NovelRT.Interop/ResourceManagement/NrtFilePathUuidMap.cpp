// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/ResourceManagement/NrtResourceManagement.h>
#include <NovelRT/ResourceManagement/ResourceManagement.h>

using namespace NovelRT::ResourceManagement;

extern "C"
{
    NrtResult Nrt_FilePathUuidMap_Indexer(NrtFilePathUuidMapHandle map, const char* filePath, NrtUuid* outUuid)
    {
        if (map == nullptr)
        {
            Nrt_setErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (filePath == nullptr || outUuid == nullptr)
        {
            Nrt_setErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        try
        {
            *outUuid = *reinterpret_cast<const NrtUuid*>(
                &reinterpret_cast<const std::map<std::filesystem::path, uuids::uuid>*>(map)->at(
                    std::filesystem::path(filePath)));
        }
        catch (const std::out_of_range&)
        {
            Nrt_setErrMsgIsArgumentOutOfRangeInternal();
            return NRT_FAILURE_ARGUMENT_OUT_OF_RANGE;
        }

        return NRT_SUCCESS;
    }
}