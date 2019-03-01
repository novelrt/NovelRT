//
// Created by matth on 23/02/2019.
//

#include "NovelRenderObject.h"

namespace NovelRT {
NovelRenderObject::NovelRenderObject(NovelRT::NovelLayeringService* layeringService,
                                     NovelRT::NovelRenderingService* renderingService,
                                     const float& screenScale,
                                     const NovelRT::GeoVector<float>& size,
                                     const NovelRT::NovelCommonArgs& args) :
    NovelObject(layeringService, screenScale, size, args) {
  _drawContext = renderingService->getNanoVGContext();

}

void NovelRenderObject::executeObjectBehaviour() const {
  drawObject();
}
}
