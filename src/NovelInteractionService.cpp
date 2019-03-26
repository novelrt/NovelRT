//
// Created by matth on 22/02/2019.
//

#include "NovelInteractionService.h"

namespace NovelRT {
void NovelInteractionService::setLastInteractableDrawn(const NovelInteractionObject* target) {
  _target = target;
}
}