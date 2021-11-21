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
        std::vector<Experimental::Graphics::GraphicsMemoryRegion<Experimental::Graphics::GraphicsResource>>
            _inputResourceRegions;

        tbb::mutex _textureQueueVectorMutex;
        std::vector<Experimental::Threading::ConcurrentSharedPtr<TextureInfo>> _namedTextureInfo;
        std::queue<Experimental::Threading::ConcurrentSharedPtr<TextureInfo>> _texturesToInitialise;

        tbb::mutex _vertexQueueVectorMutex;
        std::vector<Experimental::Threading::ConcurrentSharedPtr<VertexInfo>> _namedVertexInfo;
        std::queue<Experimental::Threading::ConcurrentSharedPtr<VertexInfo>> _vertexDataToInitialise;

        Experimental::Threading::ConcurrentSharedPtr<VertexInfo> _defaultSpriteMeshPtr;

        tbb::mutex _existingEntityRenderComponentAttachQueueMutex;
        std::queue<AttachRenderToExistingEntityRequestInfo> _existingEntityRenderComponentAttachQueue;

        tbb::mutex _createEntityWithRenderComponentQueueMutex;
        std::queue<CreateRenderEntityRequestInfo> _createEntityWithRenderComponentQueue;

        tbb::mutex _graphicsPipelineVectorMutex;
        std::vector<Experimental::Threading::ConcurrentSharedPtr<Experimental::Graphics::GraphicsPipeline>>
            _namedGraphicsPipelineInfo;

        Experimental::Threading::ConcurrentSharedPtr<GraphicsPipelineInfo>
            _defaultGraphicsPipelinePtr;

        SceneGraph::Scene _renderScene;

        void ResolveVertexInfoFutureResults();
        void ResolveTextureFutureResults();
        void ResolveExistingEntityAttachments(Catalogue& catalogue);
        void ResolveCreatingNewEntities(Catalogue& catalogue);

    public:
        DefaultRenderingSystem(
            std::shared_ptr<PluginManagement::IGraphicsPluginProvider> graphicsPluginProvider,
            std::shared_ptr<PluginManagement::IWindowingPluginProvider> windowingPluginProvider,
            std::shared_ptr<PluginManagement::IResourceManagementPluginProvider> resourceManagementPluginProvider);

        void Update(Timing::Timestamp delta, Catalogue catalogue) final;

        [[nodiscard]] Experimental::Threading::FutureResult<TextureInfo> GetOrLoadTexture(
            const std::string& spriteName);

        [[nodiscard]] Experimental::Threading::ConcurrentSharedPtr<TextureInfo> GetExistingTextureBasedOnId(Atom ecsId);

        // TODO: I don't know if we want to have an untyped version of this. we could use the C++ new mechanism with a
        // type for complete safety but then C might have a harder time. Unsure.
        // TODO: in the future when we have mesh loading capabilities these will be replaced with similar mechanisms to
        // texture loading. End-users shouldn't need to manually hard-code the data.
        template<typename TSpanType>
        [[nodiscard]] Experimental::Threading::FutureResult<VertexInfo> LoadVertexDataRaw(
            const std::string& vertexDataName,
            gsl::span<TSpanType> vertexDataSpan,
            std::vector<Experimental::Graphics::GraphicsPipelineInputElement> vertexShaderInputElements)
        {
            static_assert(std::is_trivially_copyable_v<TSpanType> &&
                          "The specified vertex struct must be trivially copyable.");

            return LoadVertexDataRawUntyped(vertexDataName, vertexDataSpan.data(), sizeof(TSpanType),
                                            vertexDataSpan.size(), std::move(vertexShaderInputElements));
        }

        [[nodiscard]] Experimental::Threading::FutureResult<VertexInfo> LoadVertexDataRawUntyped(
            const std::string& vertexDataName,
            void* data,
            size_t dataTypeSize,
            size_t dataLength,
            std::vector<Experimental::Graphics::GraphicsPipelineInputElement> vertexShaderInputElements);

        [[nodiscard]] Experimental::Threading::ConcurrentSharedPtr<VertexInfo> GetExistingVertexDataBasedOnName(
            const std::string& vertexDataName);

        [[nodiscard]] Experimental::Threading::ConcurrentSharedPtr<VertexInfo> GetExistingVertexDataBasedOnId(
            Atom ecsId);

        void AttachSpriteRenderingToEntity(EntityId entity,
                                           Experimental::Threading::ConcurrentSharedPtr<TextureInfo> texture);

        [[nodiscard]] Experimental::Threading::ConcurrentSharedPtr<GraphicsPipelineInfo> RegisterPipeline(const std::string& pipelineName, std::shared_ptr<Experimental::Graphics::GraphicsPipeline> pipeline);

        [[nodiscard]] Experimental::Threading::FutureResult<EntityId> CreateSpriteEntity(
            Experimental::Threading::ConcurrentSharedPtr<TextureInfo> texture);
    };
}
#endif // !NOVELRT_ECS_GRAPHICS_DEFAULTRENDERINGSYSTEM_H
