#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsProvider.hpp>
#include <NovelRT/Logging/LoggingService.hpp>
#include <NovelRT/Threading/VolatileState.hpp>
#include <NovelRT/Utilities/Lazy.hpp>
#include <NovelRT/Utilities/Span.hpp>

#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;
}

namespace NovelRT::Graphics
{
    template<>
    class GraphicsProvider<Vulkan::VulkanGraphicsBackend>
        : public std::enable_shared_from_this<GraphicsProvider<Vulkan::VulkanGraphicsBackend>>
    {
    public:
        using iterator =
            typename std::vector<std::shared_ptr<GraphicsAdapter<Vulkan::VulkanGraphicsBackend>>>::iterator;
        using const_iterator =
            typename std::vector<std::shared_ptr<GraphicsAdapter<Vulkan::VulkanGraphicsBackend>>>::const_iterator;

    private:
        std::vector<std::string> _finalInstanceExtensions;
        std::vector<std::string> _finalInstanceLayers;

        VkInstance _vulkanInstance;
        VkDebugUtilsMessengerEXT _debugLogger;
        Logging::LoggingService _logger;
        bool _debugModeEnabled;

        mutable NovelRT::Utilities::Lazy<std::vector<std::shared_ptr<GraphicsAdapter<Vulkan::VulkanGraphicsBackend>>>>
            _adapters;

    public:
        GraphicsProvider(bool enableDebugMode,
                         std::vector<std::string> requiredInstanceExtensions,
                         std::vector<std::string> optionalInstanceExtensions,
                         std::vector<std::string> requiredInstanceLayers,
                         std::vector<std::string> optionalInstanceLayers);
        ~GraphicsProvider();

        [[nodiscard]] bool GetDebugModeEnabled() const noexcept;

        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        [[nodiscard]] iterator begin() noexcept;
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        [[nodiscard]] const_iterator begin() const noexcept;
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        [[nodiscard]] iterator end() noexcept;
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        [[nodiscard]] const_iterator end() const noexcept;

        [[nodiscard]] uint32_t GetApiVersion() const noexcept;

        [[nodiscard]] VkInstance GetVulkanInstance() const noexcept;

        [[nodiscard]] NovelRT::Utilities::Span<const std::string> GetValidationLayers() const noexcept;
    };
}
