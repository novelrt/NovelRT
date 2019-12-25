// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <NovelRT.h>

namespace NovelRT::Input {
  InteractionObject::InteractionObject(const Transform& transform, int layer, const std::function<void(InteractionObject*)> notifyHasBeenDrawnObject)
    : WorldObject(transform, layer) {
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
