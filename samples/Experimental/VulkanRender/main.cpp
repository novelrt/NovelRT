// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#include <NovelRT.h>

using namespace NovelRT::Experimental::Windowing::Glfw;
using namespace NovelRT::Experimental::Graphics::Vulkan;

int main()
{
    NovelRT::EngineConfig::EnableDebugOutputFromEngineInternals() = true;
    NovelRT::EngineConfig::MinimumInternalLoggingLevel() = NovelRT::LogLevel::Warn;
    NovelRT::EngineConfig::RequiredVulkanLayers().emplace_back("VK_LAYER_KHRONOS_validation");
    NovelRT::EngineConfig::RequiredVulkanExtensions().emplace_back("VK_EXT_debug_utils");

    GlfwWindowingDevice device{};
    device.Initialise(NovelRT::Windowing::WindowMode::Windowed, NovelRT::Maths::GeoVector2F(400, 400));
    VulkanGraphicsDevice gfxDevice{};
    gfxDevice.Initialise();
    gfxDevice.TearDown();

    return 0;
}