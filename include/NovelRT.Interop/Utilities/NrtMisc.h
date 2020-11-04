// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_UTILITIES_MISC_H
#define NOVELRT_INTEROP_UTILITIES_MISC_H

#include <stdint.h>
#include "../NrtInteropUtils.h"

#ifdef __cplusplus
extern "C" {
#endif

const char* Nrt_getExecutablePath();
NrtResult Nrt_getExecutableDirPath(const char** path);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_UTILITIES_MISC_H
