// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_UIPROVIDER_H
#define NOVELRT_UI_UIPROVIDER_H

#ifndef NOVELRT_UI_H
#error NovelRT does not support including types explicitly by default. Please include UI.h instead for the Windowing namespace subset.
#endif

namespace NovelRT::UI
{
    class UIProvider : public std::enable_shared_from_this<UIProvider>
    {
    protected:
        LoggingService _logger;

    public:
        virtual void Initialise(std::shared_ptr<NovelRT::Graphics::GraphicsDevice> gfxDevice,
            std::shared_ptr<NovelRT::Windowing::IWindowingDevice> windowingDevice,
            void* gfxProvider,
            std::shared_ptr<NovelRT::Graphics::GraphicsPipeline> pipeline) = 0;
        virtual ~UIProvider() = default;
    };
}

#endif // NOVELRT_UI_UIPROVIDER_H
