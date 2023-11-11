#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <memory>

namespace NovelRT::Graphics
{
    class GraphicsAdapter;
    class GraphicsProvider;
    class GraphicsSurfaceContext;

    class IGraphicsAdapterSelector
    {
    public:
        [[nodiscard]] virtual std::shared_ptr<GraphicsAdapter> GetDefaultRecommendedAdapter(
            const std::shared_ptr<GraphicsProvider>& provider,
            const std::shared_ptr<GraphicsSurfaceContext>& surfaceContext) const = 0;

        virtual ~IGraphicsAdapterSelector() = default;
    };
}
