// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/ResourceManagement/NrtResourceManagement.h>
#include <NovelRT/ResourceManagement/ResourceManagement.h>

using namespace NovelRT::ResourceManagement;

extern "C"
{
    NrtResult Nrt_UuidFilePathMap_Indexer(NrtUuidFilePathMapHandle map, NrtUuid id, const char** outFilePath)
    {
        if (map == nullptr)
        {
            Nrt_setErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outFilePath == nullptr)
        {
            Nrt_setErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        try
        {
            std::string pathString = reinterpret_cast<const std::map<uuids::uuid, std::filesystem::path>*>(map)
                                         ->at(*reinterpret_cast<uuids::uuid*>(&id))
                                         .string();
            char* returnPtr = nullptr;

            size_t length = pathString.length() + 1;
            returnPtr = static_cast<char*>(malloc(length));
            strcpy(returnPtr, pathString.c_str());

            *outFilePath = returnPtr;
        }
        catch (const std::out_of_range&)
        {
            Nrt_setErrMsgIsArgumentOutOfRangeInternal();
            return NRT_FAILURE_ARGUMENT_OUT_OF_RANGE;
        }

        return NRT_SUCCESS;
    }
}
