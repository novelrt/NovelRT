// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Graphics/Vulkan/Graphics.Vulkan.h>
#include <NovelRT/Experimental/Graphics/Vulkan/VulkanShaderProgram.h>

namespace NovelRT::Experimental::Graphics::Vulkan
{
    VulkanShaderProgram::VulkanShaderProgram(std::shared_ptr<VulkanGraphicsDevice> device,
                                             std::string entryPointName,
                                             ShaderProgramKind kind,
                                             gsl::span<uint8_t> bytecode) noexcept
        : ShaderProgram(device, std::move(entryPointName), kind),
          _shaderModule(NovelRT::Utilities::Lazy<VkShaderModule>(
              std::function<VkShaderModule()>([this]() { return CreateShaderModule(); }))),
          _bytecode(bytecode),
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

        VkResult moduleCreationResult = vkCreateShaderModule(std::static_pointer_cast<VulkanGraphicsDevice>(GetDevice())->GetVulkanDevice(),
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
        vkDestroyShaderModule(std::static_pointer_cast<VulkanGraphicsDevice>(GetDevice())->GetVulkanDevice(), _shaderModule.getActual(), nullptr);
    }

    gsl::span<uint8_t> VulkanShaderProgram::GetBytecode() const noexcept
    {
        return _bytecode;
    }
    VkShaderModule VulkanShaderProgram::GetShaderModule()
    {
        return _shaderModule.getActual();
    }
} // namespace NovelRT::Experimental::Graphics::Vulkan