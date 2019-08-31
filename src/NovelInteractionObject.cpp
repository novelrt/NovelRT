//
// Created by matth on 26/03/2019.
//

#include "NovelInteractionObject.h"
namespace NovelRT {
NovelInteractionObject::NovelInteractionObject(NovelRT::NovelLayeringService* layeringService,
                                               const float screenScale,
                                               const NovelRT::GeoVector<float>& size,
                                               const NovelRT::NovelCommonArgs& args,
                                               const std::function<void(NovelRT::NovelInteractionObject*)> notifyHasBeenDrawnObject)
    : NovelObject(layeringService, screenScale, size, args) {
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