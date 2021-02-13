// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Graphics/NrtBasicFillRect.h>
#include <NovelRT.Interop/NrtInteropErrorHandlingInternal.h>
#include <NovelRT.Interop/NrtInteropUtils.h>
#include <NovelRT.Interop/Windowing/NrtWindowingService.h>
#include <NovelRT.h>
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
extern "C"
{
#endif

    NrtResult Nrt_RenderingService_create(NrtWindowingService windowingService,
                                          NrtRenderingService* outputRenderingService)
    {
        if (windowingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        WindowingService* windowingServicePtr = reinterpret_cast<WindowingService*>(windowingService);

        auto renderingServicePtr = std::make_shared<RenderingService>(windowingServicePtr->shared_from_this());
        _renderingServiceCollection.push_back(renderingServicePtr);
        *outputRenderingService = reinterpret_cast<NrtRenderingService>(renderingServicePtr.get());

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderingService_initialiseRendering(NrtRenderingService renderingService)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);

        try
        {
            renderingServicePtr->initialiseRendering();
        }
        catch (const Exceptions::InitialisationFailureException)
        {
            Nrt_setErrMsgIsInitialisationFailureInternal();
            return NRT_FAILURE_INITIALISATION_FAILURE;
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderingService_tearDown(NrtRenderingService renderingService)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);
        renderingServicePtr->tearDown();

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderingService_createImageRectWithFile(NrtRenderingService renderingService,
                                                           NrtImageRect* outputImageRect,
                                                           NrtTransform transform,
                                                           int32_t layer,
                                                           const char* filePath,
                                                           NrtRGBAConfig colourTint)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);

        _imageRectCollection.push_back(
            renderingServicePtr->createImageRect(*reinterpret_cast<Transform*>(&transform), layer,
                                                 std::string(filePath), *reinterpret_cast<RGBAConfig*>(colourTint)));
        *outputImageRect = reinterpret_cast<NrtImageRect>(_imageRectCollection.back().get());

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderingService_createImageRectWithNothing(NrtRenderingService renderingService,
                                                              NrtImageRect* outputImageRect,
                                                              NrtTransform transform,
                                                              int32_t layer,
                                                              NrtRGBAConfig colourTint)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);

        _imageRectCollection.push_back(renderingServicePtr->createImageRect(
            *reinterpret_cast<Transform*>(&transform), layer, *reinterpret_cast<RGBAConfig*>(colourTint)));
        *outputImageRect = reinterpret_cast<NrtImageRect>(_imageRectCollection.back().get());

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderingService_createBasicFillRect(NrtRenderingService renderingService,
                                                       NrtBasicFillRect* outputBasicFillRect,
                                                       NrtTransform transform,
                                                       int32_t layer,
                                                       NrtRGBAConfig colourConfig)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);

        _basicFillRectCollection.push_back(renderingServicePtr->createBasicFillRect(
            *reinterpret_cast<Transform*>(&transform), layer, *reinterpret_cast<RGBAConfig*>(colourConfig)));
        *outputBasicFillRect = reinterpret_cast<NrtBasicFillRect>(_basicFillRectCollection.back().get());

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderingService_createTextRect(NrtRenderingService renderingService,
                                                  NrtTextRect* outputTextRect,
                                                  NrtTransform transform,
                                                  int32_t layer,
                                                  NrtRGBAConfig colourConfig,
                                                  float fontSize,
                                                  const char* fontFilePath)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);

        // DEFINITELY DO NOT DO THIS I AM AWFUL
        _textRectCollection.push_back(renderingServicePtr->createTextRect(
            *reinterpret_cast<Transform*>(&transform), layer, *reinterpret_cast<RGBAConfig*>(colourConfig), fontSize,
            std::string(fontFilePath)));
        *outputTextRect = reinterpret_cast<NrtTextRect>(_textRectCollection.back().get());

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderingService_getCamera(NrtRenderingService renderingService, NrtCamera* outputCamera)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);
        *outputCamera = reinterpret_cast<NrtCamera>(renderingServicePtr->getCamera().get());

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderingService_beginFrame(NrtRenderingService renderingService)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);
        renderingServicePtr->beginFrame();

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderingService_endFrame(NrtRenderingService renderingService)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);
        renderingServicePtr->endFrame();

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderingService_setBackgroundColour(NrtRenderingService renderingService, NrtRGBAConfig colour)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);
        renderingServicePtr->setBackgroundColour(*reinterpret_cast<RGBAConfig*>(colour));

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderingService_getTextureWithNothing(NrtRenderingService renderingService,
                                                         NrtTexture* outputTexture)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);
        _textureCollection.push_back(renderingServicePtr->getTexture(""));
        *outputTexture = reinterpret_cast<NrtTexture>(_textureCollection.back().get());

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderingService_getTextureWithFile(NrtRenderingService renderingService,
                                                      NrtTexture* outputTexture,
                                                      const char* fileTarget)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);

        _textureCollection.push_back(renderingServicePtr->getTexture(std::string(fileTarget)));
        *outputTexture = reinterpret_cast<NrtTexture>(_textureCollection.back().get());

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderingService_getFontSet(NrtRenderingService renderingService,
                                              NrtFontSet* outputFontSet,
                                              const char* fileTarget,
                                              float fontSize)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);

        _fontSetCollection.push_back(renderingServicePtr->getFontSet(std::string(fileTarget), fontSize));
        *outputFontSet = reinterpret_cast<NrtFontSet>(_fontSetCollection.back().get());

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderingService_destroy(NrtRenderingService renderingService)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);

        for (auto& service : _renderingServiceCollection)
        {
            if (service.get() != renderingServicePtr)
            {
                continue;
            }

            _renderingServiceCollection.remove(service);

            return NRT_SUCCESS;
        }

        Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
        return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
    }

#ifdef __cplusplus
}
#endif
