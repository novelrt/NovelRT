// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <stdint.h>

#ifndef NOVELRT_INTEROP_NOVELRUNNER_H
#define NOVELRT_INTEROP_NOVELRUNNER_H

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct NovelRunnerHandle* NovelRTNovelRunner;

  NovelRTNovelRunner* NovelRunner_create(int displayNumber);
  NovelRTNovelRunner* NovelRunner_createCustom(int displayNumber, const char* windowTitle, uint32_t targetFrameRate);
  int NovelRunner_runNovel(NovelRTNovelRunner* runner);
  void NovelRunner_destroy(NovelRTNovelRunner* runner);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_NOVELRUNNER_H
