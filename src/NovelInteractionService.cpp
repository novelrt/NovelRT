// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelInteractionService.h"
#include <SDL2/SDL_events.h>

namespace NovelRT {
NovelInteractionService::NovelInteractionService(NovelLayeringService* layeringService)
    : _clickTarget(nullptr), _layeringService(layeringService) {

  _mousePositionsOnScreenPerButton.insert({KeyCode::LeftMouseButton, GeoVector<float>(0, 0)});
  _keyStates.insert({KeyCode::LeftMouseButton, false});
}

void NovelInteractionService::HandleInteractionDraw(NovelInteractionObject* target) {
  if (_keyStates[target->getSubscribedKey()]
      && target->validateInteractionPerimeter(_mousePositionsOnScreenPerButton[KeyCode::LeftMouseButton])
      && (_clickTarget == nullptr || (target->getLayer() >= _clickTarget->getLayer()
          && target->getOrderInLayer() >= _clickTarget->getOrderInLayer())))
    _clickTarget = target;
}

void NovelInteractionService::consumePlayerInput() {
  for (auto pair : _keyStates) {
    _keyStates[pair.first] = false;
  }

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      raiseQuit();
      return;
    case SDL_MOUSEBUTTONUP:
      if (event.button.button == SDL_BUTTON_LEFT) {
        _mousePositionsOnScreenPerButton[KeyCode::LeftMouseButton].setX(event.button.x);
        _mousePositionsOnScreenPerButton[KeyCode::LeftMouseButton].setY(event.button.y);
        _keyStates[KeyCode::LeftMouseButton] = true;
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
