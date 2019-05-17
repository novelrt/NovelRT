//
// Created by matth on 27/02/2019.
//

#ifndef NOVELRT_NOVELTEXTRECT_H
#define NOVELRT_NOVELTEXTRECT_H
#include "NovelRenderObject.h"
#include "RGBAConfig.h"

namespace NovelRT {
class NovelTextRect : public NovelRenderObject {
public:
  NovelTextRect(NovelLayeringService* layeringService, const float& screenScale,
  const std::string_view fontFileDir, const NovelCommonArgs& args);

  void drawObject() const final;

  RGBAConfig getColourConfig() const;

  void setColourConfig(const RGBAConfig& value);

private:
  RGBAConfig _colourConfig;
};
}
#endif //NOVELRT_NOVELTEXTRECT_H
