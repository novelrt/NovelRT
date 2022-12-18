// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_UIPROVIDER_H
#define NOVELRT_UI_UIPROVIDER_H

#ifndef NOVELRT_UI_H
#error NovelRT does not support including types explicitly by default. Please include UI.h instead for the Windowing namespace subset.
#endif

namespace NovelRT::UI
{
    class IUIProvider : public std::enable_shared_from_this<IUIProvider>
    {
    protected:
        LoggingService _logger;
        bool _editorMode;
        //std::list<IUIElement> _elements;

    public:
        Utilities::Event<std::reference_wrapper<IUIProvider>> RenderEvent;

        virtual void Initialise(std::shared_ptr<NovelRT::Graphics::GraphicsDevice> gfxDevice,
            std::shared_ptr<NovelRT::Windowing::IWindowingDevice> windowingDevice,
            std::shared_ptr<NovelRT::Graphics::GraphicsProvider> gfxProvider,
            std::shared_ptr<NovelRT::Graphics::GraphicsPipeline> pipeline) = 0;
        virtual ~IUIProvider() = default;
        virtual void Begin() = 0;
        virtual void End(std::shared_ptr<NovelRT::Graphics::GraphicsContext> context) = 0;
        virtual std::shared_ptr<IUITextbox> CreateTextbox(std::string id, bool wordWrap, std::string text) = 0;

        [[nodiscard]] inline bool& EditorMode() noexcept
        {
            return _editorMode;
        }

        [[nodiscard]] inline const bool& EditorMode() const noexcept
        {
            return _editorMode;
        }


    };
}

#endif // NOVELRT_UI_UIPROVIDER_H
