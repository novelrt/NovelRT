// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.Interop/Windowing/NovelRTWindowingService.h"
#include "NovelRT.Interop/Graphics/NovelRTBasicFillRect.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.h"
#include <list>

using namespace NovelRT;
using namespace NovelRT::Graphics;
using namespace NovelRT::Windowing;

  std::list<std::shared_ptr<RenderingService>> _renderingServiceCollection;
  std::list<std::unique_ptr<BasicFillRect>> _basicFillRectCollection;
  std::list<std::unique_ptr<ImageRect>> _imageRectCollection;
  std::list<std::unique_ptr<TextRect>> _textRectCollection;
  std::list<std::shared_ptr<Texture>> _textureCollection;
  std::list<std::shared_ptr<FontSet>> _fontSetCollection;

#ifdef __cplusplus
extern "C" {
#endif

  int32_t NovelRT_RenderingService_create(NovelRTWindowingService windowingService, NovelRTRenderingService* outputRenderingService) {
    if(windowingService == nullptr) {
      return NOVELRT_FAILURE;
    }

    WindowingService* windowingServicePtr = reinterpret_cast<WindowingService*>(windowingService);

    auto renderingServicePtr = std::make_shared<RenderingService>(windowingServicePtr->shared_from_this());
    _renderingServiceCollection.push_back(renderingServicePtr);
    *outputRenderingService = reinterpret_cast<NovelRTRenderingService>(renderingServicePtr.get());

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_RenderingService_initialiseRendering(NovelRTRenderingService renderingService) {
    if(renderingService == nullptr) {
      return NOVELRT_FAILURE;
    }
    
    RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);
    renderingServicePtr->initialiseRendering();

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_RenderingService_tearDown(NovelRTRenderingService renderingService) {
    if(renderingService == nullptr) {
      return NOVELRT_FAILURE;
    }
    
    RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);
    renderingServicePtr->tearDown();

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_RenderingService_createImageRectWithFile(NovelRTRenderingService renderingService, NovelRTImageRect* outputImageRect, NovelRTTransform transform, int32_t layer, const char* filePath, NovelRTRGBAConfig colourTint) {
    if(renderingService == nullptr) {
      return NOVELRT_FAILURE;
    }
    
    RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);

    _imageRectCollection.push_back(renderingServicePtr->createImageRect(*reinterpret_cast<Transform*>(&transform), layer, std::string(filePath), *reinterpret_cast<RGBAConfig*>(colourTint)));
    *outputImageRect = reinterpret_cast<NovelRTImageRect>(_imageRectCollection.back().get());

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_RenderingService_createImageRectWithNothing(NovelRTRenderingService renderingService, NovelRTImageRect* outputImageRect, NovelRTTransform transform, int32_t layer, NovelRTRGBAConfig colourTint) {
    if(renderingService == nullptr) {
      return NOVELRT_FAILURE;
    }
    
    RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);

    _imageRectCollection.push_back(renderingServicePtr->createImageRect(*reinterpret_cast<Transform*>(&transform), layer, *reinterpret_cast<RGBAConfig*>(colourTint)));
    *outputImageRect = reinterpret_cast<NovelRTImageRect>(_imageRectCollection.back().get());

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_RenderingService_createBasicFillRect(NovelRTRenderingService renderingService, NovelRTBasicFillRect* outputBasicFillRect, NovelRTTransform transform, int32_t layer, NovelRTRGBAConfig colourConfig) {
    if(renderingService == nullptr) {
      return NOVELRT_FAILURE;
    }
    
    RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);

    _basicFillRectCollection.push_back(renderingServicePtr->createBasicFillRect(*reinterpret_cast<Transform*>(&transform), layer, *reinterpret_cast<RGBAConfig*>(colourConfig)));
    *outputBasicFillRect = reinterpret_cast<NovelRTBasicFillRect>(_basicFillRectCollection.back().get());

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_RenderingService_createTextRect(NovelRTRenderingService renderingService, NovelRTTextRect* outputTextRect, NovelRTTransform transform, int32_t layer, NovelRTRGBAConfig colourConfig, float fontSize, const char* fontFilePath) {
    if(renderingService == nullptr) {
      return NOVELRT_FAILURE;
    }
    
    RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);
    
    //DEFINITELY DO NOT DO THIS I AM AWFUL
    _textRectCollection.push_back(renderingServicePtr->createTextRect(*reinterpret_cast<Transform*>(&transform), layer, *reinterpret_cast<RGBAConfig*>(colourConfig), fontSize, std::string(fontFilePath)));
    *outputTextRect = reinterpret_cast<NovelRTTextRect>(_textRectCollection.back().get());

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_RenderingService_getCamera(NovelRTRenderingService renderingService, NovelRTCamera* outputCamera) {
    if(renderingService == nullptr) {
      return NOVELRT_FAILURE;
    }
    
    RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);
    *outputCamera = reinterpret_cast<NovelRTCamera>(renderingServicePtr->getCamera().get());

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_RenderingService_beginFrame(NovelRTRenderingService renderingService) {
    if(renderingService == nullptr) {
      return NOVELRT_FAILURE;
    }
    
    RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);
    renderingServicePtr->beginFrame();

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_RenderingService_endFrame(NovelRTRenderingService renderingService) {
    if(renderingService == nullptr) {
      return NOVELRT_FAILURE;
    }
    
    RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);
    renderingServicePtr->endFrame();

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_RenderingService_setBackgroundColour(NovelRTRenderingService renderingService, NovelRTRGBAConfig colour) {
    if(renderingService == nullptr) {
      return NOVELRT_FAILURE;
    }
    
    RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);
    renderingServicePtr->setBackgroundColour(*reinterpret_cast<RGBAConfig*>(colour));

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_RenderingService_getTextureWithNothing(NovelRTRenderingService renderingService, NovelRTTexture* outputTexture) {
    if(renderingService == nullptr) {
      return NOVELRT_FAILURE;
    }
    
    RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);
    _textureCollection.push_back(renderingServicePtr->getTexture("")); 
    *outputTexture = reinterpret_cast<NovelRTTexture>(_textureCollection.back().get());

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_RenderingService_getTextureWithFile(NovelRTRenderingService renderingService, NovelRTTexture* outputTexture, const char* fileTarget) {
    if(renderingService == nullptr) {
      return NOVELRT_FAILURE;
    }
    
    RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);
    
    _textureCollection.push_back(renderingServicePtr->getTexture(std::string(fileTarget)));
    *outputTexture = reinterpret_cast<NovelRTTexture>(_textureCollection.back().get());

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_RenderingService_getFontSet(NovelRTRenderingService renderingService, NovelRTFontSet* outputFontSet, const char* fileTarget, float fontSize) {
    if(renderingService == nullptr) {
      return NOVELRT_FAILURE;
    }
    
    RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);
    
    _fontSetCollection.push_back(renderingServicePtr->getFontSet(std::string(fileTarget), fontSize));
    *outputFontSet = reinterpret_cast<NovelRTFontSet>(_fontSetCollection.back().get());

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_RenderingService_destroy(NovelRTRenderingService renderingService) {
    if(renderingService == nullptr) {
      return NOVELRT_FAILURE;
    }
    
    RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);
    
    
    for (auto& service : _renderingServiceCollection) {
      if(service.get() != renderingServicePtr) {
        continue;
      }

      _renderingServiceCollection.remove(service);
        
      return NOVELRT_SUCCESS;
    }

    return NOVELRT_FAILURE;
  }

#ifdef __cplusplus
}
#endif