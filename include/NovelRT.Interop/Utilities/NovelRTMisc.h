// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <stdint.h>

#ifndef NOVELRT_INTEROP_UTILITIES_MISC_H
#define NOVELRT_INTEROP_UTILITIES_MISC_H

#ifdef __cplusplus
extern "C" {
#endif

const char* NovelRT_getExecutablePath();
int32_t NovelRT_getExecutableDirPath(const char** path);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_UTILITIES_MISC_H
