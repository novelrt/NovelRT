// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Input {
  InteractionService::InteractionService(std::weak_ptr<Windowing::WindowingService> windowingService) noexcept :
    _currentBufferIndex(0),
    _clickTarget(nullptr),
    _logger(LoggingService(Utilities::Misc::CONSOLE_LOG_INPUT)) {
    if(!windowingService.expired()) windowingService.lock()->WindowResized += [this](auto value) {
      setScreenSize(value);
    };
  }

  void InteractionService::processKeyState(KeyCode code, KeyState state) {
    auto result = _keyStates[_currentBufferIndex].find(code);
    auto previousState = result->second.currentState;

    if (result->second.wasUpdatedThisFrame) {
      return;
    }

    switch (state) {
    case KeyState::KeyDown:
      if (result->second.currentState == KeyState::KeyDown) {
        result->second.currentState = KeyState::KeyDownHeld;
      }
      else if (result->second.currentState != KeyState::KeyDownHeld) {
        result->second.currentState = KeyState::KeyDown;
      }
      break;
    case KeyState::KeyDownHeld:
    case KeyState::KeyUp:
      result->second.currentState = (result->second.currentState == KeyState::KeyUp) ? KeyState::Idle : state; //lmao
      break;
    }

    if(previousState != result->second.currentState) {
      result->second.wasUpdatedThisFrame = true;
    }
  }

  void InteractionService::processKeyStates() {
    for (auto& pair : _keyStates[_currentBufferIndex]) {
      processKeyState(pair.first, pair.second.currentState);
    }
  }

  void InteractionService::acceptKeyboardInputBindingPush(int key, int action) {

    auto keyState = static_cast<KeyState>(action);
    auto keyCode = static_cast<KeyCode>(key);

    auto result = _keyStates[_currentBufferIndex].find(keyCode);

    if (result == _keyStates[_currentBufferIndex].end()) {
      _keyStates[_currentBufferIndex].insert({ keyCode, KeyStateFrameUpdatePair{ keyState, true } });
      return;
    }
    processKeyState(keyCode, keyState);
  }

  void InteractionService::acceptMouseButtonClickPush(int button, int action, const Maths::GeoVector2<float>& mousePosition) {
    auto keyState = static_cast<KeyState>(action);
    auto keyCode = static_cast<KeyCode>(button);
    auto value = Maths::GeoVector4<float>(mousePosition).vec4Value() * glm::scale(glm::vec3(1920.0f / _screenSize.getX(), 1080.0f / _screenSize.getY(), 0.0f));

    _cursorPosition =  Maths::GeoVector2<float>(value.x, value.y);

    processKeyState(keyCode, keyState);
  }

  void InteractionService::HandleInteractionDraw(InteractionObject* target) {
    if (_keyStates[_currentBufferIndex][target->subscribedKey()].currentState == KeyState::KeyDown
      && target->validateInteractionPerimeter(_cursorPosition)
      && (_clickTarget == nullptr || (_clickTarget->layer() > target->layer()))) {
      _logger.logDebug("Valid click target detected! Executing...");
      _clickTarget = target;
    }
  }

void InteractionService::consumePlayerInput() {
  for (auto& pair : _keyStates[_currentBufferIndex]) {
    pair.second.wasUpdatedThisFrame = false;
  }

  processKeyStates();
  glfwPollEvents();
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
