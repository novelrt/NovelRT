//
// Created by matth on 26/03/2019.
//

#ifndef NOVELRT_NOVELINTERACTIONOBJECT_H
#define NOVELRT_NOVELINTERACTIONOBJECT_H
#include <functional>
#include "NovelObject.h"

namespace NovelRT {
class NovelInteractionObject : NovelObject {
public:
  NovelInteractionObject(NovelLayeringService* layeringService, const float screenScale, const GeoVector<float>& size,
                         const NovelCommonArgs& args, const std::function<void(const NovelInteractionObject*)> notifyHasBeenDrawnObject);
  void executeObjectBehaviour() const final;
  virtual void checkInteractionPerimeter(const GeoVector<float>& mousePosition) const = 0;

private:
  std::function<void(const NovelInteractionObject*)> _notifyHasBeenDrawnObject;
};
}
#endif //NOVELRT_NOVELINTERACTIONOBJECT_H
