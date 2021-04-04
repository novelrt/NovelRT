// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_VULKANGRAPHICSDEVICE_H
#define NOVELRT_VULKANGRAPHICSDEVICE_H

#include "../ILLGraphicsDevice.h"
#include <vulkan/vulkan.h>
#include "../../../LoggingService.h"

namespace NovelRT::Experimental::Graphics::Vulkan
{
    class VulkanGraphicsDevice : public ILLGraphicsDevice
    {
    private:
        VkInstance _instance;
        LoggingService _logger;

        void CreateInstance();


    public:
        VulkanGraphicsDevice() noexcept;
        void Initialise() override;
        void TearDown() override;
    };
} // namespace NovelRT::Experimental::Graphics::Vulkan

#endif // NOVELRT_VULKANGRAPHICSDEVICE_H
