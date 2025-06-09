// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>
#include <NovelRT/Graphics/ShaderProgram.hpp>

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanShaderProgram.hpp>
#include <NovelRT/Utilities/Span.hpp>

namespace NovelRT::Graphics
{
    using VulkanGraphicsDevice = GraphicsDevice<Vulkan::VulkanGraphicsBackend>;
    using VulkanShaderProgram = ShaderProgram<Vulkan::VulkanGraphicsBackend>;

    VkShaderModule CreateShaderModule(
        std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> device,
        NovelRT::Utilities::Span<const uint8_t> bytecode)
    {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = bytecode.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(bytecode.data());

        VkShaderModule shaderModule = VK_NULL_HANDLE;
        const VkResult moduleCreationResult = vkCreateShaderModule(device->GetVulkanDevice(), &createInfo, nullptr, &shaderModule);

        if (moduleCreationResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException(
                "Failed to initialise the provided SPIR-V data into a VkShaderModule.", moduleCreationResult);
        }

        return shaderModule;
    }

    VulkanShaderProgram::ShaderProgram(
        std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> device,
        std::string entryPointName,
        ShaderProgramKind kind,
        NovelRT::Utilities::Span<const uint8_t> bytecode) noexcept
        : _device(std::move(device))
        , _entryPointName(std::move(entryPointName))
        , _kind(kind)
        , _shaderModule([device = _device, &bytecode = _bytecode]() { return CreateShaderModule(device, bytecode); })
        , _bytecode(bytecode.begin(), bytecode.end())
    { }

    VulkanShaderProgram::~ShaderProgram() noexcept
    {
        vkDestroyShaderModule(_device->GetVulkanDevice(), _shaderModule.Get(), nullptr);
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
