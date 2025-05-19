// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_RESOURCEMANAGEMENT_FILEPATHUUIDMAP_H
#define NOVELRT_INTEROP_RESOURCEMANAGEMENT_FILEPATHUUIDMAP_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_FilePathUuidMap_Indexer(NrtFilePathUuidMapHandle map, const char* filePath, NrtUuid* outUuid);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_RESOURCEMANAGEMENT_FILEPATHUUIDMAP_H
