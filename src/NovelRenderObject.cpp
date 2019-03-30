//
// Created by matth on 23/02/2019.
//

#include "NovelRenderObject.h"

namespace NovelRT {
NovelRenderObject::NovelRenderObject(NovelLayeringService* layeringService,
                                     const float screenScale,
                                     const GeoVector<float>& size,
                                     const NovelCommonArgs& args,
                                     NovelRenderingService* renderingService) :
    NovelObject(layeringService, screenScale, size, args) {
  _drawContext = renderingService->getNanoVGContext();

}

void NovelRenderObject::executeObjectBehaviour() {
  drawObject();
}
}
