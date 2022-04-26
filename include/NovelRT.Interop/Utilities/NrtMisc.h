// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_UTILITIES_MISC_H
#define NOVELRT_INTEROP_UTILITIES_MISC_H

#include <NovelRT.Interop/NrtTypedefs.h>

#ifdef __cplusplus
extern "C"
{
#endif

    const char* Nrt_getExecutablePath();
    const char* Nrt_getExecutableDirPath();
    const char* Nrt_appendFilePath(int32_t numberOfArgs, const char* const* args);
    const char* Nrt_appendText(int32_t numberOfArgs, const char* const* args);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_UTILITIES_MISC_H
