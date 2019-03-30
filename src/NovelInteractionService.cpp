//
// Created by matth on 22/02/2019.
//

#include "NovelInteractionService.h"
#include "../lib/SDL2/include/SDL_events.h"

namespace NovelRT {
void NovelInteractionService::setLastInteractableDrawn(NovelInteractionObject* const target) {
  _target = target;
}
void NovelInteractionService::consumePlayerInput() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch(event.type) {
    case SDL_QUIT:
      return;
    //case SDL_MOUSEBUTTONDOWN:[[fallthrough]];
    case SDL_MOUSEBUTTONUP:
      if(event.button.button == SDL_BUTTON_LEFT)
      {
        _windowClickPosition = GeoVector<Sint32>(event.button.x, event.button.y);
      }

      break;
    }
/*    if (event.type == SDL_QUIT) {
      exitCode = 0;
      break;
    }*/
  }
}
}