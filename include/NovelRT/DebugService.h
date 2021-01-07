// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELDEBUGSERVICE_H
#define NOVELRT_NOVELDEBUGSERVICE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT {

  class DebugService {

  private:
    std::shared_ptr<Graphics::RenderingService> _renderingService;
    std::unique_ptr<Graphics::TextRect> _fpsCounter;

    uint32_t _framesPerSecond;

    uint32_t _minFrames = 1000;
    uint32_t _maxFrames = 0;
    uint32_t _frameCount = 1;
    uint32_t _runningAverage = 1;

    bool _frameSkip = false;

    void updateFpsCounter();

    void onSceneConstruction();

  public:
    DebugService(Utilities::Event<>& sceneConstructionEvent, std::shared_ptr<Graphics::RenderingService> renderingService) noexcept;

    bool getIsFpsCounterVisible() const;
    void setIsFpsCounterVisible(bool value);

    inline uint32_t getFramesPerSecond() const {
      return _framesPerSecond;
    }

    inline uint32_t accumulateAverage(uint32_t data) {
      if(_frameSkip)
      {
        _runningAverage += data;
      }
      else
      {
        _frameSkip = true;
      }
      return _runningAverage / _frameCount++;
    }

    void setFramesPerSecond(uint32_t value);
  };
}

#endif // NOVELRT_NOVELDEBUGSERVICE_H
