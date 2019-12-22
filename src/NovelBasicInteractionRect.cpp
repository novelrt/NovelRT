// Copyright © Matt Jones and Contributors. Licensed under the MIT LICENCE.md (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Input {
  BasicInteractionRect::BasicInteractionRect(LayeringService* layeringService,
    const Maths::GeoVector<float>& size,
    const Utilities::CommonArgs& args,
    const std::function<void(Input::InteractionObject*)> notifyHasBeenDrawnObject)
    : InteractionObject(layeringService, args, notifyHasBeenDrawnObject) {

  }

  bool BasicInteractionRect::validateInteractionPerimeter(const Maths::GeoVector<float>& mousePosition) const {
    auto position = getPosition();
    auto size = getScale();
    return Maths::GeoBounds(position, size, getRotation()).pointIsWithinBounds(mousePosition);
  }
}
