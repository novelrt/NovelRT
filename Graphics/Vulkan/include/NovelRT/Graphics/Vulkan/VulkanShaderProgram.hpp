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
    struct VulkanGraphicsBackend;
}

namespace NovelRT::Graphics
{
    template <>
    class ShaderProgram<Vulkan::VulkanGraphicsBackend> final
        : public GraphicsDeviceObject<Vulkan::VulkanGraphicsBackend>
    {
    private:
        std::weak_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> _device;
        std::string _entryPointName;
        ShaderProgramKind _kind;
        NovelRT::Utilities::Lazy<VkShaderModule> _shaderModule;
        std::vector<uint8_t> _bytecode;

    public:
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<ShaderProgram<Vulkan::VulkanGraphicsBackend>> shared_from_this();
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<const ShaderProgram<Vulkan::VulkanGraphicsBackend>> shared_from_this() const;

        ShaderProgram(
            std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> device,
            std::string entryPointName,
            ShaderProgramKind kind,
            NovelRT::Utilities::Span<uint8_t> bytecode) noexcept;
        ~ShaderProgram() noexcept final;

        [[nodiscard]] const std::string& GetEntryPointName() const noexcept;
        [[nodiscard]] ShaderProgramKind GetKind() const noexcept;
        [[nodiscard]] NovelRT::Utilities::Span<const uint8_t> GetBytecode() const noexcept;
        [[nodiscard]] VkShaderModule GetShaderModule();

    };
}
