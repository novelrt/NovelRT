// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_GLFWVULKAN_GLFWVULKANUIPROVIDER_H
#define NOVELRT_UI_GLFWVULKAN_GLFWVULKANUIPROVIDER_H

#ifndef NOVELRT_UI_DEARIMGUI_GLFWVULKAN_H
#error NovelRT does not support including types explicitly by default. Please include UI.GlfwVulkan.h instead for the UI::DearImGui::GlfwVulkan namespace subset.
#endif

namespace NovelRT::UI::DearImGui::GlfwVulkan
{
    class GlfwVulkanUIProvider final : public UI::IUIProvider
    {
    private:
        std::list<std::shared_ptr<ImGuiTextbox>> _textboxes;
        std::list<std::shared_ptr<ImGuiButton>> _buttons;
        NovelRT::Maths::GeoVector2F _windowSize;

        void Render();
        ImGuiKey GlfwVulkanUIProvider::GlfwToImGuiKey(int32_t key);

    protected:
        bool _isInitialised;
        ImGui_ImplVulkan_InitInfo _initInfo;

    public:
        GlfwVulkanUIProvider() noexcept;
        ~GlfwVulkanUIProvider() final;
        void Initialise(std::shared_ptr<NovelRT::Graphics::GraphicsDevice> gfxDevice,
                        std::shared_ptr<NovelRT::Windowing::IWindowingDevice> windowingDevice,
                        std::shared_ptr<NovelRT::Input::IInputDevice> inputDevice,
                        std::shared_ptr<NovelRT::Graphics::GraphicsProvider> gfxProvider,
                        std::shared_ptr<NovelRT::Graphics::GraphicsPipeline> pipeline);

        void Begin();
        void End(std::shared_ptr<NovelRT::Graphics::GraphicsContext> context);

        std::shared_ptr<IUITextbox> CreateTextbox(const std::string& identifier,
                                                  const std::string& text,
                                                  bool wordWrap,
                                                  NovelRT::Maths::GeoVector2F position,
                                                  NovelRT::Maths::GeoVector2F scale,
                                                  float fontSize,
                                                  NovelRT::Graphics::RGBAColour backgroundColour) final;

        std::shared_ptr<IUIButton> CreateButton(const std::string& identifier,
                                                NovelRT::Maths::GeoVector2F position,
                                                NovelRT::Maths::GeoVector2F scale,
                                                NovelRT::Graphics::RGBAColour backgroundColour) final;
    };
}

#endif // NOVELRT_UI_GLFWVULKAN_GLFWVULKANUIPROVIDER_H
