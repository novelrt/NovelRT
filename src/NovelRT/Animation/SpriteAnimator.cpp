// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Animation {
  SpriteAnimator::SpriteAnimator(NovelRunner* runner, Graphics::ImageRect* rect) noexcept :
  _runner(runner),
  _rect(rect),
  _animatorState(AnimatorPlayState::Stopped),
  _animationUpdateHandle([=](double delta) { constructAnimation(delta); }) {}

  void SpriteAnimator::constructAnimation(double delta) {
    switch (_animatorState) {
    case AnimatorPlayState::Playing:
      break;
    case AnimatorPlayState::Paused:
      break;
    }
  }

  void SpriteAnimator::play() {
    _runner->Update += _animationUpdateHandle;
    _animatorState = AnimatorPlayState::Playing;
  }

  void SpriteAnimator::pause() {
    _animatorState = AnimatorPlayState::Paused;
  }

  void SpriteAnimator::stop() {
    _runner->Update -= _animationUpdateHandle;
    _animatorState = AnimatorPlayState::Stopped;
  }
}
