//
// Created by matth on 16/12/2018.
//

#ifndef NOVELRT_NOVELRECT_H
#define NOVELRT_NOVELRECT_H

#include "NovelRenderObject.h"
#include "RGBAConfig.h"

namespace NovelRT {
class NovelBasicFillRect : public NovelRenderObject {
public:
  NovelBasicFillRect(NovelLayeringService* layeringService,
                     const float screenScale,
                     const GeoVector<float>& size,
                     const RGBAConfig& fillColour,
                     const NovelCommonArgs& args,
                     NovelRenderingService* renderingService);

  void drawObject() const override;

  RGBAConfig getColourConfig() const;

  void setColourConfig(const RGBAConfig& value);

private:

  RGBAConfig _colourConfig;

};
}

#endif //NOVELRT_NOVELRECT_H
