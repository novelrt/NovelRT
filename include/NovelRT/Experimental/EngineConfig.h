// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ENGINECONFIG_H
#define NOVELRT_ENGINECONFIG_H

#include <string>
#include <vector>

namespace NovelRT
{
    class EngineConfig
    {
    public:
        static inline const std::string EngineName = "NovelRT";
        static inline std::string ApplicationName;
        static inline std::vector<std::string> RequiredVulkanExtensions{};
        static inline std::vector<std::string> OptionalVulkanExtensions{};
        static inline std::vector<std::string> RequiredVulkanLayers{};
        static inline std::vector<std::string> OptionalVulkanLayers{};
    };
} // namespace NovelRT

#endif // NOVELRT_ENGINECONFIG_H
