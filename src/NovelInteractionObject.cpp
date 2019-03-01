//
// Created by matth on 22/02/2019.
//

#include "NovelInteractionObject.h"
namespace NovelRT {
NovelInteractionObject::NovelInteractionObject(NovelLayeringService* layeringService,
                                           const float screenScale,
                                           const GeoVector<float>& size,
                                           const NovelCommonArgs& args) :
    NovelObject(layeringService, screenScale, size, args) {}

void NovelInteractionObject::executeObjectBehaviour() const {
  checkInteractionPerimeter();
}

}