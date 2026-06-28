#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <algorithm>
#include <memory>
#include <optional>
#include <span>
#include <vector>

namespace NovelRT::Graphics
{
    struct FeatureProviderExtensionGroup
    {
        std::vector<std::string> extensionNames;

        [[nodiscard]] std::optional<std::string> FindFirstAvailableExtension(
            std::span<const std::string> extensionNames) const noexcept
        {
            for (const std::string& ext : extensionNames)
            {
                auto iter = std::find(extensionNames.begin(), extensionNames.end(), ext);
                if (iter != extensionNames.end())
                {
                    return *iter;
                }
            }

            return std::nullopt;
        }
    };

    template<typename TBackend>
    class GraphicsAdapter;
    template<typename TBackend>
    class GraphicsProvider;
    template<typename TBackend>
    class GraphicsSurfaceContext;

    template<typename TBackend>
    class IGraphicsAdapterSelector
    {
    public:
        [[nodiscard]] virtual std::shared_ptr<GraphicsAdapter<TBackend>> GetDefaultRecommendedAdapter(
            std::shared_ptr<GraphicsProvider<TBackend>> provider,
            std::shared_ptr<GraphicsSurfaceContext<TBackend>> surfaceContext);
    };
}
