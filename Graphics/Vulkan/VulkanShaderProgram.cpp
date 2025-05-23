// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanShaderProgram.hpp>

namespace NovelRT::Graphics::Vulkan
{
    VulkanShaderProgram::VulkanShaderProgram(std::shared_ptr<VulkanGraphicsDevice> device,
                                             std::string entryPointName,
                                             ShaderProgramKind kind,
                                             NovelRT::Utilities::Misc::Span<uint8_t> bytecode) noexcept
        : _device(device),
          _entryPointName(entryPointName),
          _kind(kind),
          _shaderModule(NovelRT::Utilities::Lazy<VkShaderModule>(
              std::function<VkShaderModule()>([this]() { return CreateShaderModule(); }))),
          _bytecode(std::vector<uint8_t>(bytecode.begin(), bytecode.end())),
          _shaderModuleCreateInfo(VkShaderModuleCreateInfo{})
    {
        size_t length = _bytecode.size();
        _shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        _shaderModuleCreateInfo.codeSize = length;
        _shaderModuleCreateInfo.pCode = reinterpret_cast<uint32_t*>(&(*_bytecode.begin()));
    }

    VkShaderModule VulkanShaderProgram::CreateShaderModule()
    {
        VkShaderModule returnShaderModule = VK_NULL_HANDLE;

        VkResult moduleCreationResult =
            vkCreateShaderModule(std::static_pointer_cast<VulkanGraphicsDevice>(GetDevice())->GetVulkanDevice(),
                                 &_shaderModuleCreateInfo, nullptr, &returnShaderModule);

        if (moduleCreationResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException(
                "Failed to initialise the provided SPIR-V data into a VkShaderModule.", moduleCreationResult);
        }

        return returnShaderModule;
    }

    VulkanShaderProgram::~VulkanShaderProgram()
    {
        vkDestroyShaderModule(std::static_pointer_cast<VulkanGraphicsDevice>(GetDevice())->GetVulkanDevice(),
                              _shaderModule.getActual(), nullptr);
    }

    std::shared_ptr<VulkanGraphicsDevice> VulkanShaderProgram::GetDevice() const noexcept
    {
        return _device;
    }

    const std::string& VulkanShaderProgram::GetEntryPointName() const noexcept
    {
        return _entryPointName;
    }

    ShaderProgramKind VulkanShaderProgram::GetKind() const noexcept
    {
        return _kind;
    }

    NovelRT::Utilities::Misc::Span<const uint8_t> VulkanShaderProgram::GetBytecode() const noexcept
    {
        return NovelRT::Utilities::Misc::Span<const uint8_t>(&(*_bytecode.begin()), _bytecode.size());
    }

    VkShaderModule VulkanShaderProgram::GetShaderModule()
    {
        return _shaderModule.getActual();
    }
}
