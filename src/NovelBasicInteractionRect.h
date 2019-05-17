//
// Created by matth on 30/03/2019.
//

#ifndef NOVELRT_NOVELBASICINTERACTIONRECT_H
#define NOVELRT_NOVELBASICINTERACTIONRECT_H

#include "NovelInteractionObject.h"
namespace NovelRT {
class NovelBasicInteractionRect : public NovelInteractionObject {
public:
  NovelBasicInteractionRect(NovelLayeringService* layeringService, const float screenScale, const GeoVector<float>& size,
  const NovelCommonArgs& args, const std::function<void(NovelInteractionObject*)> notifyHasBeenDrawnObject);

  bool validateInteractionPerimeter(const GeoVector<float>& mousePosition) const override;
};
}
#endif //NOVELRT_NOVELBASICINTERACTIONRECT_H
