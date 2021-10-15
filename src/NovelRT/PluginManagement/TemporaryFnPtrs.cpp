// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Graphics/Vulkan/Graphics.Vulkan.h>
#include <NovelRT/Experimental/Windowing/Glfw/Windowing.Glfw.h>
#include <NovelRT/PluginManagement/PluginManagement.h>
#include <NovelRT/ResourceManagement/Desktop/ResourceManagement.Desktop.h>
#include <NovelRT/PluginManagement/TemporaryFnPtrs.h>

namespace NovelRT::PluginManagement
{
    std::shared_ptr<IGraphicsPluginProvider> GetVulkanPluginProvider() noexcept
    {
        return std::make_shared<Experimental::Graphics::Vulkan::VulkanGraphicsPluginProvider>();
    }
    std::shared_ptr<IWindowingPluginProvider> GetGlfwPluginProvider() noexcept
    {
        return std::make_shared<Experimental::Windowing::Glfw::GlfwWindowingPluginProvider>();
    }
    std::shared_ptr<IResourceManagementPluginProvider> GetDesktopResourceManagementPluginProvider() noexcept
    {
        return std::make_shared<ResourceManagement::Desktop::DesktopResourceManagementPluginProvider>();
    }
}
