// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#include <NovelRT.h>

using namespace NovelRT::Experimental::Windowing::Glfw;
using namespace NovelRT::Experimental::Graphics::Vulkan;

int main()
{
    GlfwWindowingDevice device{};
    device.Initialise(NovelRT::Windowing::WindowMode::Windowed, "Hello!", NovelRT::Maths::GeoVector2F(400, 400));
    VulkanGraphicsDevice gfxDevice{};
    gfxDevice.Initialise();

    return 0;
}