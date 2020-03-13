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
      _keyStates.insert({ code, KeyState::Idle });
    }
  }
  void InteractionService::processKeyState(KeyCode code, KeyState state) {
    validateIfKeyCached(code);

    auto result = _keyStates.find(code);

    switch (state) {
    case KeyState::KeyDown:
      if (result->second == KeyState::KeyDown) {
        result->second = KeyState::KeyDownHeld;
      }
      else if (result->second != KeyState::KeyDownHeld) {
        result->second = KeyState::KeyDown;
      }
      break;
    case KeyState::KeyDownHeld:
    case KeyState::KeyUp:
      result->second = (result->second == KeyState::KeyUp) ? KeyState::Idle : state; //lmao
      break;
    }
  }

  void InteractionService::processMouseStates() {
    for (int32_t i = static_cast<int32_t>(KeyCode::FirstMouseButton); i < static_cast<int32_t>(KeyCode::LastMouseButton); i++) {
      auto keyCode = static_cast<KeyCode>(i);
      auto result = _keyStates.find(keyCode);

      if (result == _keyStates.end()) continue;
      processKeyState(result->first, result->second);
    }
  }

  void InteractionService::acceptKeyboardInputBindingPush(int key, int action) {

    auto keyState = static_cast<KeyState>(action);
    auto keyCode = static_cast<KeyCode>(key);

    auto result = _keyStates.find(keyCode);

    if (result == _keyStates.end()) {
      _keyStates.insert({ keyCode, keyState });
      return;
    }

    validateIfKeyCached(keyCode);
    processKeyState(keyCode, keyState);
  }

  void InteractionService::acceptMouseButtonClickPush(int button, int action, const Maths::GeoVector<float>& mousePosition) {
    auto keyState = static_cast<KeyState>(action);
    auto keyCode = static_cast<KeyCode>(button);
    auto value = mousePosition.vec4Value() * glm::scale(glm::vec3(1920.0f / _screenSize.getX(), 1080.0f / _screenSize.getY(), 0.0f));

    auto result = _mousePositionsOnScreenPerButton.find(keyCode);

    if (result == _mousePositionsOnScreenPerButton.end()) {
      _mousePositionsOnScreenPerButton.insert({ keyCode, value });
    }
    else {
      result->second = value;
    }

    validateIfKeyCached(keyCode);
    processKeyState(keyCode, keyState);
  }

  void InteractionService::HandleInteractionDraw(InteractionObject* target) {
    if (_keyStates[target->subscribedKey()] == KeyState::KeyDown
      && target->validateInteractionPerimeter(_mousePositionsOnScreenPerButton[target->subscribedKey()])
      && (_clickTarget == nullptr || (_clickTarget->getLayer() > target->getLayer()))) {
      _logger.logDebug("Valid click target detected! Executing...");
      _clickTarget = target;
    }
  }

void InteractionService::consumePlayerInput() {
  processMouseStates();
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
