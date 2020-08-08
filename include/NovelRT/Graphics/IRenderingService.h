// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_GRAPHICS_IRENDERINGSERVICE_H
#define NOVELRT_GRAPHICS_IRENDERINGSERVICE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Graphics {
  class IRenderingService {
  protected:
    std::shared_ptr<Windowing::WindowingService> _windowingService;

  public:
    IRenderingService(std::shared_ptr<Windowing::WindowingService> windowingService) noexcept : _windowingService(windowingService){};
    virtual int initialiseRendering() = 0;
    virtual void tearDown() = 0;

    virtual std::unique_ptr<ImageRect> createImageRect(const Transform& transform, int layer, const std::string& filePath, const RGBAConfig& colourTint = RGBAConfig(255, 255, 255, 255)) = 0;

    virtual std::unique_ptr<ImageRect> createImageRect(const Transform& transform, int layer, const RGBAConfig& colourTint = RGBAConfig(255, 255, 255, 255)) = 0;

    virtual std::unique_ptr<BasicFillRect> createBasicFillRect(const Transform& transform, int layer, const RGBAConfig& colourConfig) = 0;

    virtual std::unique_ptr<TextRect> createTextRect(const Transform& transform, int layer, const RGBAConfig& colourConfig, float fontSize, const std::string& fontFilePath) = 0;

    virtual std::weak_ptr<Camera> getCamera() const = 0;

    virtual void beginFrame() const = 0;
    virtual void endFrame() const = 0;

    virtual void setBackgroundColour(const RGBAConfig& colour) = 0;

    virtual std::shared_ptr<Texture> getTexture(const std::string& fileTarget = "") = 0;
    virtual std::shared_ptr<FontSet> getFontSet(const std::string& fileTarget, float fontSize) = 0; 
  };
}

#endif
