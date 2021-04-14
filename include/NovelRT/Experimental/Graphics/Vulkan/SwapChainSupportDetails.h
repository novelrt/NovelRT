// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_SWAPCHAINSUPPORTDETAILS_H
#define NOVELRT_SWAPCHAINSUPPORTDETAILS_H

#include <vector>
#include <vulkan/vulkan.h>

namespace NovelRT::Experimental::Graphics::Vulkan
{
    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };
} // namespace NovelRT::Experimental::Graphics::Vulkan

#endif // NOVELRT_SWAPCHAINSUPPORTDETAILS_H
