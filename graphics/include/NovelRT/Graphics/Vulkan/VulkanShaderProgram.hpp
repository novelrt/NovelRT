#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <memory>
#include <vulkan/vulkan.h>
#include <NovelRT/Graphics/ShaderProgram.hpp>
#include <NovelRT/Utilities/Lazy.h>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsDevice;

    class VulkanShaderProgram
    {
    private:
        NovelRT::Utilities::Lazy<VkShaderModule> _shaderModule;
        std::vector<uint8_t> _bytecode;
        VkShaderModuleCreateInfo _shaderModuleCreateInfo;

        VkShaderModule CreateShaderModule();

    public:
        VulkanShaderProgram(std::shared_ptr<VulkanGraphicsDevice> device,
                            std::string entryPointName,
                            ShaderProgramKind kind,
                            NovelRT::Utilities::Misc::Span<uint8_t> bytecode) noexcept;

        [[nodiscard]] NovelRT::Utilities::Misc::Span<const uint8_t> GetBytecode() const noexcept;
        [[nodiscard]] VkShaderModule GetShaderModule();

        ~VulkanShaderProgram();
    };
}
