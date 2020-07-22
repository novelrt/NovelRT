// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Input {
  InteractionService::InteractionService(std::weak_ptr<Windowing::WindowingService> windowingService) noexcept :
    _previousBufferIndex(0),
    _currentBufferIndex(1),
    _clickTarget(nullptr),
    _logger(LoggingService(Utilities::Misc::CONSOLE_LOG_INPUT)) {
    if(!windowingService.expired()) windowingService.lock()->WindowResized += [this](auto value) {
      setScreenSize(value);
    };
  }

  void InteractionService::processKeyState(KeyCode code, KeyState state) {
    auto& previousBuffer = _keyStates.at(_previousBufferIndex);
    auto& currentBuffer = _keyStates.at(_currentBufferIndex);

    auto result = previousBuffer.find(code);
    KeyState stateResult;

    if (result == _keyStates[_previousBufferIndex].end()) {
      stateResult = KeyState::Idle;
    }
    else {
      stateResult = result->second;
    }

    switch (state) {
    case KeyState::KeyDown:
      if (stateResult == KeyState::KeyDown) {
        currentBuffer.insert_or_assign(code, KeyState::KeyDownHeld);
      }
      else if (stateResult != KeyState::KeyDownHeld) {
        currentBuffer.insert_or_assign(code, KeyState::KeyDown);
      }
      break;
    case KeyState::KeyDownHeld:
    case KeyState::KeyUp:
      currentBuffer.insert_or_assign(code, (stateResult == KeyState::KeyUp) ? KeyState::Idle : state);
      break;
    case KeyState::Idle:
    default:
      //do nothing. Seriously. These cases are only here because the Ubuntu build cried at me in CI for not having them suddenly.
      break;
    }
  }

  void InteractionService::processKeyStates() {
    auto& currentBuffer = _keyStates.at(_currentBufferIndex);

    for (const auto& pair : _keyStates.at(_previousBufferIndex)) {
      auto findResultForCurrent = currentBuffer.find(pair.first);
      if (findResultForCurrent != currentBuffer.end()) {
        processKeyState(findResultForCurrent->first, findResultForCurrent->second);
      }
      else {
        processKeyState(pair.first, pair.second);
      }
    }
  }

  void InteractionService::acceptKeyboardInputBindingPush(int key, int action) {
    auto keyState = static_cast<KeyState>(action);
    auto keyCode = static_cast<KeyCode>(key);
    _keyStates.at(_currentBufferIndex).insert_or_assign(keyCode, keyState);
  }

  void InteractionService::acceptMouseButtonClickPush(int button, int action, const Maths::GeoVector2<float>& mousePosition) {
    auto keyState = static_cast<KeyState>(action);
    auto keyCode = static_cast<KeyCode>(button);
    auto value = Maths::GeoVector4<float>(mousePosition).vec4Value() * glm::scale(glm::vec3(1920.0f / _screenSize.getX(), 1080.0f / _screenSize.getY(), 0.0f));

    _cursorPosition =  Maths::GeoVector2<float>(value.x, value.y);
    _keyStates.at(_currentBufferIndex).insert_or_assign(keyCode, keyState);
  }

  void InteractionService::HandleInteractionDraw(InteractionObject* target) {

    auto& currentBuffer = _keyStates.at(_currentBufferIndex);
    auto subscribedKeyIterator = currentBuffer.find(target->subscribedKey());

    if (subscribedKeyIterator == currentBuffer.end()) {
      return;
    }

    if (subscribedKeyIterator->second == KeyState::KeyDown
      && target->validateInteractionPerimeter(_cursorPosition)
      && (_clickTarget == nullptr || (_clickTarget->layer() > target->layer()))) {
      _logger.logDebug("Valid click target detected! Executing...");
      _clickTarget = target;
    }
  }

void InteractionService::consumePlayerInput() {
  _currentBufferIndex = (_currentBufferIndex + 1) % INPUT_BUFFER_COUNT;
  _keyStates.at(_currentBufferIndex).clear();
  glfwPollEvents();
  processKeyStates();
  _previousBufferIndex = _currentBufferIndex;

}

  std::unique_ptr<BasicInteractionRect> InteractionService::createBasicInteractionRect(const Transform& transform, int layer) {
    return std::make_unique<BasicInteractionRect>(transform, layer, [this](InteractionObject* x) { HandleInteractionDraw(x); });
  }
  void InteractionService::executeClickedInteractable() {
    if (_clickTarget == nullptr) return;

    _clickTarget->Interacted();
    _clickTarget = nullptr;
  }
}
