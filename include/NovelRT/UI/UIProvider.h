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
        Utilities::Event<std::reference_wrapper<UIProvider>> UIEvent;

        virtual void Initialise(std::shared_ptr<NovelRT::Graphics::GraphicsDevice> gfxDevice,
            std::shared_ptr<NovelRT::Windowing::IWindowingDevice> windowingDevice,
            std::shared_ptr<NovelRT::Graphics::GraphicsProvider> gfxProvider,
            std::shared_ptr<NovelRT::Graphics::GraphicsPipeline> pipeline) = 0;
        virtual ~UIProvider() = default;
        virtual void Begin() = 0;
        virtual void End(std::shared_ptr<NovelRT::Graphics::GraphicsContext> context) = 0;

    };
}

#endif // NOVELRT_UI_UIPROVIDER_H
