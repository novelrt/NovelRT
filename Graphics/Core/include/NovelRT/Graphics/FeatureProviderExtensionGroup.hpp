#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <algorithm>
#include <optional>
#include <span>
#include <string>
#include <vector>

namespace NovelRT::Graphics
{
    struct FeatureProviderExtensionGroup
    {
        std::vector<std::string> extensionNames;

        [[nodiscard]] std::optional<std::string> FindFirstAvailableExtension(
            std::span<const std::string> extensionNamesTestCandidate) const noexcept
        {
            for (const std::string& ext : extensionNames)
            {
                auto iter = std::find(extensionNamesTestCandidate.begin(), extensionNamesTestCandidate.end(), ext);
                if (iter != extensionNamesTestCandidate.end())
                {
                    return *iter;
                }
            }

            return std::nullopt;
        }

        bool operator==(const FeatureProviderExtensionGroup& other) const noexcept
        {
            if (extensionNames.size() != other.extensionNames.size())
            {
                return false;
            }

            for (const auto& ext : extensionNames)
            {
                bool match = false;

                for (const auto& otherExt : other.extensionNames)
                {
                    if (ext == otherExt)
                    {
                        match = true;
                        break;
                    }
                }

                if (!match)
                {
                    return false;
                }
            }

            return true;
        }
    };
}
