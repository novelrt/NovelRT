// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef DUMMYRENDERINGSERVICEFACTORY_H
#define DUMMYRENDERINGSERVICEFACTORY_H

#include <NovelRT.h>

using namespace NovelRT;

//these are the best stubs ive ever made seriously wow 10/10
class DummyRenderingService : public Graphics::IRenderingService {
private:
  std::shared_ptr<Graphics::Camera> _camera;

public:
  DummyRenderingService(std::shared_ptr<Windowing::WindowingService> windowingService) noexcept : Graphics::IRenderingService(windowingService) {
    _camera = nullptr;
  };

    virtual int initialiseRendering() final;
    virtual void tearDown() final;

    virtual std::unique_ptr<Graphics::ImageRect> createImageRect(const Transform& transform, int layer, const std::string& filePath, const Graphics::RGBAConfig& colourTint = Graphics::RGBAConfig(255, 255, 255, 255)) final;

    virtual std::unique_ptr<Graphics::ImageRect> createImageRect(const Transform& transform, int layer, const Graphics::RGBAConfig& colourTint = Graphics::RGBAConfig(255, 255, 255, 255)) final;

    virtual std::unique_ptr<Graphics::BasicFillRect> createBasicFillRect(const Transform& transform, int layer, const Graphics::RGBAConfig& colourConfig) final;

    virtual std::unique_ptr<Graphics::TextRect> createTextRect(const Transform& transform, int layer, const Graphics::RGBAConfig& colourConfig, float fontSize, const std::string& fontFilePath) final;

    virtual std::weak_ptr<Graphics::Camera> getCamera() const final;

    virtual void beginFrame() const final;
    virtual void endFrame() const final;

    virtual void setBackgroundColour(const Graphics::RGBAConfig& colour) final;

    virtual std::shared_ptr<Graphics::Texture> getTexture(const std::string& fileTarget = "") final;
    virtual std::shared_ptr<Graphics::FontSet> getFontSet(const std::string& fileTarget, float fontSize) final; 
};

class DummyRenderingServiceFactory : public Graphics::IRenderingServiceFactory {
public:
  inline std::shared_ptr<Graphics::IRenderingService> create() override {
      return std::static_pointer_cast<Graphics::IRenderingService>(std::make_shared<DummyRenderingService>(std::shared_ptr<Windowing::WindowingService>(nullptr)));
  }
};

#endif
