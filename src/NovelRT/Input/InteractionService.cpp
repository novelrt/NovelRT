// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Input {
  InteractionService::InteractionService(std::shared_ptr<Windowing::WindowingService> windowingService) noexcept :
    _previousBufferIndex(0),
    _currentBufferIndex(1),
    _clickTarget(nullptr),
    _logger(LoggingService(Utilities::Misc::CONSOLE_LOG_INPUT)) {
    windowingService->WindowResized += [this](auto value) {
      setScreenSize(value);
    };
    windowingService->MouseButtonClicked += [this](auto eventArgs) {
      acceptMouseButtonClickPush(eventArgs.button, eventArgs.action, eventArgs.mousePosition);
    };
    windowingService->KeyboardButtonChanged += [this](auto eventArgs) {
      acceptKeyboardInputBindingPush(eventArgs.key, eventArgs.action);
    };
  }

  void InteractionService::processKeyState(KeyCode code, KeyState state) {
    auto& previousBuffer = _keyStates.at(_previousBufferIndex);
    auto& currentBuffer = _keyStates.at(_currentBufferIndex);

    auto previousBufferResult = previousBuffer.find(code);
    KeyState previousStateResult;

    if (previousBufferResult == previousBuffer.end()) {
      previousStateResult = KeyState::Idle;
    }
    else {
      previousStateResult = previousBufferResult->second.getCurrentState();
    }

    auto currentBufferResult = currentBuffer.find(code);
    KeyStateFrameChangeLog changeLogObject{};

    if (currentBufferResult == currentBuffer.end()) {
      changeLogObject = KeyStateFrameChangeLog();
    }
    else {
      changeLogObject = currentBufferResult->second;
    }

    switch (state) {
    case KeyState::KeyDown:
      if (previousStateResult == KeyState::KeyDown) {
        changeLogObject.pushNewState(KeyState::KeyDownHeld);
      }
      else if (previousStateResult != KeyState::KeyDownHeld) {
        changeLogObject.pushNewState(KeyState::KeyDown); //TODO: Is this actually gonna work lol
      }
      break;
    case KeyState::KeyDownHeld:
    case KeyState::KeyUp:
      changeLogObject.pushNewState((previousStateResult == KeyState::KeyUp) ? KeyState::Idle : state);
      break;
    case KeyState::Idle:
    default:
      //do nothing. Seriously. These cases are only here because the Ubuntu build cried at me in CI for not having them suddenly.
      break;
    }

    currentBuffer.insert_or_assign(code, changeLogObject);
  }

  void InteractionService::processKeyStates() {
    auto& currentBuffer = _keyStates.at(_currentBufferIndex);

    for (const auto& pair : _keyStates.at(_previousBufferIndex)) {
      auto findResultForCurrent = currentBuffer.find(pair.first);
      if (findResultForCurrent != currentBuffer.end()) {
        processKeyState(findResultForCurrent->first, findResultForCurrent->second.getCurrentState());
      }
      else {
        processKeyState(pair.first, pair.second.getCurrentState());
      }
    }
  }

  void InteractionService::acceptKeyboardInputBindingPush(int key, int action) {
    auto keyState = static_cast<KeyState>(action);
    auto keyCode = static_cast<KeyCode>(key);
    KeyStateFrameChangeLog log{};

    if (_keyStates.at(_currentBufferIndex).find(keyCode) != _keyStates.at(_currentBufferIndex).end()) {
      log = _keyStates.at(_currentBufferIndex).at(keyCode);
    }

    log.pushNewState(keyState);
    _keyStates.at(_currentBufferIndex).insert_or_assign(keyCode, log);
  }

  void InteractionService::acceptMouseButtonClickPush(int button, int action, Maths::GeoVector2F mousePosition) {
    auto keyState = static_cast<KeyState>(action);
    auto keyCode = static_cast<KeyCode>(button);
    auto value = Maths::GeoVector4F(mousePosition).vec4Value() * glm::scale(glm::vec3(1920.0f / _screenSize.x, 1080.0f / _screenSize.y, 0.0f));

    _cursorPosition =  Maths::GeoVector2F(value.x, value.y);
    KeyStateFrameChangeLog log{};

    if (_keyStates.at(_currentBufferIndex).find(keyCode) != _keyStates.at(_currentBufferIndex).end()) {
      log = _keyStates.at(_currentBufferIndex).at(keyCode);
    }

    log.pushNewState(keyState);
    _keyStates.at(_currentBufferIndex).insert_or_assign(keyCode, log);
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
