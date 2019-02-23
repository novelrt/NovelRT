//
// Created by matth on 22/02/2019.
//

#include "NovelInteractionRect.h"
namespace NovelRT {
NovelInteractionRect::NovelInteractionRect(NovelRenderingService* novelRenderer,
                                           const float screenScale,
                                           const GeoVector<float>& size,
                                           const NovelCommonArgs& args) :
                                           NovelObject(novelRenderer, screenScale, size, args) {}

}