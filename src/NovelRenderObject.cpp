//
// Created by matth on 23/02/2019.
//

#include "NovelRenderObject.h"

namespace NovelRT {
NovelRenderObject::NovelRenderObject(NovelLayeringService* layeringService,
                                     const float screenScale,
                                     const GeoVector<float>& size,
                                     const NovelCommonArgs& args) :
    NovelObject(layeringService, screenScale, size, args) {

}

void NovelRenderObject::executeObjectBehaviour() {
  drawObject();
}
}
