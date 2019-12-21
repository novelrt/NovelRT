// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "../include/NovelInteractionService.h"
#include "../include/NovelInteractionService.h"
#include <SDL2/SDL_events.h>

namespace NovelRT {
  NovelInteractionService::NovelInteractionService(NovelLayeringService* const layeringService)
    : _clickTarget(nullptr), _layeringService(layeringService) {
    _mousePositionsOnScreenPerButton.insert({ KeyCode::LeftMouseButton, GeoVector<float>(0, 0) });
    _keyStates.insert({ KeyCode::LeftMouseButton, KeyState::Idle });
    _keyStates.insert({ KeyCode::RightMouseButton, KeyState::Idle });
  }

  void NovelInteractionService::HandleInteractionDraw(NovelInteractionObject* target) {
    if (_keyStates[target->getSubscribedKey()] != KeyState::KeyDown
      && target->validateInteractionPerimeter(_mousePositionsOnScreenPerButton[KeyCode::LeftMouseButton])
      && (_clickTarget == nullptr || (target->getLayer() >= _clickTarget->getLayer()
        && target->getOrderInLayer() >= _clickTarget->getOrderInLayer())))
      _clickTarget = target;
  }

  void NovelInteractionService::consumePlayerInput() {
    SDL_Event sdlEvent;

    for (auto& pair : _keyStates) {
      if (pair.second != KeyState::KeyUp) continue;
      pair.second = KeyState::Idle;
    }

    while (SDL_PollEvent(&sdlEvent)) {
      switch (sdlEvent.type) {
      case SDL_QUIT:
        raiseQuit();
        return;
      case SDL_MOUSEBUTTONDOWN: {
        auto result = GeoVector<float>(GeoVector<float>(sdlEvent.button.x, sdlEvent.button.y).getVec4Value() * glm::scale(glm::vec3(1920.0f / _screenSize.getX(), 1080.0f / _screenSize.getY(), 0.0f)));

        if (sdlEvent.button.button == SDL_BUTTON_LEFT) {
          _mousePositionsOnScreenPerButton[KeyCode::LeftMouseButton].setX(result.getX());
          _mousePositionsOnScreenPerButton[KeyCode::LeftMouseButton].setY(result.getY());

          if (_keyStates[KeyCode::LeftMouseButton] == KeyState::KeyDown) {
            _keyStates[KeyCode::LeftMouseButton] = KeyState::KeyDownHeld;
          }
          else {
            _keyStates[KeyCode::LeftMouseButton] = KeyState::KeyDown;
          }
        }
        else if (sdlEvent.button.button == SDL_BUTTON_RIGHT) {
          _mousePositionsOnScreenPerButton[KeyCode::RightMouseButton].setX(result.getX());
          _mousePositionsOnScreenPerButton[KeyCode::RightMouseButton].setY(result.getY());

          if (_keyStates[KeyCode::RightMouseButton] == KeyState::KeyDown) {
            _keyStates[KeyCode::RightMouseButton] = KeyState::KeyDownHeld;
          }
          else {
            _keyStates[KeyCode::RightMouseButton] = KeyState::KeyDown;
          }
        }

      }
        break;
      case SDL_MOUSEBUTTONUP: {
        if (sdlEvent.button.button == SDL_BUTTON_LEFT) {
          auto result = GeoVector<float>(GeoVector<float>(sdlEvent.button.x, sdlEvent.button.y).getVec4Value() * glm::scale(glm::vec3(1920.0f / _screenSize.getX(), 1080.0f / _screenSize.getY(), 0.0f)));
          _mousePositionsOnScreenPerButton[KeyCode::LeftMouseButton].setX(result.getX());
          _mousePositionsOnScreenPerButton[KeyCode::LeftMouseButton].setY(result.getY());
          _keyStates[KeyCode::LeftMouseButton] = KeyState::KeyUp;
        }
        break;
      case SDL_KEYDOWN:
        auto keyDownCode = static_cast<KeyCode>(sdlEvent.key.keysym.sym); //TODO: This is gonna break in certain situations. New input system should be implemented ASAP.
        _keyStates.insert({ keyDownCode, KeyState::Idle });
        if (_keyStates[keyDownCode] == KeyState::KeyDown) {
          _keyStates[keyDownCode] = KeyState::KeyDownHeld;
        }
        else {
          _keyStates[keyDownCode] = KeyState::KeyDown;
        }

      }
         break;
      case SDL_KEYUP: {
        auto keyUpCode = static_cast<KeyCode>(sdlEvent.key.keysym.sym); //TODO: This is gonna break in certain situations. New input system should be implemented ASAP.
        _keyStates[keyUpCode] = KeyState::KeyUp;
      }
        break;
      }
    }
  }

  NovelBasicInteractionRect* NovelInteractionService::getBasicInteractionRect(const GeoVector<float>& startingSize,
    const NovelCommonArgs& args) {
    return new NovelBasicInteractionRect(_layeringService,
      startingSize,
      args,
      [this](NovelInteractionObject* x) { HandleInteractionDraw(x); });
  }
  void NovelInteractionService::ExecuteClickedInteractable() {
    if (_clickTarget == nullptr) return;

    _clickTarget->raiseInteracted();
    _clickTarget = nullptr;
  }
}
