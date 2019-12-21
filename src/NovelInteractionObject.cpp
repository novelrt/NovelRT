// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "../include/NovelInteractionObject.h"
namespace NovelRT {
InteractionObject::InteractionObject(NovelRT::LayeringService* layeringService,
                                               const NovelRT::CommonArgs& args,
                                               const std::function<void(NovelRT::InteractionObject*)> notifyHasBeenDrawnObject)
    : Transform(layeringService, args) {
  _notifyHasBeenDrawnObject = notifyHasBeenDrawnObject;

}

void InteractionObject::executeObjectBehaviour() {
  _notifyHasBeenDrawnObject(this);
}
KeyCode InteractionObject::getSubscribedKey() const {
  return _subscribedKey;
}
void InteractionObject::setSubscribedKey(KeyCode key) {
  _subscribedKey = key;
}
}
