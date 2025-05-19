// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>
#include <NovelRT/Graphics/ShaderProgram.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBackendTraits.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanShaderProgram.hpp>
#include <NovelRT/Utilities/Span.hpp>

namespace NovelRT::Graphics::Vulkan
{
    VulkanShaderProgram::VulkanShaderProgram(VulkanGraphicsDevice* device,
                                             std::string entryPointName,
                                             ShaderProgramKind kind,
                                             NovelRT::Utilities::Span<uint8_t> bytecode) noexcept
        : _device(device)
        , _entryPointName(std::move(entryPointName))
        , _kind(kind)
        , _shaderModule([this]() { return CreateShaderModule(); })
        , _bytecode(std::vector<uint8_t>(bytecode.begin(), bytecode.end()))
        , _shaderModuleCreateInfo(VkShaderModuleCreateInfo{})
    {
        const size_t length = _bytecode.size();
        _shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        _shaderModuleCreateInfo.codeSize = length;
        _shaderModuleCreateInfo.pCode = reinterpret_cast<uint32_t*>(&(*_bytecode.begin()));
    }

    VkShaderModule VulkanShaderProgram::CreateShaderModule()
    {
        VkShaderModule returnShaderModule = VK_NULL_HANDLE;

        const VkResult moduleCreationResult = vkCreateShaderModule(GetDevice()->GetVulkanDevice(), &_shaderModuleCreateInfo, nullptr, &returnShaderModule);

        if (moduleCreationResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException(
                "Failed to initialise the provided SPIR-V data into a VkShaderModule.", moduleCreationResult);
        }

        return returnShaderModule;
    }

    VulkanShaderProgram::~VulkanShaderProgram()
    {
        vkDestroyShaderModule(GetDevice()->GetVulkanDevice(), _shaderModule.Get(), nullptr);
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

    NovelRT::Utilities::Span<const uint8_t> VulkanShaderProgram::GetBytecode() const noexcept
    {
        return _bytecode;
    }

    VkShaderModule VulkanShaderProgram::GetShaderModule()
    {
        return _shaderModule.Get();
    }
}

template class NovelRT::Graphics::ShaderProgram<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
