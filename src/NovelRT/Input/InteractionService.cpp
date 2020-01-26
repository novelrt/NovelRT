// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Input {
  InteractionService::InteractionService(NovelRunner* const runner) :
    _runner(runner),
    _clickTarget(nullptr),
    _logger(LoggingService(Utilities::Misc::CONSOLE_LOG_INPUT)) {
    _mousePositionsOnScreenPerButton.insert({ KeyCode::LeftMouseButton, Maths::GeoVector<float>(0, 0) });
    _keyStates.insert({ KeyCode::LeftMouseButton, KeyState::Idle });
    _keyStates.insert({ KeyCode::RightMouseButton, KeyState::Idle });
  }

  void InteractionService::processKeyState(KeyCode code, KeyState state) {
    switch (state) {
    case KeyState::KeyDown:
      if (_keyStates.at(code) == KeyState::KeyDown) {
        _keyStates.at(code) = KeyState::KeyDownHeld;
      }
      else if (_keyStates.at(code) != KeyState::KeyDownHeld) {
        _keyStates.at(code) = KeyState::KeyDown;
      }
      break;
    case KeyState::KeyDownHeld:
    case KeyState::KeyUp:
      _keyStates.at(code) = (_keyStates.at(code) == KeyState::KeyUp) ? KeyState::Idle : state; //lmao
      break;
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

    processKeyState(keyCode, keyState);
  }

  void InteractionService::acceptMouseButtonClickPush(int button, int action, const Maths::GeoVector<float>& mousePosition) {
    auto keyState = static_cast<KeyState>(action);
    auto keyCode = static_cast<KeyCode>(button);

    _mousePositionsOnScreenPerButton.at(keyCode) = mousePosition.getVec4Value() * glm::scale(glm::vec3(1920.0f / _screenSize.getX(), 1080.0f / _screenSize.getY(), 0.0f));

    processKeyState(keyCode, keyState);
  }

  void InteractionService::HandleInteractionDraw(InteractionObject* target) {
    if (_keyStates[target->getSubscribedKey()] == KeyState::KeyDown
      && target->validateInteractionPerimeter(_mousePositionsOnScreenPerButton[KeyCode::LeftMouseButton])
      && (_clickTarget == nullptr || (_clickTarget->getLayer() > target->getLayer()))) {
        _logger.logDebug("Valid click target detected! Executing...");
        _clickTarget = target;
    }
  }

  void InteractionService::consumePlayerInput() {
    processKeyState(KeyCode::LeftMouseButton, _keyStates.at(KeyCode::LeftMouseButton));
    glfwPollEvents();
  }

  std::unique_ptr<BasicInteractionRect> InteractionService::createBasicInteractionRect(const Transform& transform, int layer) {
    return std::make_unique<BasicInteractionRect>(transform, layer, [this](InteractionObject* x) { HandleInteractionDraw(x); });
  }
  void InteractionService::executeClickedInteractable() {
    if (_clickTarget == nullptr) return;

    _clickTarget->raiseInteracted();
    _clickTarget = nullptr;
  }
}
