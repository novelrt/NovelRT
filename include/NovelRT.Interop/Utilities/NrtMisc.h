// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_UTILITIES_MISC_H
#define NOVELRT_INTEROP_UTILITIES_MISC_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    const char* Nrt_GetExecutablePath();
    const char* Nrt_GetExecutableDirPath();
    const char* Nrt_AppendFilePath(int32_t numberOfArgs, const char* const* args);
    const char* Nrt_AppendText(int32_t numberOfArgs, const char* const* args);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_UTILITIES_MISC_H
