//
// Created by matth on 22/02/2019.
//

#include "NovelInteractionRect.h"
namespace NovelRT {
NovelInteractionRect::NovelInteractionRect(NovelLayeringService* layeringService,
                                           const float screenScale,
                                           const GeoVector<float>& size,
                                           const NovelCommonArgs& args) :
    NovelObject(layeringService, screenScale, size, args) {}

void NovelInteractionRect::executeObjectBehaviour() const {

}

}