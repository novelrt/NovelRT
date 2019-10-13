// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelInteractionObject.h"
namespace NovelRT {
NovelInteractionObject::NovelInteractionObject(NovelRT::NovelLayeringService* layeringService,
                                               const NovelRT::GeoVector<float>& size,
                                               const NovelRT::NovelCommonArgs& args,
                                               const std::function<void(NovelRT::NovelInteractionObject*)> notifyHasBeenDrawnObject)
    : NovelWorldObject(layeringService, size, args) {
  _notifyHasBeenDrawnObject = notifyHasBeenDrawnObject;

}

void NovelInteractionObject::executeObjectBehaviour() {
  _notifyHasBeenDrawnObject(this);
}
KeyCode NovelInteractionObject::getSubscribedKey() const {
  return _subscribedKey;
}
void NovelInteractionObject::setSubscribedKey(const KeyCode key) {
  _subscribedKey = key;
}
}