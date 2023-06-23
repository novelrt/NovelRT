// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

//TODO: Hacky hack, fix this before merging.
#if defined(_WIN32)
#include <NovelRT/ResourceManagement/Windows/ResourceManagement.Desktop.h>
#else
#include <NovelRT/ResourceManagement/Linux/ResourceManagement.Desktop.h>
#endif

#include <NovelRT/Graphics/Vulkan/Graphics.Vulkan.h>
#include <NovelRT/Input/Glfw/Input.Glfw.h>
#include <NovelRT/PluginManagement/PluginManagement.h>
#include <NovelRT/PluginManagement/TemporaryFnPtrs.h>
#include <NovelRT/Windowing/Glfw/Windowing.Glfw.h>



namespace NovelRT::PluginManagement
{
    std::shared_ptr<IGraphicsPluginProvider> GetVulkanPluginProvider() noexcept
    {
        return std::make_shared<Graphics::Vulkan::VulkanGraphicsPluginProvider>();
    }
    std::shared_ptr<IWindowingPluginProvider> GetGlfwWindowPluginProvider() noexcept
    {
        return std::make_shared<Windowing::Glfw::GlfwWindowingPluginProvider>();
    }
    std::shared_ptr<IResourceManagementPluginProvider> GetDesktopResourceManagementPluginProvider() noexcept
    {
        return std::make_shared<ResourceManagement::Desktop::DesktopResourceManagementPluginProvider>();
    }
    std::shared_ptr<IInputPluginProvider> GetGlfwInputPluginProvider() noexcept
    {
        return std::make_shared<Input::Glfw::GlfwInputPluginProvider>();
    }
}
