// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/ResourceManagement/NrtResourceManagement.h>
#include <NovelRT/ResourceManagement/ResourceManagement.h>

using namespace NovelRT::ResourceManagement;

extern "C"
{
    NrtInt16VectorHandle Nrt_AudioMetadata_GetProcessedAudioFrames(NrtAudioMetadataHandle audioMetadata)
    {
        return reinterpret_cast<NrtInt16VectorHandle>(
            &reinterpret_cast<AudioMetadata*>(audioMetadata)->processedAudioFrames);
    }

    int32_t Nrt_AudioMetadata_GetChannelCount(NrtAudioMetadataHandle audioMetadata)
    {
        return reinterpret_cast<AudioMetadata*>(audioMetadata)->channelCount;
    }

    int32_t Nrt_AudioMetadata_GetSampleRate(NrtAudioMetadataHandle audioMetadata)
    {
        return reinterpret_cast<AudioMetadata*>(audioMetadata)->sampleRate;
    }

    NrtUuid Nrt_AudioMetadata_GetDatabaseHandle(NrtAudioMetadataHandle audioMetadata)
    {
        return *reinterpret_cast<NrtUuid*>(&reinterpret_cast<AudioMetadata*>(audioMetadata)->databaseHandle);
    }
}