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
    //glfwSetKeyCallback();
    //glfwSetMouseButtonCallback();
    //TODO: enable and add callbacks for mouse buttons and keyboard events


    //auto window = runner->getWindowingService()->getWindow();
    //glfwSetWindowUserPointer(window, this);
    //glfwSetKeyCallback(window, [](auto window, int key, int scancode, int action, int mods) {
    //  auto thisPtr = reinterpret_cast<InteractionService*>(window);
    //  auto result = thisPtr->_keyStates.find(static_cast<KeyCode>(scancode));
    //  thisPtr->_logger.logDebug("Hello lambda!");
    //  });
  }

  void InteractionService::HandleInteractionDraw(InteractionObject* target) {
    if (_keyStates[target->getSubscribedKey()] == KeyState::KeyDown
      && target->validateInteractionPerimeter(_mousePositionsOnScreenPerButton[KeyCode::LeftMouseButton])
      && (_clickTarget == nullptr || (_clickTarget->getLayer() > target->getLayer())))
      _clickTarget = target;
  }

  void InteractionService::consumePlayerInput() {
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
        auto result = Maths::GeoVector<float>(Maths::GeoVector<float>(sdlEvent.button.x, sdlEvent.button.y).getVec4Value() * glm::scale(glm::vec3(1920.0f / _screenSize.getX(), 1080.0f / _screenSize.getY(), 0.0f)));
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
