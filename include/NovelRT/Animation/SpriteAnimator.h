// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ANIMATION_SPRITEANIMATOR_H
#define NOVELRT_ANIMATION_SPRITEANIMATOR_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Animation {

  class SpriteAnimator {
  private:
    float _accumulatedDelta;
    int32_t _currentFrameIndex;
    NovelRunner* _runner; //I'm a bit worried about this, but whatever, just want it working for now
    Graphics::ImageRect* _rect;
    AnimatorPlayState _animatorState;
    Utilities::EventHandler<double> _animationUpdateHandle;
    std::vector<std::shared_ptr<SpriteAnimatorState>> _states;
    std::shared_ptr<SpriteAnimatorState> _currentState;
    std::vector<SpriteAnimatorFrame> _stateFrames;
    LoggingService _logger;


    void constructAnimation(double delta);

  public:
    explicit SpriteAnimator(NovelRunner* runner, Graphics::ImageRect* rect) noexcept;
    void play();
    void pause();
    void stop();

    inline AnimatorPlayState getCurrentPlayState() const noexcept {
      return _animatorState;
    }

    inline void insertNewState(std::shared_ptr<SpriteAnimatorState> state) {
      _states.push_back(state);
    }
  };
}

#endif //!NOVELRT_ANIMATION_SPRITEANIMATOR_H
