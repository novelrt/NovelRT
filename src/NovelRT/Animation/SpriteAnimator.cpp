// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Animation {
  SpriteAnimator::SpriteAnimator(NovelRunner* runner, Graphics::ImageRect* rect) noexcept :
    _accumulatedDelta(0.0f),
    _runner(runner),
    _rect(rect),
    _animatorState(AnimatorPlayState::Stopped),
    _animationUpdateHandle([=](double delta) { constructAnimation(delta); }),
    _currentState(nullptr) {}

  void SpriteAnimator::constructAnimation(double delta) {
    switch (_animatorState) {
    case AnimatorPlayState::Playing:
      if (_currentState == nullptr) {
        _currentState = _states.at(0);
        _currentState->getFrames()->at(_currentFrameIndex).getOnFrameEnterDelegate()();
      }

      if (_currentState->getShouldLoop() && _currentFrameIndex >= _currentState->getFrames()->size()) _currentFrameIndex = 0;

      if (_currentState->getFrames()->size() < _currentFrameIndex && _currentState->getFrames()->at(_currentFrameIndex).getDuration() <= _accumulatedDelta) {
        _currentState->getFrames()->at(_currentFrameIndex++).getOnFrameExitDelegate()();
        auto newFrame = _currentState->getFrames()->at(_currentFrameIndex);
        newFrame.getOnFrameEnterDelegate()();
        _rect->setTexture(newFrame.getTexture());
      }

      for (auto pair : _currentState->transitions) {
        auto conditions = std::get<std::vector<std::function<bool()>>>(pair.second);
        bool shouldTransitionToThisState = true;

        for (auto condition : conditions) {
          if (condition()) continue;

          shouldTransitionToThisState = false;
          break;
        }

        if (!shouldTransitionToThisState) continue;

        _currentState = std::get<std::shared_ptr<SpriteAnimatorState>>(pair.second);
        _accumulatedDelta = 0.0f;
        _currentFrameIndex = 0;
        _currentState->getFrames()->at(_currentFrameIndex).getOnFrameEnterDelegate()();

        break;

      }

      _accumulatedDelta += delta;
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
