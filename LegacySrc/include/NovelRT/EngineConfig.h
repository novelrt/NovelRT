// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ENGINECONFIG_H
#define NOVELRT_ENGINECONFIG_H

#include "LoggingService.h"
#include <string>
#include <vector>

namespace NovelRT::EngineConfig
{
    const std::string& EngineName() noexcept;
    std::string& ApplicationName() noexcept;
    std::vector<std::string>& RequiredVulkanInstanceExtensions() noexcept;
    std::vector<std::string>& OptionalVulkanInstanceExtensions() noexcept;
    std::vector<std::string>& RequiredVulkanPhysicalDeviceExtensions() noexcept;
    std::vector<std::string>& OptionalVulkanPhysicalDeviceExtensions() noexcept;
    std::vector<std::string>& RequiredVulkanLayers() noexcept;
    std::vector<std::string>& OptionalVulkanLayers() noexcept;
    LogLevel& MinimumInternalLoggingLevel() noexcept;
    bool& EnableDebugOutputFromEngineInternals() noexcept;
}

#endif // NOVELRT_ENGINECONFIG_H
