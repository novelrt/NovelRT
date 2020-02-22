// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Animation {
  SpriteAnimator::SpriteAnimator(NovelRunner* runner, Graphics::ImageRect* rect) noexcept :
    _accumulatedDelta(0.0f),
    _currentFrameIndex(0),
    _runner(runner),
    _rect(rect),
    _animatorState(AnimatorPlayState::Stopped),
    _animationUpdateHandle(Utilities::EventHandler<double>([=](double delta) { constructAnimation(delta); })),
    _currentState(nullptr),
    _logger(Utilities::Misc::CONSOLE_LOG_GENERIC) {}

  void SpriteAnimator::constructAnimation(double delta) {
    switch (_animatorState) {
      case AnimatorPlayState::Playing: {
        if (_currentState == nullptr) {
          _currentState = _states.at(0);
          _currentState->getFrames()->at(_currentFrameIndex).FrameEnter();
        }

        auto transitionPtr = _currentState->tryFindValidTransition();

        if (transitionPtr != nullptr) {
          _currentState = transitionPtr;
          _accumulatedDelta = 0.0f;
          _currentFrameIndex = 0;
          _currentState->getFrames()->at(_currentFrameIndex).FrameEnter();
        }

        if (_currentState->getFrames()->size() > _currentFrameIndex && _currentState->getFrames()->at(_currentFrameIndex).getDuration() <= _accumulatedDelta) {
          _accumulatedDelta = 0;
          _currentState->getFrames()->at(_currentFrameIndex++).FrameExit();

          if (_currentState->getShouldLoop() && _currentFrameIndex >= _currentState->getFrames()->size()) {
            _currentFrameIndex = 0;
          } else if (_currentFrameIndex >= _currentState->getFrames()->size()) {
            return;
          }

          auto newFrame = _currentState->getFrames()->at(_currentFrameIndex);
          newFrame.FrameEnter();
          _rect->setTexture(newFrame.getTexture());
        }


        _accumulatedDelta += static_cast<float>(delta);
        break;
      }

      default:
        assert((_animatorState == AnimatorPlayState::Stopped) || (_animatorState == AnimatorPlayState::Paused));
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
