// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <NovelRT.h>

namespace NovelRT::Input {
  InteractionObject::InteractionObject(Transform transform, int32_t layer, const std::function<void(InteractionObject*)> notifyHasBeenDrawnObject) :
    WorldObject(transform, layer),
    Interacted(Utilities::Event<>()),
    _subscribedKey(KeyCode::LeftMouseButton),
    _notifyHasBeenDrawnObject(notifyHasBeenDrawnObject) {
  }

  void InteractionObject::executeObjectBehaviour() {
    _notifyHasBeenDrawnObject(this);
  }
}
