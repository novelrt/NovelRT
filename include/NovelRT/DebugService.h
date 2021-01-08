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
<<<<<<< HEAD
    uint32_t _minFramesPerSecond = 1000;
    uint32_t _maxFramesPerSecond = 0;
    uint32_t _totalSeconds = 0;
    uint32_t _totalFrames = 0;
=======

    uint32_t _minFrames = 1000;
    uint32_t _maxFrames = 0;
    uint32_t _frameCount = 1;
    uint32_t _runningAverage = 1;

    bool _frameSkip = false;

>>>>>>> 336ccfea02c18b658ea45876e684cb1f82a6b717
    void updateFpsCounter();

    void onSceneConstruction();

    
  public:
    DebugService(Utilities::Event<>& sceneConstructionEvent, std::shared_ptr<Graphics::RenderingService> renderingService) noexcept;

    bool getIsFpsCounterVisible() const;
    void setIsFpsCounterVisible(bool value);

    void GetStatistics(uint32_t framesPerSecond,uint32_t totalSeconds,uint32_t totalFrames);
    
    inline uint32_t getFramesPerSecond() const {
<<<<<<< HEAD
        return _framesPerSecond;
=======
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
>>>>>>> 336ccfea02c18b658ea45876e684cb1f82a6b717
    }

    void setFramesPerSecond(uint32_t framesPerSecond);
  };
}

#endif // NOVELRT_NOVELDEBUGSERVICE_H
