// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Animation {
  SpriteAnimator::SpriteAnimator(NovelRunner* runner, Graphics::ImageRect* rect) noexcept :
    _accumulatedDelta(0.0f),
    _currentFrameIndex(0),
    _runner(runner),
    _rect(rect),
    _animatorState(AnimatorPlayState::Stopped),
    _animationUpdateHandle(Utilities::EventHandler<Timing::Timestamp>([=](Timing::Timestamp delta) { constructAnimation(delta); })),
    _currentState(nullptr),
    _logger(Utilities::Misc::CONSOLE_LOG_GENERIC) {}

  void SpriteAnimator::constructAnimation(Timing::Timestamp delta) {
    switch (_animatorState) {
      case AnimatorPlayState::Playing: {
        if (_currentState == nullptr) {
          _currentState = _states.at(0);

          auto frame = _currentState->frames().at(_currentFrameIndex);
          _rect->texture() = frame.texture();
          frame.FrameEnter();
        }

        auto transitionPtr = _currentState->tryFindValidTransition();

        if (transitionPtr != nullptr) {
          _currentState = transitionPtr;
          _accumulatedDelta = 0.0f;
          _currentFrameIndex = 0;
          _currentState->frames().at(_currentFrameIndex).FrameEnter();
        }

        if (_currentState->frames().size() > _currentFrameIndex && _currentState->frames().at(_currentFrameIndex).duration() <= _accumulatedDelta) {
          _accumulatedDelta = 0;
          _currentState->frames().at(_currentFrameIndex++).FrameExit();

          if (_currentState->shouldLoop() && _currentFrameIndex >= _currentState->frames().size()) {
            _currentFrameIndex = 0;
          } else if (_currentFrameIndex >= _currentState->frames().size()) {
            return;
          }

          auto newFrame = _currentState->frames().at(_currentFrameIndex);
          _rect->texture() = newFrame.texture();
          newFrame.FrameEnter();
        }


        _accumulatedDelta += delta.getSecondsFloat();
        break;
      }

      case AnimatorPlayState::Stopped:
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
    _accumulatedDelta = 0;
    _currentFrameIndex = 0;
  }
}
