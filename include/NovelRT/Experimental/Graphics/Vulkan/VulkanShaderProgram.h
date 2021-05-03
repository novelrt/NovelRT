// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_VULKANSHADERPROGRAM_H
#define NOVELRT_VULKANSHADERPROGRAM_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.h instead for the Graphics::Vulkan namespace subset.
#endif

namespace NovelRT::Experimental::Graphics::Vulkan
{
    class VulkanShaderProgram : public ShaderProgram
    {
    private:
        Utilities::Lazy<VkShaderModule> _shaderModule;
        gsl::span<uint8_t> _bytecode;
        VkShaderModuleCreateInfo _shaderModuleCreateInfo;

        VulkanGraphicsDevice* GetGraphicsDeviceAsVulkanDevice() const noexcept;
        VkShaderModule CreateShaderModule();

    public:
        VulkanShaderProgram(VulkanGraphicsDevice& device,
                            std::string entryPointName,
                            ShaderProgramKind kind,
                            gsl::span<uint8_t> bytecode) noexcept;

        gsl::span<uint8_t> GetBytecode() const noexcept final;

        ~VulkanShaderProgram() override;
    };
} // namespace NovelRT::Experimental::Graphics::Vulkan

#endif // NOVELRT_VULKANSHADERPROGRAM_H
