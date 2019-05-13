//
// Created by matth on 23/02/2019.
//

#ifndef NOVELRT_NOVELRENDEROBJECT_H
#define NOVELRT_NOVELRENDEROBJECT_H
#include "NovelObject.h"
#include "../lib/nanovg/nanovg.h"
#include "NovelRenderingService.h"

namespace NovelRT {
class NovelRenderObject : public NovelObject {
public:
  NovelRenderObject(NovelLayeringService* layeringService, const float screenScale, const GeoVector<float>& size,
                    const NovelCommonArgs& args, NovelRenderingService* renderingService);

  void executeObjectBehaviour() final;

protected:
  NVGcontext* _drawContext;
  NovelRenderingService* _novelRenderer;
  virtual void drawObject() const = 0;

public:
  std::string wew;
};
}
#endif //NOVELRT_NOVELRENDEROBJECT_H
