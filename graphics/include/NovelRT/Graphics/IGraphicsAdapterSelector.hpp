#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <memory>

namespace NovelRT::Graphics
{
    template<typename TBackend> class GraphicsAdapter;
    template<typename TBackend> class GraphicsProvider;
    template<typename TBackend> class GraphicsSurfaceContext;

    template<typename TBackend> class IGraphicsAdapterSelector
    {
    public:
        [[nodiscard]] virtual std::shared_ptr<GraphicsAdapter<TBackend>> GetDefaultRecommendedAdapter(
            const std::shared_ptr<GraphicsProvider<TBackend>>& provider,
            const std::shared_ptr<GraphicsSurfaceContext<TBackend>>& surfaceContext) const = 0;

        virtual ~IGraphicsAdapterSelector() = default;
    };
}
