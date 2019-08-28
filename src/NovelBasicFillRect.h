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
                     const GLuint programId);

  void drawObject() const final;

  RGBAConfig getColourConfig() const;

  void setColourConfig(const RGBAConfig& value);

  ~NovelBasicFillRect();

protected:
  virtual void configureObjectBuffers(bool refreshBuffers = false) override;

private:

  RGBAConfig _colourConfig;
  GLuint _colourBuffer;
  std::vector<GLfloat> _colourData;
};
}

#endif //NOVELRT_NOVELRECT_H
