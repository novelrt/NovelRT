// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_IGRAPHICSPLUGINPROVIDER_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_IGRAPHICSPLUGINPROVIDER_H

#ifndef NOVELRT_PLUGINMANAGEMENT_H
#error NovelRT does not support including types explicitly by default. Please include PluginManagement.h instead for the PluginManagement namespace subset.
#endif

namespace NovelRT::PluginManagement
{
    class IGraphicsPluginProvider
    {
    private:
        [[nodiscard]] virtual Experimental::Graphics::GraphicsProvider* GetGraphicsProviderInternal() = 0;

    public:
        [[nodiscard]] inline std::shared_ptr<Experimental::Graphics::GraphicsProvider> GetGraphicsProvider()
        {
            return GetGraphicsProviderInternal()->shared_from_this();
        }

        [[nodiscard]] virtual std::shared_ptr<Experimental::Graphics::GraphicsAdapter>
        GetDefaultSelectedGraphicsAdapterForContext(
            std::shared_ptr<Experimental::Graphics::GraphicsSurfaceContext> context) = 0;

        [[nodiscard]] virtual std::shared_ptr<Experimental::Graphics::GraphicsSurfaceContext> CreateSurfaceContext(
            std::shared_ptr<Experimental::Graphics::IGraphicsSurface> windowingDevice) = 0;

        virtual ~IGraphicsPluginProvider() = default;
    };
}

#endif // NOVELRT_EXPERIMENTAL_GRAPHICS_IGRAPHICSPLUGINPROVIDER_H
