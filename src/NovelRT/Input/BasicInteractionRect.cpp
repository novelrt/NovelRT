// Copyright © Matt Jones and Contributors. Licensed under the MIT LICENCE.md (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Input {
  BasicInteractionRect::BasicInteractionRect(Transform transform, int32_t layer, const std::function<void(Input::InteractionObject*)> notifyHasBeenDrawnObject)
    : InteractionObject(transform, layer, notifyHasBeenDrawnObject) {}

  bool BasicInteractionRect::validateInteractionPerimeter(Maths::GeoVector2F mousePosition) const {
    auto position = transform().position;
    auto size = transform().scale;
    return Maths::GeoBounds(position, size, transform().rotation).pointIsWithinBounds(mousePosition);
  }
}
