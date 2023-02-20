// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_GLFWVULKAN_GLFWVULKANUIPROVIDER_H
#define NOVELRT_UI_GLFWVULKAN_GLFWVULKANUIPROVIDER_H

#ifndef NOVELRT_UI_DEARIMGUI_GLFWVULKAN_H
#error NovelRT does not support including types explicitly by default. Please include UI.GlfwVulkan.h instead for the UI::DearImGui::GlfwVulkan namespace subset.
#endif

namespace NovelRT::UI::DearImGui::GlfwVulkan
{
    class GlfwVulkanUIProvider final : public UI::UIProvider
    {
    private:
        NovelRT::Maths::GeoVector2F _windowSize;
        std::map<std::string, ImFont*> _fontNameMapping;
        std::atomic_bool _currentCommandListFinished;
        std::map<const char*, bool> _buttonCache;
        NovelRT::AtomFactory _factory;

        ImGuiKey GlfwVulkanUIProvider::GlfwToImGuiKey(int32_t key);
        void GenerateCommand(std::shared_ptr<UIElement> element);

        //void GeneratePanelCommand(UIPanel& panel);
        //void GenerateButtonCommand(UIButton& button);
        // void GenerateTextboxCommand(UITextbox& textbox);

    protected:
        bool _isInitialised;
        ImGui_ImplVulkan_InitInfo _initInfo;

    public:
        GlfwVulkanUIProvider() noexcept;
        ~GlfwVulkanUIProvider() final;
        void Initialise(std::shared_ptr<NovelRT::ResourceManagement::ResourceLoader> resourceLoader,
                        std::shared_ptr<NovelRT::Graphics::GraphicsDevice> gfxDevice,
                        std::shared_ptr<NovelRT::Windowing::IWindowingDevice> windowingDevice,
                        std::shared_ptr<NovelRT::Input::IInputDevice> inputDevice,
                        std::shared_ptr<NovelRT::Graphics::GraphicsProvider> gfxProvider,
                        std::shared_ptr<NovelRT::Graphics::GraphicsPipeline> pipeline);

        void Begin();
        void End(std::shared_ptr<NovelRT::Graphics::GraphicsContext> context);
        void Update();
        void Render();
        [[nodiscard]] std::shared_ptr<UIPanel> CreatePanel(const char* identifier, NovelRT::Maths::GeoVector2F position,
        NovelRT::Maths::GeoVector2F scale,
        NovelRT::Graphics::RGBAColour colour) final;

    };
}

#endif // NOVELRT_UI_GLFWVULKAN_GLFWVULKANUIPROVIDER_H
