// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.


#include <NovelRT/Graphics/Vulkan/Graphics.Vulkan.hpp>
#include <NovelRT/Input/Glfw/Input.Glfw.h>
#include <NovelRT/PluginManagement/PluginManagement.h>
#include <NovelRT/PluginManagement/TemporaryFnPtrs.h>
#include <NovelRT/ResourceManagement/Desktop/ResourceManagement.Desktop.h>
#include <NovelRT/Windowing/Glfw/Windowing.Glfw.h>

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBackendTraits.hpp>

namespace NovelRT::PluginManagement
{
    std::shared_ptr<IGraphicsPluginProvider<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>> GetVulkanPluginProvider() noexcept
    {
        return std::make_shared<IGraphicsPluginProvider<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>>();
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
