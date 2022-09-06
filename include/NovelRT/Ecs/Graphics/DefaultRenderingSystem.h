// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_GRAPHICS_DEFAULTRENDERINGSYSTEM_H
#define NOVELRT_ECS_GRAPHICS_DEFAULTRENDERINGSYSTEM_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs::Graphics
{
    struct TexturedVertex
    {
        NovelRT::Maths::GeoVector3F Position;
        NovelRT::Maths::GeoVector2F UV;
    };

    class DefaultRenderingSystem : public IEcsSystem
    {
    private:
        inline static AtomFactory& _textureIdFactory = AtomFactoryDatabase::GetFactory("TextureId");
        inline static AtomFactory& _ecsPrimitiveInfoConfigurationIdFactory =
            AtomFactoryDatabase::GetFactory("EcsPrimitiveInfoConfigurationId");

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
        std::queue<Atom> _texturesToDelete;

        tbb::mutex _vertexQueueMapMutex;
        std::map<Atom, Threading::ConcurrentSharedPtr<VertexInfo>> _namedVertexInfoObjects;
        std::queue<Threading::ConcurrentSharedPtr<VertexInfo>> _vertexDataToInitialise;
        std::queue<Atom> _vertexDataToDelete;

        Threading::ConcurrentSharedPtr<VertexInfo> _defaultSpriteMeshPtr;

        tbb::mutex _graphicsPipelineMapMutex;
        std::map<Atom, Threading::ConcurrentSharedPtr<GraphicsPipelineInfo>> _namedGraphicsPipelineInfoObjects;

        Threading::ConcurrentSharedPtr<GraphicsPipelineInfo> _defaultGraphicsPipelinePtr;

        std::map<Atom, GraphicsPrimitiveInfo> _primitiveConfigurations;

        SceneGraph::Scene _renderScene;

        NovelRT::Graphics::RGBAColour _backgroundColour;

        void ResolveGpuResourceCleanup();
        void ResolveVertexInfoGpuCleanup();
        void ResolveTextureInfoGpuCleanup();

        void ResolveGpuFutures();
        void ResolveVertexInfoFutureResults();
        void ResolveTextureFutureResults();

    public:
        struct UIRenderEventArgs
        {
            Timing::Timestamp delta;
            Catalogue& catalogue;
            std::shared_ptr<NovelRT::Graphics::GraphicsSurfaceContext> graphicsSurfaceContext;
            std::shared_ptr<NovelRT::Graphics::GraphicsAdapter> graphicsAdapter;
            std::shared_ptr<NovelRT::Graphics::GraphicsDevice> graphicsDevice;
            std::shared_ptr<NovelRT::Graphics::GraphicsContext> graphicsContext;
            NovelRT::Graphics::GraphicsResourceManager& resourceManager;
            NovelRT::Graphics::GraphicsMemoryRegion<NovelRT::Graphics::GraphicsResource>
                frameMatrixConstantBufferRegion;
        };

        Utilities::Event<std::reference_wrapper<DefaultRenderingSystem>, UIRenderEventArgs> UIRenderEvent;

        DefaultRenderingSystem(
            std::shared_ptr<PluginManagement::IGraphicsPluginProvider> graphicsPluginProvider,
            std::shared_ptr<PluginManagement::IWindowingPluginProvider> windowingPluginProvider,
            std::shared_ptr<PluginManagement::IResourceManagementPluginProvider> resourceManagementPluginProvider);

        void Update(Timing::Timestamp delta, Catalogue catalogue) final;

        [[nodiscard]] Threading::FutureResult<TextureInfo> GetOrLoadTexture(const std::string& spriteName);

        template<typename TSpanType>
        [[nodiscard]] Threading::FutureResult<TextureInfo> LoadTextureDataRaw(const std::string& textureDataName,
                                                                              gsl::span<TSpanType> textureDataSpan,
                                                                              uint32_t width,
                                                                              uint32_t height)
        {
            static_assert(std::is_trivially_copyable_v<TSpanType> &&
                          "The specified vertex struct must be trivially copyable.");

            return LoadTextureDataRawUntyped(textureDataName, textureDataSpan.data(), sizeof(TSpanType),
                                             textureDataSpan.size(), width, height);
        }

        [[nodiscard]] Threading::FutureResult<TextureInfo> LoadTextureDataRawUntyped(const std::string& textureDataName,
                                                                                     void* data,
                                                                                     size_t dataTypeSize,
                                                                                     size_t dataLength,
                                                                                     uint32_t width,
                                                                                     uint32_t height);

        [[nodiscard]] Threading::ConcurrentSharedPtr<TextureInfo> GetExistingTexture(Atom ecsId);

        [[nodiscard]] Threading::ConcurrentSharedPtr<TextureInfo> GetExistingTexture(const std::string& name);

        void DeleteTexture(Threading::ConcurrentSharedPtr<TextureInfo> texture);

        void DeleteTexture(Atom ecsId);

        void DeleteTexture(const std::string& name);

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

        [[nodiscard]] Threading::ConcurrentSharedPtr<VertexInfo> GetExistingVertexData(
            const std::string& vertexDataName);

        [[nodiscard]] Threading::ConcurrentSharedPtr<VertexInfo> GetExistingVertexData(Atom ecsId);

        void DeleteVertexData(Threading::ConcurrentSharedPtr<VertexInfo> vertexData);

        void DeleteVertexData(Atom ecsId);

        void DeleteVertexData(const std::string& name);

        [[nodiscard]] Threading::ConcurrentSharedPtr<GraphicsPipelineInfo> GetExistingPipelineInfo(
            const std::string& name);

        [[nodiscard]] Threading::ConcurrentSharedPtr<GraphicsPipelineInfo> GetExistingPipelineInfo(Atom ecsId);

        [[nodiscard]] Threading::ConcurrentSharedPtr<GraphicsPipelineInfo> RegisterPipeline(
            const std::string& pipelineName,
            std::shared_ptr<NovelRT::Graphics::GraphicsPipeline> pipeline,
            std::vector<NovelRT::Graphics::GraphicsMemoryRegion<NovelRT::Graphics::GraphicsResource>>
                customConstantBufferRegions = {},
            bool useEcsTransforms = true);

        void UnregisterPipeline(Threading::ConcurrentSharedPtr<GraphicsPipelineInfo> pipelineInfo);

        void UnregisterPipeline(Atom ecsId);

        void UnregisterPipeline(const std::string& name);

        void AttachSpriteRenderingToEntity(EntityId entity,
                                           Threading::ConcurrentSharedPtr<TextureInfo> texture,
                                           Catalogue& catalogue);

        [[nodiscard]] EntityId CreateSpriteEntity(Threading::ConcurrentSharedPtr<TextureInfo> texture,
                                                  Catalogue& catalogue);

        [[nodiscard]] EntityId CreateSpriteEntityOutsideOfSystem(Threading::ConcurrentSharedPtr<TextureInfo> texture,
                                                                 SystemScheduler& scheduler);

        void ForceVertexTextureFutureResolution();

        [[nodiscard]] inline NovelRT::Graphics::RGBAColour& BackgroundColour() noexcept
        {
            return _backgroundColour;
        }

        [[nodiscard]] inline const NovelRT::Graphics::RGBAColour& BackgroundColour() const noexcept
        {
            return _backgroundColour;
        }

        [[nodiscard]] uuids::uuid GetVertexShaderGuidForPrimitiveInfo(Atom primitiveInfoId) const noexcept;

        [[nodiscard]] uuids::uuid GetPixelShaderGuidForPrimitiveInfo(Atom primitiveInfoId) const noexcept;

        [[nodiscard]] uuids::uuid GetGuidForTexture(Atom textureId) const noexcept;
    };
}
#endif // !NOVELRT_ECS_GRAPHICS_DEFAULTRENDERINGSYSTEM_H
