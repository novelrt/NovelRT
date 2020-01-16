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
        _logger.logDebug("Held reached!");
        _keyStates.at(code) = KeyState::KeyDownHeld;
      }
      else if (_keyStates.at(code) != KeyState::KeyDownHeld) {
        _logger.logDebug("KeyState before: ", _keyStates.at(code));
        _keyStates.at(code) = KeyState::KeyDown;
        _logger.logDebug("KeyState after: ", _keyStates.at(code));
      }
      break;
    case KeyState::KeyDownHeld:
    case KeyState::KeyUp:
      _keyStates.at(code) = (_keyStates.at(code) == KeyState::KeyUp)? KeyState::Idle : state; //lmao
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
      && (_clickTarget == nullptr || (_clickTarget->getLayer() > target->getLayer())))
      _clickTarget = target;
  }

  void InteractionService::consumePlayerInput() {
    processKeyState(KeyCode::LeftMouseButton, _keyStates.at(KeyCode::LeftMouseButton));

    glfwPollEvents();
  }
  /*
    void InteractionService::consumePlayerInput() {
      SDL_Event sdlEvent;

      for (auto& pair : _keyStates) {

        if (pair.second == KeyState::KeyDown) _keyStates[pair.first] = KeyState::KeyDownHeld;
        if (pair.second != KeyState::KeyUp) continue;

        pair.second = KeyState::Idle;
      }

      while (SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type) {
        case SDL_QUIT:
          raiseQuit();
          return;
        case SDL_MOUSEBUTTONDOWN: {
          auto result = Maths::GeoVector<float>(Maths::GeoVector<float>(sdlEvent.button.x, sdlEvent.button.y));
          if (sdlEvent.button.button == SDL_BUTTON_LEFT) {
            _mousePositionsOnScreenPerButton[KeyCode::LeftMouseButton].setX(result.getX());
            _mousePositionsOnScreenPerButton[KeyCode::LeftMouseButton].setY(result.getY());

            _keyStates[KeyCode::LeftMouseButton] = KeyState::KeyDown;
          }
          else if (sdlEvent.button.button == SDL_BUTTON_RIGHT) {
            _mousePositionsOnScreenPerButton[KeyCode::RightMouseButton].setX(result.getX());
            _mousePositionsOnScreenPerButton[KeyCode::RightMouseButton].setY(result.getY());

            _keyStates[KeyCode::RightMouseButton] = KeyState::KeyDown;
          }

        }
          break;
        case SDL_MOUSEBUTTONUP: {
          if (sdlEvent.button.button == SDL_BUTTON_LEFT) {
            auto result = Maths::GeoVector<float>(Maths::GeoVector<float>(sdlEvent.button.x, sdlEvent.button.y).getVec4Value() * glm::scale(glm::vec3(1920.0f / _screenSize.getX(), 1080.0f / _screenSize.getY(), 0.0f)));
            _mousePositionsOnScreenPerButton[KeyCode::LeftMouseButton].setX(result.getX());
            _mousePositionsOnScreenPerButton[KeyCode::LeftMouseButton].setY(result.getY());
            _keyStates[KeyCode::LeftMouseButton] = KeyState::KeyUp;
          }
        }
          break;
        case SDL_KEYDOWN: {
          auto keyDownCode = static_cast<KeyCode>(sdlEvent.key.keysym.sym); //TODO: This is gonna break in certain situations. New input system should be implemented ASAP.
          _keyStates.insert({ keyDownCode, KeyState::Idle });
          _keyStates[keyDownCode] = KeyState::KeyDown;

        }
          break;
        case SDL_KEYUP: {
          auto keyUpCode = static_cast<KeyCode>(sdlEvent.key.keysym.sym); //TODO: This is gonna break in certain situations. New input system should be implemented ASAP.
          _keyStates[keyUpCode] = KeyState::KeyUp;
        }
          break;

        case SDL_WINDOWEVENT: {
          if (sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
            _logger.log("Resize input detected! notifying subscribers...", LogLevel::Info);
            raiseResizeInputDetected(Maths::GeoVector<float>(sdlEvent.window.data1, sdlEvent.window.data2));
          }
        }
          break;
        }
      }
    }
  */

  std::unique_ptr<BasicInteractionRect> InteractionService::createBasicInteractionRect(const Transform& transform, int layer) {
    return std::make_unique<BasicInteractionRect>(transform, layer, [this](InteractionObject* x) { HandleInteractionDraw(x); });
  }
  void InteractionService::executeClickedInteractable() {
    if (_clickTarget == nullptr) return;

    _clickTarget->raiseInteracted();
    _clickTarget = nullptr;
  }
}
