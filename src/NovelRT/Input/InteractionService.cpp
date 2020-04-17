// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Input {
  InteractionService::InteractionService(NovelRunner* const runner) noexcept :
    _runner(runner),
    _clickTarget(nullptr),
    _logger(LoggingService(Utilities::Misc::CONSOLE_LOG_INPUT)) {
    auto ptr = _runner->getWindowingService();
    if(!ptr.expired()) ptr.lock()->WindowResized += [this](auto value) {
      setScreenSize(value);
    };
  }

  void InteractionService::validateIfKeyCached(KeyCode code) {
    auto result = _keyStates.find(code);

    if (result == _keyStates.end()) {
      _keyStates.insert({ code, KeyStateFrameUpdatePair{ KeyState::Idle, false } });
    }
  }
  void InteractionService::processKeyState(KeyCode code, KeyState state) {
    validateIfKeyCached(code);
    auto result = _keyStates.find(code);
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
    for (auto& pair : _keyStates) {
      processKeyState(pair.first, pair.second.currentState);
    }
  }

  void InteractionService::acceptKeyboardInputBindingPush(int key, int action) {

    auto keyState = static_cast<KeyState>(action);
    auto keyCode = static_cast<KeyCode>(key);

    auto result = _keyStates.find(keyCode);

    if (result == _keyStates.end()) {
      _keyStates.insert({ keyCode, KeyStateFrameUpdatePair{ keyState, true } });
      return;
    }

    validateIfKeyCached(keyCode);
    processKeyState(keyCode, keyState);
  }

  void InteractionService::acceptMouseButtonClickPush(int button, int action, const Maths::GeoVector2<float>& mousePosition) {
    auto keyState = static_cast<KeyState>(action);
    auto keyCode = static_cast<KeyCode>(button);
    auto value = Maths::GeoVector4<float>(mousePosition).vec4Value() * glm::scale(glm::vec3(1920.0f / _screenSize.getX(), 1080.0f / _screenSize.getY(), 0.0f));

    auto result = _mousePositionsOnScreenPerButton.find(keyCode);

    if (result == _mousePositionsOnScreenPerButton.end()) {
      _mousePositionsOnScreenPerButton.insert({ keyCode, Maths::GeoVector2<float>(value.x, value.y) });
    }
    else {
      result->second = Maths::GeoVector2<float>(value.x, value.y);
    }

    validateIfKeyCached(keyCode);
    processKeyState(keyCode, keyState);
  }

  void InteractionService::HandleInteractionDraw(InteractionObject* target) {
    if (_keyStates[target->subscribedKey()].currentState == KeyState::KeyDown
      && target->validateInteractionPerimeter(_mousePositionsOnScreenPerButton[target->subscribedKey()])
      && (_clickTarget == nullptr || (_clickTarget->layer() > target->layer()))) {
      _logger.logDebug("Valid click target detected! Executing...");
      _clickTarget = target;
    }
  }

void InteractionService::consumePlayerInput() {
  for (auto& pair : _keyStates) {
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
