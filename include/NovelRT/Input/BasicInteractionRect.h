// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELBASICINTERACTIONRECT_H
#define NOVELRT_NOVELBASICINTERACTIONRECT_H

#include "NovelInteractionObject.h"
namespace NovelRT::Input {

  class BasicInteractionRect : public InteractionObject {
  public:
    BasicInteractionRect(NovelLayeringService* layeringService, const GeoVector<float>& size,
      const CommonArgs& args, const std::function<void(InteractionObject*)> notifyHasBeenDrawnObject);
    bool validateInteractionPerimeter(const GeoVector<float>& mousePosition) const override;
  };
}
#endif //NOVELRT_NOVELBASICINTERACTIONRECT_H
