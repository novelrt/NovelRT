// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.Interop/NovelRunner_t.h"
#include <NovelRT.h>
#include <stdint.h>

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

  NovelRunner_t* NovelRunner_create(int displayNumber)
  {
    NovelRunner* runner = new NovelRunner(displayNumber);

    return reinterpret_cast<NovelRunner_t*>(runner);
  }

  NovelRunner_t* NovelRunner_createCustom(int displayNumber, const char* windowTitle, uint32_t targetFrameRate)
  {
    NovelRunner* runner = new NovelRunner(displayNumber, windowTitle, targetFrameRate);

    return reinterpret_cast<NovelRunner_t*>(runner);
  }

  int NovelRunner_runNovel(NovelRunner_t* runner)
  {
    NovelRunner* cRunner = reinterpret_cast<NovelRunner*>(runner);

    return cRunner->runNovel();
  }

  void NovelRunner_destroy(NovelRunner_t* runner)
  {
    NovelRunner* cRunner = reinterpret_cast<NovelRunner*>(runner);

    return cRunner->~NovelRunner();
  }

#ifdef __cplusplus
}
#endif
