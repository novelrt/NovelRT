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
    NovelRunner* _runner; //I'm a bit worried about this, but whatever, just want it working for now
    Graphics::ImageRect* _rect;
    AnimatorPlayState _animatorState;
    std::function<void(double)> _animationUpdateHandle;
    std::vector<std::shared_ptr<SpriteAnimatorState>> _states;
    std::shared_ptr<SpriteAnimatorState> _currentState;
    int32_t _currentFrameIndex;
    std::vector<SpriteAnimatorFrame> _stateFrames;


    void constructAnimation(double delta);

  public:
    explicit SpriteAnimator(NovelRunner* runner, Graphics::ImageRect* rect) noexcept;
    void play();
    void pause();
    void stop();
  };
}

#endif //!NOVELRT_ANIMATION_SPRITEANIMATOR_H
