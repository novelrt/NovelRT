// Copyright © Matt Jones and Contributors. Licensed under the MIT LICENCE.md (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Input {
  BasicInteractionRect::BasicInteractionRect(const Transform& transform, int layer, const std::function<void(Input::InteractionObject*)> notifyHasBeenDrawnObject)
    : InteractionObject(transform, layer, notifyHasBeenDrawnObject) {}

  bool BasicInteractionRect::validateInteractionPerimeter(const Maths::GeoVector<float>& mousePosition) const {
    auto position = getTransformReadonly().getPosition();
    auto size = getTransformReadonly().getScale();
    return Maths::GeoBounds(position, size, getTransformReadonly().getRotation()).pointIsWithinBounds(mousePosition);
  }
}
