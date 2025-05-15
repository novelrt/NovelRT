// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PLUGINMANAGEMENT_TEMPORARYFNPTRS_H
#define NOVELRT_PLUGINMANAGEMENT_TEMPORARYFNPTRS_H

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;
}

/**
 * @brief This whole header is a hack. It won't be here post-MVP.
 */
namespace NovelRT::PluginManagement
{
    [[nodiscard]] std::shared_ptr<IGraphicsPluginProvider<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>>
    GetVulkanPluginProvider() noexcept;
    [[nodiscard]] std::shared_ptr<IWindowingPluginProvider> GetGlfwWindowPluginProvider() noexcept;
    [[nodiscard]] std::shared_ptr<IInputPluginProvider> GetGlfwInputPluginProvider() noexcept;
    [[nodiscard]] std::shared_ptr<IResourceManagementPluginProvider>
    GetDesktopResourceManagementPluginProvider() noexcept;
}

#endif // NOVELRT_PLUGINMANAGEMENT_TEMPORARYFNPTRS_H
