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
        std::vector<Experimental::Graphics::GraphicsMemoryRegion<Experimental::Graphics::GraphicsResource>> _inputResourceRegions;

        tbb::mutex _textureQueueVectorMutex;
        std::vector<Experimental::Threading::ConcurrentSharedPtr<TextureInfo>> _namedTextureInfo;
        std::queue<Experimental::Threading::ConcurrentSharedPtr<TextureInfo>> _texturesToInitialise;

        tbb::mutex _meshQueueVectorMutex;
        std::vector<Experimental::Threading::ConcurrentSharedPtr<MeshInfo>> _namedMeshInfo;
        std::queue<Experimental::Threading::ConcurrentSharedPtr<MeshInfo>> _meshesToInitialise;

        Experimental::Threading::ConcurrentSharedPtr<MeshInfo> _defaultSpriteMeshPtr;
        size_t _defaultSpriteMeshIndex;

        tbb::mutex _ecsPrimitiveMapMutex;
        std::map<Atom, GraphicsPrimitiveInfo, AtomHashFunction> _ecsPrimitiveMap;

        tbb::mutex _existingEntityRenderComponentAttachQueueMutex;
        std::queue<AttachRenderToExistingEntityRequestInfo> _existingEntityRenderComponentAttachQueue;

        tbb::mutex _createEntityWithRenderComponentQueueMutex;
        std::queue<CreateRenderEntityRequestInfo> _createEntityWithRenderComponentQueue;

        tbb::mutex _graphicsPipelineVectorQueueMutex;
        std::vector<Experimental::Threading::ConcurrentSharedPtr<Experimental::Graphics::GraphicsPipeline>> _namedGraphicsPipelineInfo;
        std::queue<Experimental::Threading::ConcurrentSharedPtr<Experimental::Graphics::GraphicsPipeline>> _graphicsPipelinesToInitialise;

        Experimental::Threading::ConcurrentSharedPtr<Experimental::Graphics::GraphicsPipeline> _defaultGraphicsPipelinePtr;
        size_t _defaultGraphicsPtrIndex;

        SceneGraph::Scene _renderScene;


        void ResolveTextureFutureResults();
        void ResolveExistingEntityAttachments(Catalogue& catalogue);
        void ResolveCreatingNewEntities(Catalogue& catalogue);
    public:
        DefaultRenderingSystem(std::shared_ptr<PluginManagement::IGraphicsPluginProvider> graphicsPluginProvider,
                               std::shared_ptr<PluginManagement::IWindowingPluginProvider> windowingPluginProvider,
                               std::shared_ptr<PluginManagement::IResourceManagementPluginProvider> resourceManagementPluginProvider);

        void Update(Timing::Timestamp delta, Catalogue catalogue) final;

        [[nodiscard]] Experimental::Threading::FutureResult<TextureInfo> GetOrLoadTexture(const std::string& spriteFileName);
        [[nodiscard]] Experimental::Threading::ConcurrentSharedPtr<TextureInfo> GetExistingTextureBasedOnId(Atom ecsId);

        void AttachSpriteRenderingToEntity(EntityId entity, Experimental::Threading::ConcurrentSharedPtr<TextureInfo> texture);
        [[nodiscard]] Experimental::Threading::FutureResult<EntityId> CreateSpriteEntity( Experimental::Threading::ConcurrentSharedPtr<TextureInfo> texture);
    };
}

#endif // !NOVELRT_ECS_GRAPHICS_DEFAULTRENDERINGSYSTEM_H
