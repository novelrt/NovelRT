// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_IGRAPHICSPLUGINPROVIDER_H
#define NOVELRT_GRAPHICS_IGRAPHICSPLUGINPROVIDER_H

#include <NovelRT/Utilities/Lazy.h>

namespace NovelRT::Graphics
{
    template<typename TBackend> struct GraphicsBackendTraits;
}

namespace NovelRT::PluginManagement
{
    template<typename TBackend>
    class IGraphicsPluginProvider : public std::enable_shared_from_this<IGraphicsPluginProvider<TBackend>>
    {
    public:
        using BackendGraphicsProvider = typename Graphics::GraphicsBackendTraits<TBackend>::ProviderType;

    private:
        Utilities::Lazy<std::shared_ptr<BackendGraphicsProvider>> _graphicsProvider;

    public:
        IGraphicsPluginProvider() noexcept;
        virtual ~IGraphicsPluginProvider() = default;

        [[nodiscard]] std::shared_ptr<Graphics::GraphicsProvider<TBackend>> GetGraphicsProvider();

        [[nodiscard]] std::shared_ptr<Graphics::GraphicsAdapter<TBackend>> GetDefaultSelectedGraphicsAdapterForContext(
            std::shared_ptr<Graphics::GraphicsSurfaceContext<TBackend>> context);

        [[nodiscard]] std::shared_ptr<Graphics::GraphicsSurfaceContext<TBackend>> CreateSurfaceContext(
            std::shared_ptr<Graphics::IGraphicsSurface> windowingDevice);
    };
}

#endif // NOVELRT_GRAPHICS_IGRAPHICSPLUGINPROVIDER_H
