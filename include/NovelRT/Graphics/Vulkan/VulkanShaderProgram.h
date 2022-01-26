// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_VULKAN_VULKANSHADERPROGRAM_H
#define NOVELRT_GRAPHICS_VULKAN_VULKANSHADERPROGRAM_H

#ifndef NOVELRT_GRAPHICS_VULKAN_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.h instead for the Graphics::Vulkan namespace subset.
#endif

namespace NovelRT::Graphics::Vulkan
{
    class VulkanShaderProgram : public ShaderProgram
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
                            gsl::span<uint8_t> bytecode) noexcept;

        [[nodiscard]] gsl::span<const uint8_t> GetBytecode() const noexcept final;
        [[nodiscard]] VkShaderModule GetShaderModule();

        ~VulkanShaderProgram() override;
    };
}

#endif // NOVELRT_GRAPHICS_VULKAN_VULKANSHADERPROGRAM_H
