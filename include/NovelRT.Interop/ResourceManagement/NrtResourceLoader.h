// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#ifndef NOVELRT_INTEROP_RESOURCEMANAGEMENT_NRTRESOURCELOADER_H
#define NOVELRT_INTEROP_RESOURCEMANAGEMENT_NRTRESOURCELOADER_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_ResourceLoader_GetResourcePath(NrtResourceLoaderHandle loader, char** outputPath);
    NrtResult Nrt_ResourceLoader_SetResourcePath(NrtResourceLoaderHandle loader, const char* newPath);

    NrtResult Nrt_ResourceLoader_Destroy(NrtResourceLoaderHandle loader);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_RESOURCEMANAGEMENT_NRTRESOURCELOADER_H
