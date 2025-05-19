#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.


#include <NovelRT/Graphics/ShaderProgram.hpp>
#include <NovelRT/Utilities/Lazy.hpp>
#include <NovelRT/Utilities/Span.hpp>

#include <memory>

#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsDevice;

    class VulkanShaderProgram
    {
    private:
        std::shared_ptr<VulkanGraphicsDevice> _device;
        std::string _entryPointName;
        ShaderProgramKind _kind;
        NovelRT::Utilities::Lazy<VkShaderModule> _shaderModule;
        std::vector<uint8_t> _bytecode;
        VkShaderModuleCreateInfo _shaderModuleCreateInfo;

        VkShaderModule CreateShaderModule();

    public:
        VulkanShaderProgram(VulkanGraphicsDevice* device,
                            std::string entryPointName,
                            ShaderProgramKind kind,
                            NovelRT::Utilities::Span<uint8_t> bytecode) noexcept;

        ~VulkanShaderProgram();

        [[nodiscard]] std::shared_ptr<VulkanGraphicsDevice> GetDevice() const noexcept;
        [[nodiscard]] const std::string& GetEntryPointName() const noexcept;
        [[nodiscard]] ShaderProgramKind GetKind() const noexcept;
        [[nodiscard]] NovelRT::Utilities::Span<const uint8_t> GetBytecode() const noexcept;
        [[nodiscard]] VkShaderModule GetShaderModule();

    };
}
