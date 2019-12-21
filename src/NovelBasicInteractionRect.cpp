// Copyright © Matt Jones and Contributors. Licensed under the MIT LICENCE.md (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Graphics {
BasicInteractionRect::BasicInteractionRect(LayeringService* layeringService,
                                                     const Maths::GeoVector<float>& size,
                                                     const Utilities::CommonArgs& args,
                                                     const std::function<void(Input::InteractionObject*)> notifyHasBeenDrawnObject)
    : InteractionObject(layeringService, args, notifyHasBeenDrawnObject) {

}
bool BasicInteractionRect::validateInteractionPerimeter(const Maths::GeoVector<float>& mousePosition) const {
  GeoVector<float> position = getPosition();
  GeoVector<float> size = getScale();
  return GeoBounds(position, size, getRotation()).pointIsWithinBounds(mousePosition);
}
}
