// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELDEBUGSERVICE_H
#define NOVELRT_NOVELDEBUGSERVICE_H

#include "NovelTextRect.h"

namespace NovelRT {

  typedef class NovelRunner NovelRunner;

  class NovelDebugService {

  private:
    NovelRunner* _runner;
    NovelTextRect* _fpsCounter;
    uint32_t _framesPerSecond;

    void updateFpsCounter();

  public:
    NovelDebugService(NovelRunner* runner);

    bool getIsFpsCounterVisible() const;
    void setIsFpsCounterVisible(bool value);

    inline uint32_t getFramesPerSecond() const {
      return _framesPerSecond;
    }
    void setFramesPerSecond(uint32_t value);
  };
}

#endif // NOVELRT_NOVELDEBUGSERVICE_H
