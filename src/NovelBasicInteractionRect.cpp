// Copyright © Matt Jones and Contributors. Licensed under the MIT LICENCE.md (MIT). See LICENCE.md in the repository root for more information.

#include "../include/NovelBasicInteractionRect.h"
#include "../include/GeoBounds.h"
namespace NovelRT {
BasicInteractionRect::BasicInteractionRect(LayeringService* layeringService,
                                                     const GeoVector<float>& size,
                                                     const CommonArgs& args,
                                                     const std::function<void(InteractionObject*)> notifyHasBeenDrawnObject)
    : InteractionObject(layeringService, args, notifyHasBeenDrawnObject) {

}
bool BasicInteractionRect::validateInteractionPerimeter(const NovelRT::GeoVector<float>& mousePosition) const {
  GeoVector<float> position = getPosition();
  GeoVector<float> size = getScale();
  return GeoBounds(position, size, getRotation()).pointIsWithinBounds(mousePosition);
}
}
