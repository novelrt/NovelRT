// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_DEARIMGUI_IMGUIUIPLUGINPROVIDER_H
#define NOVELRT_UI_DEARIMGUI_IMGUIUIPLUGINPROVIDER_H

namespace NovelRT::UI::DearImGui
{
    class ImGuiUIPluginProvider final : public PluginManagement::IUIPluginProvider
    {
    protected:
        NovelRT::Utilities::Lazy<std::shared_ptr<ImGuiUIProvider>> _uiProvider;

        [[nodiscard]] std::shared_ptr<ImGuiUIProvider> CreateImGuiUIProviderInternal();

        [[nodiscard]] ImGuiUIProvider* GetUIProviderInternal() override;

    public:
        ImGuiUIPluginProvider() noexcept;
        ~ImGuiUIPluginProvider() final = default;

        [[nodiscard]] inline std::shared_ptr<ImGuiUIProvider> GetUIProvider()
        {
            return std::dynamic_pointer_cast<ImGuiUIProvider>(GetUIProviderInternal()->shared_from_this());
        }
    };
}

#endif // NOVELRT_UI_IMGUI_IMGUIUIPLUGINPROVIDER_H
