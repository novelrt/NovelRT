// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_GLFWVULKAN_GLFWVULKANUIPLUGINPROVIDER_H
#define NOVELRT_UI_GLFWVULKAN_GLFWVULKANUIPLUGINPROVIDER_H

#ifndef NOVELRT_UI_DEARIMGUI_GLFWVULKAN_H
#error NovelRT does not support including types explicitly by default. Please include UI.DearImGui.GlfwVulkan.h instead for the UI::DearImGui::GlfwVulkan namespace subset.
#endif

namespace NovelRT::UI::DearImGui::GlfwVulkan
{
    class GlfwVulkanUIPluginProvider final : public NovelRT::PluginManagement::IUIPluginProvider
    {
    protected:
        std::shared_ptr<GlfwVulkanUIProvider> _uiProvider;

        [[nodiscard]] GlfwVulkanUIProvider* GetUIProviderInternal() override;

    public:
        GlfwVulkanUIPluginProvider() noexcept;

        [[nodiscard]] inline std::shared_ptr<GlfwVulkanUIProvider> GetUIProvider()
        {
            return std::dynamic_pointer_cast<GlfwVulkanUIProvider>(GetUIProviderInternal()->shared_from_this());
        }
    };
}


#endif // NOVELRT_UI_GLFWVULKAN_GLFWVULKANUIPLUGINPROVIDER_H
