// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <stdint.h>

#ifndef NOVELRT_INTEROP_NOVELRUNNER_H
#define NOVELRT_INTEROP_NOVELRUNNER_H

#ifdef __cplusplus
extern "C" {
#endif

  typedef void NovelRunner_t;

  NovelRunner_t* NovelRunner_create(int displayNumber);
  NovelRunner_t* NovelRunner_createCustom(int displayNumber, const char* windowTitle, uint32_t targetFrameRate);
  int NovelRunner_runNovel(NovelRunner_t* runner);
  void NovelRunner_destroy(NovelRunner_t* runner);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_NOVELRUNNER_H
