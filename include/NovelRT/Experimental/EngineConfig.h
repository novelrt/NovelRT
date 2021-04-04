// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ENGINECONFIG_H
#define NOVELRT_ENGINECONFIG_H

#include "../LoggingService.h"
#include <string>
#include <vector>

namespace NovelRT::EngineConfig
{
    const std::string& EngineName() noexcept;
    std::string& ApplicationName() noexcept;
    std::vector<std::string>& RequiredVulkanExtensions() noexcept;
    std::vector<std::string>& OptionalVulkanExtensions() noexcept;
    std::vector<std::string>& RequiredVulkanLayers() noexcept;
    std::vector<std::string>& OptionalVulkanLayers() noexcept;
    LogLevel& MinimumInternalLoggingLevel() noexcept;
    bool& EnableDebugOutputFromEngineInternals() noexcept;
} // namespace NovelRT::EngineConfig

#endif // NOVELRT_ENGINECONFIG_H
