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
        Utilities::Lazy<NovelRT::Graphics::GraphicsResourceManager> _resourceManager;
        std::shared_ptr<PluginManagement::IGraphicsPluginProvider> _graphicsPluginProvider;
        std::shared_ptr<PluginManagement::IWindowingPluginProvider> _windowingPluginProvider;
        std::shared_ptr<PluginManagement::IResourceManagementPluginProvider> _resourceManagementPluginProvider;
        std::shared_ptr<NovelRT::Graphics::GraphicsSurfaceContext> _surfaceContext;
        std::shared_ptr<NovelRT::Graphics::GraphicsAdapter> _graphicsAdapter;
        std::shared_ptr<NovelRT::Graphics::GraphicsDevice> _graphicsDevice;
        std::shared_ptr<NovelRT::Windowing::IWindowingDevice> _windowingDevice;

        NovelRT::Graphics::GraphicsMemoryRegion<NovelRT::Graphics::GraphicsResource> _frameMatrixConstantBufferRegion;

        tbb::mutex _textureQueueMapMutex;
        std::map<Atom, Threading::ConcurrentSharedPtr<TextureInfo>> _namedTextureInfoObjects;
        std::queue<Threading::ConcurrentSharedPtr<TextureInfo>> _texturesToInitialise;

        tbb::mutex _vertexQueueMapMutex;
        std::map<Atom, Threading::ConcurrentSharedPtr<VertexInfo>> _namedVertexInfoObjects;
        std::queue<Threading::ConcurrentSharedPtr<VertexInfo>> _vertexDataToInitialise;

        Threading::ConcurrentSharedPtr<VertexInfo> _defaultSpriteMeshPtr;

        tbb::mutex _graphicsPipelineMapMutex;
        std::map<Atom, Threading::ConcurrentSharedPtr<GraphicsPipelineInfo>> _namedGraphicsPipelineInfoObjects;

        Threading::ConcurrentSharedPtr<GraphicsPipelineInfo> _defaultGraphicsPipelinePtr;

        std::map<Atom, GraphicsPrimitiveInfo> _primitiveConfigurations;

        SceneGraph::Scene _renderScene;

        void ResolveGpuFutures();
        void ResolveVertexInfoFutureResults();
        void ResolveTextureFutureResults();

    public:
        Utilities::Event<Timing::Timestamp,
                         Catalogue&,
                         int32_t,
                         EntityId,
                         RenderComponent,
                         TransformComponent,
                         NovelRT::Graphics::GraphicsResourceManager&,
                         std::shared_ptr<NovelRT::Graphics::GraphicsSurfaceContext>,
                         std::shared_ptr<NovelRT::Graphics::GraphicsAdapter>,
                         std::shared_ptr<NovelRT::Graphics::GraphicsDevice>,
                         std::shared_ptr<NovelRT::Windowing::IWindowingDevice>,
                         std::shared_ptr<NovelRT::Graphics::GraphicsContext>>
            CustomRenderForEntity;

        DefaultRenderingSystem(
            std::shared_ptr<PluginManagement::IGraphicsPluginProvider> graphicsPluginProvider,
            std::shared_ptr<PluginManagement::IWindowingPluginProvider> windowingPluginProvider,
            std::shared_ptr<PluginManagement::IResourceManagementPluginProvider> resourceManagementPluginProvider);

        void Update(Timing::Timestamp delta, Catalogue catalogue) final;

        [[nodiscard]] Threading::FutureResult<TextureInfo> GetOrLoadTexture(const std::string& spriteName);

        [[nodiscard]] Threading::ConcurrentSharedPtr<TextureInfo> GetExistingTextureBasedOnId(Atom ecsId);

        // TODO: I don't know if we want to have an untyped version of this. we could use the C++ new mechanism with a
        // type for complete safety but then C might have a harder time. Unsure.
        // TODO: in the future when we have mesh loading capabilities these will be replaced with similar mechanisms to
        // texture loading. End-users shouldn't need to manually hard-code the data.
        template<typename TSpanType>
        [[nodiscard]] Threading::FutureResult<VertexInfo> LoadVertexDataRaw(const std::string& vertexDataName,
                                                                            gsl::span<TSpanType> vertexDataSpan)
        {
            static_assert(std::is_trivially_copyable_v<TSpanType> &&
                          "The specified vertex struct must be trivially copyable.");

            return LoadVertexDataRawUntyped(vertexDataName, vertexDataSpan.data(), sizeof(TSpanType),
                                            vertexDataSpan.size());
        }

        [[nodiscard]] Threading::FutureResult<VertexInfo> LoadVertexDataRawUntyped(const std::string& vertexDataName,
                                                                                   void* data,
                                                                                   size_t dataTypeSize,
                                                                                   size_t dataLength);

        [[nodiscard]] Threading::ConcurrentSharedPtr<VertexInfo> GetExistingVertexDataBasedOnName(
            const std::string& vertexDataName);

        [[nodiscard]] Threading::ConcurrentSharedPtr<VertexInfo> GetExistingVertexDataBasedOnId(Atom ecsId);

        [[nodiscard]] Threading::ConcurrentSharedPtr<GraphicsPipelineInfo> GetExistingPipelineInfoBasedOnId(Atom ecsId);

        [[nodiscard]] Threading::ConcurrentSharedPtr<GraphicsPipelineInfo> RegisterPipeline(
            const std::string& pipelineName,
            std::shared_ptr<NovelRT::Graphics::GraphicsPipeline> pipeline,
            std::vector<NovelRT::Graphics::GraphicsMemoryRegion<NovelRT::Graphics::GraphicsResource>>
                customConstantBufferRegions = {},
            bool useEcsTransforms = true);

        void AttachSpriteRenderingToEntity(EntityId entity,
                                           Threading::ConcurrentSharedPtr<TextureInfo> texture,
                                           Catalogue& catalogue);

        [[nodiscard]] EntityId CreateSpriteEntity(Threading::ConcurrentSharedPtr<TextureInfo> texture,
                                                  Catalogue& catalogue);

        [[nodiscard]] EntityId CreateSpriteEntityOutsideOfSystem(Threading::ConcurrentSharedPtr<TextureInfo> texture,
                                                                 SystemScheduler& scheduler);

        void ForceVertexTextureFutureResolution();
    };
}
#endif // !NOVELRT_ECS_GRAPHICS_DEFAULTRENDERINGSYSTEM_H
