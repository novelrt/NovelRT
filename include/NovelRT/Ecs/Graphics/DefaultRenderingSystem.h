// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_GRAPHICS_DEFAULTRENDERINGSYSTEM_H
#define NOVELRT_ECS_GRAPHICS_DEFAULTRENDERINGSYSTEM_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs::Graphics
{
    struct TexturedVertexTest
    {
        NovelRT::Maths::GeoVector3F Position;
        NovelRT::Maths::GeoVector2F UV;
    };

    class DefaultRenderingSystem : public IEcsSystem
    {
    private:
        Utilities::Lazy<Experimental::Graphics::GraphicsResourceManager> _resourceManager;
        std::shared_ptr<PluginManagement::IGraphicsPluginProvider> _graphicsPluginProvider;
        std::shared_ptr<PluginManagement::IWindowingPluginProvider> _windowingPluginProvider;
        std::shared_ptr<PluginManagement::IResourceManagementPluginProvider> _resourceManagementPluginProvider;
        std::shared_ptr<Experimental::Graphics::GraphicsSurfaceContext> _surfaceContext;
        std::shared_ptr<Experimental::Graphics::GraphicsAdapter> _graphicsAdapter;
        std::shared_ptr<Experimental::Graphics::GraphicsDevice> _graphicsDevice;
        std::shared_ptr<Experimental::Graphics::GraphicsBuffer> _textureStagingBuffer;
        std::shared_ptr<Experimental::Graphics::GraphicsTexture> _texture2D;
        std::shared_ptr<Experimental::Graphics::GraphicsPrimitive> _primitive;
        std::vector<Experimental::Graphics::GraphicsPipelineInputElement> _elements;
        std::vector<Experimental::Graphics::GraphicsPipelineInput> _inputs;
        std::vector<Experimental::Graphics::GraphicsPipelineResource> _resources;
        std::vector<Experimental::Graphics::GraphicsMemoryRegion<Experimental::Graphics::GraphicsResource>> _inputResourceRegions;
        SceneGraph::Scene _renderScene;

    public:
        DefaultRenderingSystem(std::shared_ptr<PluginManagement::IGraphicsPluginProvider> graphicsPluginProvider,
                               std::shared_ptr<PluginManagement::IWindowingPluginProvider> windowingPluginProvider,
                               std::shared_ptr<PluginManagement::IResourceManagementPluginProvider> resourceManagementPluginProvider);

        void Update(Timing::Timestamp delta, Ecs::Catalogue catalogue) final;
    };
}

#endif // !NOVELRT_ECS_GRAPHICS_DEFAULTRENDERINGSYSTEM_H
