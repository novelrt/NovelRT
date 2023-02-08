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
        std::list<UIElement> _elements;
        std::queue<std::function<void()>> _currentCommandList;
        std::queue<std::function<void()>> _previousCommandList;
        std::shared_ptr<NovelRT::ResourceManagement::ResourceLoader> _resourceLoader;
        // bool _editorMode;
        //std::list<IUIElement> _elements;

    public:
        //Utilities::Event<std::reference_wrapper<IUIProvider>> RenderEvent;
        explicit UIProvider(std::list<UIElement> elements, std::queue<std::function<void()>> commandList) :
            _elements(elements), _currentCommandList(commandList),
            _previousCommandList(std::queue<std::function<void()>>()),
            _resourceLoader()
        {}

        virtual void Initialise(std::shared_ptr<NovelRT::ResourceManagement::ResourceLoader> resourceLoader,
            std::shared_ptr<NovelRT::Graphics::GraphicsDevice> gfxDevice,
            std::shared_ptr<NovelRT::Windowing::IWindowingDevice> windowingDevice,
            std::shared_ptr<NovelRT::Input::IInputDevice> inputDevice,
            std::shared_ptr<NovelRT::Graphics::GraphicsProvider> gfxProvider,
            std::shared_ptr<NovelRT::Graphics::GraphicsPipeline> pipeline) = 0;
        virtual ~UIProvider() = default;
        virtual void Begin() = 0;
        virtual void End(std::shared_ptr<NovelRT::Graphics::GraphicsContext> context) = 0;



        // virtual std::shared_ptr<IUITextbox> CreateTextbox(const std::string& identifier, const std::string& text,
        //     bool wordWrap, NovelRT::Maths::GeoVector2F position, NovelRT::Maths::GeoVector2F scale, float fontSize, NovelRT::Graphics::RGBAColour backgroundColour) = 0;

        // virtual std::shared_ptr<IUIButton> CreateButton(const std::string& identifier,
        //     NovelRT::Maths::GeoVector2F position, NovelRT::Maths::GeoVector2F scale, NovelRT::Graphics::RGBAColour backgroundColour) = 0;

        // [[nodiscard]] inline bool& EditorMode() noexcept
        // {
        //     return _editorMode;
        // }

        // [[nodiscard]] inline const bool& EditorMode() const noexcept
        // {
        //     return _editorMode;
        // }


    };
}

#endif // NOVELRT_UI_UIPROVIDER_H
