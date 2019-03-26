//
// Created by matth on 25/03/2019.
//

#include "NovelInteractionObject.h"
#include "NovelInteractionService.h"

namespace NovelRT {

void NovelInteractionObject::executeObjectBehaviour() const {
  setLastDrawn(this);

}
void NovelInteractionObject::setLastDrawn(const NovelInteractionObject* target) const {
  _interactionService->setLastInteractableDrawn(target);
}
}