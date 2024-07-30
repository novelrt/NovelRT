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
        using BackendAdapterSelectorType = TBackend::AdapterSelectorType;

    private:
        std::shared_ptr<BackendAdapterSelectorType> _implementation;


    public:
        [[nodiscard]] virtual std::shared_ptr<GraphicsAdapter<TBackend>> GetDefaultRecommendedAdapter(
            std::shared_ptr<GraphicsProvider<TBackend>> provider,
            std::shared_ptr<GraphicsSurfaceContext<TBackend>> surfaceContext) const
        {
            return _implementation->GetDefaultRecommendedAdapter(provider, surfaceContext)
        }
    };
}
