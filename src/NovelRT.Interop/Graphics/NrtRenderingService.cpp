// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Graphics/NrtRenderingService.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
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

    NrtResult Nrt_RenderingService_create(NrtWindowingServiceHandle windowingService,
                                          NrtRenderingServiceHandle* outputRenderingService)
    {
        if (windowingService == nullptr || outputRenderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        WindowingService* windowingServicePtr = reinterpret_cast<WindowingService*>(windowingService);

        auto renderingServicePtr = std::make_shared<RenderingService>(windowingServicePtr->shared_from_this());
        _renderingServiceCollection.push_back(renderingServicePtr);
        *outputRenderingService = reinterpret_cast<NrtRenderingServiceHandle>(renderingServicePtr.get());

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderingService_initialiseRendering(NrtRenderingServiceHandle renderingService)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
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

    NrtResult Nrt_RenderingService_tearDown(NrtRenderingServiceHandle renderingService)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);
        renderingServicePtr->tearDown();

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderingService_createImageRectWithFile(NrtRenderingServiceHandle renderingService,
                                                           NrtImageRectHandle* outputImageRect,
                                                           NrtTransform transform,
                                                           int32_t layer,
                                                           const char* filePath,
                                                           NrtRGBAConfigHandle colourTint)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputImageRect == nullptr || filePath == nullptr || colourTint == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);

        _imageRectCollection.push_back(
            renderingServicePtr->createImageRect(*reinterpret_cast<Transform*>(&transform), layer,
                                                 std::string(filePath), *reinterpret_cast<RGBAConfig*>(colourTint)));
        *outputImageRect = reinterpret_cast<NrtImageRectHandle>(_imageRectCollection.back().get());

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderingService_createImageRectWithNothing(NrtRenderingServiceHandle renderingService,
                                                              NrtImageRectHandle* outputImageRect,
                                                              NrtTransform transform,
                                                              int32_t layer,
                                                              NrtRGBAConfigHandle colourTint)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputImageRect == nullptr || colourTint == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);

        _imageRectCollection.push_back(renderingServicePtr->createImageRect(
            *reinterpret_cast<Transform*>(&transform), layer, *reinterpret_cast<RGBAConfig*>(colourTint)));
        *outputImageRect = reinterpret_cast<NrtImageRectHandle>(_imageRectCollection.back().get());

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderingService_createBasicFillRect(NrtRenderingServiceHandle renderingService,
                                                       NrtBasicFillRectHandle* outputBasicFillRect,
                                                       NrtTransform transform,
                                                       int32_t layer,
                                                       NrtRGBAConfigHandle colourConfig)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputBasicFillRect == nullptr || colourConfig == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);

        _basicFillRectCollection.push_back(renderingServicePtr->createBasicFillRect(
            *reinterpret_cast<Transform*>(&transform), layer, *reinterpret_cast<RGBAConfig*>(colourConfig)));
        *outputBasicFillRect = reinterpret_cast<NrtBasicFillRectHandle>(_basicFillRectCollection.back().get());

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderingService_createTextRect(NrtRenderingServiceHandle renderingService,
                                                  NrtTextRectHandle* outputTextRect,
                                                  NrtTransform transform,
                                                  int32_t layer,
                                                  NrtRGBAConfigHandle colourConfig,
                                                  float fontSize,
                                                  const char* fontFilePath)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputTextRect == nullptr || colourConfig == nullptr || fontFilePath == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);

        // DEFINITELY DO NOT DO THIS I AM AWFUL
        _textRectCollection.push_back(renderingServicePtr->createTextRect(
            *reinterpret_cast<Transform*>(&transform), layer, *reinterpret_cast<RGBAConfig*>(colourConfig), fontSize,
            std::string(fontFilePath)));
        *outputTextRect = reinterpret_cast<NrtTextRectHandle>(_textRectCollection.back().get());

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderingService_getCamera(NrtRenderingServiceHandle renderingService, NrtCameraHandle* outputCamera)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputCamera == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);
        *outputCamera = reinterpret_cast<NrtCameraHandle>(renderingServicePtr->getCamera().get());

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderingService_beginFrame(NrtRenderingServiceHandle renderingService)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);
        renderingServicePtr->beginFrame();

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderingService_endFrame(NrtRenderingServiceHandle renderingService)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);
        renderingServicePtr->endFrame();

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderingService_setBackgroundColour(NrtRenderingServiceHandle renderingService,
                                                       NrtRGBAConfigHandle colour)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (colour == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);
        renderingServicePtr->setBackgroundColour(*reinterpret_cast<RGBAConfig*>(colour));

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderingService_getTextureWithNothing(NrtRenderingServiceHandle renderingService,
                                                         NrtTextureHandle* outputTexture)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputTexture == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);
        _textureCollection.push_back(renderingServicePtr->getTexture(""));
        *outputTexture = reinterpret_cast<NrtTextureHandle>(_textureCollection.back().get());

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderingService_getTextureWithFile(NrtRenderingServiceHandle renderingService,
                                                      NrtTextureHandle* outputTexture,
                                                      const char* fileTarget)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputTexture == nullptr || fileTarget == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);

        _textureCollection.push_back(renderingServicePtr->getTexture(std::string(fileTarget)));
        *outputTexture = reinterpret_cast<NrtTextureHandle>(_textureCollection.back().get());

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderingService_getFontSet(NrtRenderingServiceHandle renderingService,
                                              NrtFontSetHandle* outputFontSet,
                                              const char* fileTarget,
                                              float fontSize)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputFontSet == nullptr || fileTarget == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        RenderingService* renderingServicePtr = reinterpret_cast<RenderingService*>(renderingService);

        _fontSetCollection.push_back(renderingServicePtr->getFontSet(std::string(fileTarget), fontSize));
        *outputFontSet = reinterpret_cast<NrtFontSetHandle>(_fontSetCollection.back().get());

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RenderingService_destroy(NrtRenderingServiceHandle renderingService)
    {
        if (renderingService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
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
