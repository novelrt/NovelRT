// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELDEBUGSERVICE_H
#define NOVELRT_NOVELDEBUGSERVICE_H

namespace NovelRT {

  class DebugService {

  private:
    NovelRunner* const _runner;
    std::unique_ptr<Graphics::TextRect> _fpsCounter;
    uint32_t _framesPerSecond;

    void updateFpsCounter();

    void onSceneConstruction();

  public:
    DebugService(NovelRunner* const runner);

    bool getIsFpsCounterVisible() const;
    void setIsFpsCounterVisible(bool value);

    inline uint32_t getFramesPerSecond() const {
      return _framesPerSecond;
    }
    void setFramesPerSecond(uint32_t value);
  };
}

#endif // NOVELRT_NOVELDEBUGSERVICE_H
