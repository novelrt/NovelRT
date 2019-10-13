// Copyright © Matt Jones and Contributors. Licensed under the MIT LICENCE.md (MIT). See LICENCE.md in the repository root for more information.

#include "NovelBasicInteractionRect.h"
#include "GeoBounds.h"
namespace NovelRT {
NovelBasicInteractionRect::NovelBasicInteractionRect(NovelLayeringService* layeringService,
                                                     const GeoVector<float>& size,
                                                     const NovelCommonArgs& args,
                                                     const std::function<void(NovelInteractionObject*)> notifyHasBeenDrawnObject)
    : NovelInteractionObject(layeringService, size, args, notifyHasBeenDrawnObject) {

}
bool NovelBasicInteractionRect::validateInteractionPerimeter(const NovelRT::GeoVector<float>& mousePosition) const {
  GeoVector<float> position = getPosition(); // * _screenScale;
  GeoVector<float> size = getSize(); // * _screenScale;
  return GeoBounds(position, size, getRotation()).pointIsWithinBounds(mousePosition);
}
}