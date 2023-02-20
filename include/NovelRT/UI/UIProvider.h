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
        std::map<NovelRT::Atom, std::shared_ptr<UIElement>> _elements;
        std::vector<std::function<void()>> _currentCommandList;
        std::vector<std::function<void()>> _previousCommandList;
        std::shared_ptr<NovelRT::ResourceManagement::ResourceLoader> _resourceLoader;

    public:
        explicit UIProvider() :
            _elements(std::map<NovelRT::Atom, std::shared_ptr<UIElement>>()), _currentCommandList(std::vector<std::function<void()>>()),
            _previousCommandList(std::vector<std::function<void()>>()),
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
        virtual void Update() = 0;
        virtual void Render() = 0;
        [[nodiscard]] virtual std::shared_ptr<UIPanel> CreatePanel(const char* identifier, NovelRT::Maths::GeoVector2F position,
        NovelRT::Maths::GeoVector2F scale,
        NovelRT::Graphics::RGBAColour colour) = 0;

    };
}

#endif // NOVELRT_UI_UIPROVIDER_H
