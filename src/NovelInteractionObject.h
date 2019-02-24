//
// Created by matth on 22/02/2019.
//

#ifndef NOVELRT_NOVELINTERACTIONRECT_H
#define NOVELRT_NOVELINTERACTIONRECT_H

#include "NovelObject.h"

namespace NovelRT {
class NovelInteractionObject : public NovelObject {
public:
  NovelInteractionObject(NovelLayeringService* layeringService, const float screenScale, const GeoVector<float>& size,
                       const NovelCommonArgs& args);

  void executeObjectBehaviour() const final;
  virtual void checkInteractionPerimeter() const = 0;

};
}

#endif //NOVELRT_NOVELINTERACTIONRECT_H
