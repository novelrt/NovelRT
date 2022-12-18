// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/UI/DearImGui/GlfwVulkan/UI.DearImGui.GlfwVulkan.h>

namespace NovelRT::UI::DearImGui::GlfwVulkan
{
    GlfwVulkanUIPluginProvider::GlfwVulkanUIPluginProvider() noexcept : _uiProvider(std::make_shared<GlfwVulkanUIProvider>())
    {
    }

    GlfwVulkanUIProvider* GlfwVulkanUIPluginProvider::GetUIProviderInternal()
    {
        return _uiProvider.get();
    }
}
