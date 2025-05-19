// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_RESOURCEMANAGEMENT_INTEROP_AUDIOMETADATA_H
#define NOVELRT_RESOURCEMANAGEMENT_INTEROP_AUDIOMETADATA_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtInt16VectorHandle Nrt_AudioMetadata_GetProcessedAudioFrames(NrtAudioMetadataHandle audioMetadata);

    int32_t Nrt_AudioMetadata_GetChannelCount(NrtAudioMetadataHandle audioMetadata);

    int32_t Nrt_AudioMetadata_GetSampleRate(NrtAudioMetadataHandle audioMetadata);

    NrtUuid Nrt_AudioMetadata_GetDatabaseHandle(NrtAudioMetadataHandle audioMetadata);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_RESOURCEMANAGEMENT_INTEROP_AUDIOMETADATA_H
