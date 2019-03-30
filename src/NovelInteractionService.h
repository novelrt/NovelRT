//
// Created by matth on 22/02/2019.
//

#ifndef NOVELRT_NOVELINPUTSERVICE_H
#define NOVELRT_NOVELINPUTSERVICE_H
#include "NovelInteractionObject.h"
#include "../lib/SDL2/include/SDL_types.h"
#include "KeyCode.h"

namespace NovelRT {
class NovelInteractionService {
public:


  void consumePlayerInput();

  //NovelInteractionObject getInteractionRect(const NovelCommonArgs& args);
private:
  void setLastInteractableDrawn(NovelInteractionObject* target);
  NovelInteractionObject* _target;
  std::map<KeyCode, bool> _keyStates;
  GeoVector<Sint32> _windowClickPosition;
};
}

#endif //NOVELRT_NOVELINPUTSERVICE_H
