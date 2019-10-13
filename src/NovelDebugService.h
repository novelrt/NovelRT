// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELDEBUGSERVICE_H
#define NOVELRT_NOVELDEBUGSERVICE_H

#include "NovelTextRect.h"

namespace NovelRT {
  typedef class NovelRunner NovelRunner;

  class NovelDebugService {
  public:
    NovelDebugService(NovelRunner* runner);

    bool getIsFpsCounterVisible() const;
    void setIsFpsCounterVisible(bool value);

    uint32_t getFramesPerSecond() const;
    void setFramesPerSecond(uint32_t value);

  private:
    void updateFpsCounter();

    NovelRunner* _runner;
    NovelTextRect* _fpsCounter;
    uint32_t _framesPerSecond;
  };

  inline uint32_t NovelDebugService::getFramesPerSecond() const {
    return _framesPerSecond;
  }
}

#endif // NOVELRT_NOVELDEBUGSERVICE_H
