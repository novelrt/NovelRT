//
// Created by matth on 23/02/2019.
//

#include "NovelRenderObject.h"

namespace NovelRT {
NovelRenderObject::NovelRenderObject(NovelLayeringService* layeringService,
                                     NovelRenderingService* renderingService,
                                     const float& screenScale,
                                     const GeoVector<float>& size,
                                     const NovelCommonArgs& args) :
    NovelObject(layeringService, screenScale, size, args) {
  _drawContext = renderingService->getNanoVGContext();

}

void NovelRenderObject::executeObjectBehaviour() const {
  drawObject();
}
}
