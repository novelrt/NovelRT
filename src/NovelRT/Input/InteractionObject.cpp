// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <NovelRT.h>

namespace NovelRT::Input {
  InteractionObject::InteractionObject(LayeringService* layeringService,
    const Utilities::CommonArgs& args,
    const std::function<void(InteractionObject*)> notifyHasBeenDrawnObject)
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
