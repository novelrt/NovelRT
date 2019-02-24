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
  NovelRenderObject(NovelLayeringService* layeringService, NovelRenderingService* renderingService, const float& screenScale, const GeoVector<float>& size,
                    const NovelCommonArgs& args);

  void executeObjectBehaviour() const override;

protected:
  NVGcontext* _drawContext;
  NovelRenderingService* _novelRenderer;
  virtual void drawObject() const = 0;
};
}
#endif //NOVELRT_NOVELRENDEROBJECT_H
