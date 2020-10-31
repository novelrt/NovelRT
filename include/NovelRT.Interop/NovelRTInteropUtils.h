// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#ifndef NOVELRT_INTEROP_NOVELRTINTEROPUTILS_H
#define NOVELRT_INTEROP_NOVELRTINTEROPUTILS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
  NOVELRT_SUCCESS = 0,
  NOVELRT_FAILURE = 1
};


enum {
  NOVELRT_FALSE = 0,
  NOVELRT_TRUE = 1
};

const char* NovelRT_getLastError();
  
#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_NOVELRTINTEROPUTILS_H
