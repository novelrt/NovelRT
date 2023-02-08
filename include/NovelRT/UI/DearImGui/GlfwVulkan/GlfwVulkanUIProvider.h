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
        // std::list<std::shared_ptr<ImGuiTextbox>> _textboxes;
        // std::list<std::shared_ptr<ImGuiButton>> _buttons;
        NovelRT::Maths::GeoVector2F _windowSize;
        std::map<std::string, ImFont*> _fontNameMapping;

        void Render();
        ImGuiKey GlfwVulkanUIProvider::GlfwToImGuiKey(int32_t key);
        void GenerateCommand(UIElement& element);

        void GeneratePanelCommand(UIPanel& panel);

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

    };
}

#endif // NOVELRT_UI_GLFWVULKAN_GLFWVULKANUIPROVIDER_H
