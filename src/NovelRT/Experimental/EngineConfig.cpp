// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/EngineConfig.h>

namespace NovelRT
{
    const std::string& EngineConfig::EngineName() noexcept
    {
        static std::string engineName = "NovelRT";
        return engineName;
    }

    std::string& EngineConfig::ApplicationName() noexcept
    {
        static std::string applicationName;
        return applicationName;
    }

    std::vector<std::string>& EngineConfig::RequiredVulkanExtensions() noexcept
    {
        static std::vector<std::string> requiredVulkanExtensions{};
        return requiredVulkanExtensions;
    }

    std::vector<std::string>& EngineConfig::OptionalVulkanExtensions() noexcept
    {
        static std::vector<std::string> optionalVulkanExtensions{};
        return optionalVulkanExtensions;
    }

    std::vector<std::string>& EngineConfig::RequiredVulkanLayers() noexcept
    {
        static std::vector<std::string> requiredVulkanLayers{};
        return requiredVulkanLayers;
    }

    std::vector<std::string>& EngineConfig::OptionalVulkanLayers() noexcept
    {
        static std::vector<std::string> optionalVulkanLayers{};
        return optionalVulkanLayers;
    }

    LogLevel& EngineConfig::MinimumInternalLoggingLevel() noexcept
    {
        static LogLevel minimumInternalLoggingLevel = LogLevel::Off;
        return minimumInternalLoggingLevel;
    }

    bool& EngineConfig::EnableDebugOutputFromEngineInternals() noexcept
    {
        static bool enableDebugOutputFromEngineInternals = false;
        return enableDebugOutputFromEngineInternals;
    }
}