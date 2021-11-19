// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>

namespace NovelRT::Ecs::Graphics
{
    DefaultRenderingSystem::DefaultRenderingSystem(
        std::shared_ptr<PluginManagement::IGraphicsPluginProvider> graphicsPluginProvider,
        std::shared_ptr<PluginManagement::IWindowingPluginProvider> windowingPluginProvider,
        std::shared_ptr<PluginManagement::IResourceManagementPluginProvider> resourceManagementPluginProvider)
        : _resourceManager([&]() { return Experimental::Graphics::GraphicsResourceManager(_graphicsDevice); }),
          _graphicsPluginProvider(std::move(graphicsPluginProvider)),
          _windowingPluginProvider(std::move(windowingPluginProvider)),
          _resourceManagementPluginProvider(std::move(resourceManagementPluginProvider))
    {
        _windowingPluginProvider->GetWindowingDevice()->Initialise(Windowing::WindowMode::Windowed,
                                                                   Maths::GeoVector2F(400, 400));

        EngineConfig::EnableDebugOutputFromEngineInternals() = true;
        EngineConfig::MinimumInternalLoggingLevel() = LogLevel::Warn;

        _surfaceContext = _graphicsPluginProvider->CreateSurfaceContext(_windowingPluginProvider->GetWindowingDevice());
        _graphicsAdapter = _graphicsPluginProvider->GetDefaultSelectedGraphicsAdapterForContext(_surfaceContext);
        _graphicsDevice = _graphicsAdapter->CreateDevice(_surfaceContext, 2);

        auto resourceLoader = _resourceManagementPluginProvider->GetResourceLoader();
        auto vertShaderData = resourceLoader->LoadShaderSource("vert.spv");
        auto pixelShaderData = resourceLoader->LoadShaderSource("frag.spv");

        std::vector<Experimental::Graphics::GraphicsPipelineInputElement> elements = {
            Experimental::Graphics::GraphicsPipelineInputElement(
                typeid(NovelRT::Maths::GeoVector3F), Experimental::Graphics::GraphicsPipelineInputElementKind::Position,
                12),
            Experimental::Graphics::GraphicsPipelineInputElement(
                typeid(NovelRT::Maths::GeoVector2F),
                Experimental::Graphics::GraphicsPipelineInputElementKind::TextureCoordinate, 8)};

        std::vector<Experimental::Graphics::GraphicsPipelineInput> inputs = {
            Experimental::Graphics::GraphicsPipelineInput(elements)};

        std::vector<Experimental::Graphics::GraphicsPipelineResource> resources = {
            Experimental::Graphics::GraphicsPipelineResource(
                Experimental::Graphics::GraphicsPipelineResourceKind::Texture,
                Experimental::Graphics::ShaderProgramVisibility::Pixel)};

        auto vertexShaderProgram = _graphicsDevice->CreateShaderProgram(
            "main", Experimental::Graphics::ShaderProgramKind::Vertex, vertShaderData);
        auto pixelShaderProgram = _graphicsDevice->CreateShaderProgram(
            "main", Experimental::Graphics::ShaderProgramKind::Pixel, pixelShaderData);
        auto signature = _graphicsDevice->CreatePipelineSignature(
            Experimental::Graphics::GraphicsPipelineBlendFactor::SrcAlpha,
            Experimental::Graphics::GraphicsPipelineBlendFactor::OneMinusSrcAlpha, inputs, resources);
        auto pipeline = _graphicsDevice->CreatePipeline(signature, vertexShaderProgram, pixelShaderProgram);

        auto graphicsContext = _graphicsDevice->GetCurrentContext();

        graphicsContext->BeginFrame();
        auto pVertexBuffer = std::vector<TexturedVertexTest>{
            TexturedVertexTest{Maths::GeoVector3F(-1, 1, 0), Maths::GeoVector2F(0.0f, 0.0f)},
            TexturedVertexTest{Maths::GeoVector3F(1, 1, 0), Maths::GeoVector2F(1.0f, 0.0f)},
            TexturedVertexTest{Maths::GeoVector3F(1, -1, 0), Maths::GeoVector2F(1.0f, 1.0f)},
            TexturedVertexTest{Maths::GeoVector3F(1, -1, 0), Maths::GeoVector2F(1.0f, 1.0f)},
            TexturedVertexTest{Maths::GeoVector3F(-1, -1, 0), Maths::GeoVector2F(0.0f, 1.0f)},
            TexturedVertexTest{Maths::GeoVector3F(-1, 1, 0), Maths::GeoVector2F(0.0f, 0.0f)}};

        auto& resourceManager = _resourceManager.getActual();
        auto vertexBufferRegion = resourceManager.LoadVertexData(gsl::span<TexturedVertexTest>(pVertexBuffer));

        auto texture2DRegionFuture = GetOrLoadTexture("novel-chan.png");
        ResolveTextureFutureResults(); // TODO: Workaround for internal texture testing for now. Will be gone in final.

        auto texture2DRegion = texture2DRegionFuture.GetValue();

        std::vector<Experimental::Graphics::GraphicsMemoryRegion<Experimental::Graphics::GraphicsResource>>
            inputResourceRegions{texture2DRegion.gpuTextureRegion};

        auto dummyRegion = Experimental::Graphics::GraphicsMemoryRegion<Experimental::Graphics::GraphicsResource>(
            0, nullptr, _graphicsDevice, false, 0, 0);

        _primitive = _graphicsDevice->CreatePrimitive(pipeline, vertexBufferRegion, sizeof(TexturedVertexTest),
                                                      dummyRegion, 0, inputResourceRegions);
        graphicsContext->EndFrame();
        _graphicsDevice->Signal(graphicsContext->GetFence());
        _graphicsDevice->WaitForIdle();
    }

    void DefaultRenderingSystem::Update(Timing::Timestamp /*delta*/, Ecs::Catalogue /*catalogue*/)
    {
        auto context = _graphicsDevice->GetCurrentContext();
        context->BeginFrame();

        // TODO: This call is probably not supposed to be here but we have nowhere else for it to live right now. :)
        ResolveTextureFutureResults();

        context->BeginDrawing(NovelRT::Graphics::RGBAColour(0, 0, 255, 255));
        context->Draw(_primitive);
        context->EndDrawing();
        context->EndFrame();
        _graphicsDevice->PresentFrame();
        _graphicsDevice->WaitForIdle();
    }

    void DefaultRenderingSystem::ResolveTextureFutureResults()
    {
        std::scoped_lock<tbb::mutex> guard(_textureQueueVectorMutex);

        while (!_texturesToInitialise.empty())
        {
            Experimental::Threading::ConcurrentSharedPtr<TextureInfo> ptr = _texturesToInitialise.front();
            _texturesToInitialise.pop();

            auto resourceManager = _resourceManager.getActual();
            auto resourceLoader = _resourceManagementPluginProvider->GetResourceLoader();
            auto texture = resourceLoader->LoadTexture(ptr->textureName);

            auto texture2DRegion =
                resourceManager.LoadTextureData(texture, Experimental::Graphics::GraphicsTextureAddressMode::ClampToEdge,
                                                Experimental::Graphics::GraphicsTextureKind::TwoDimensional);

            *ptr = TextureInfo{texture2DRegion, ptr->textureName};
            _namedTextureInfo.emplace_back(ptr);
        }
    }

    Experimental::Threading::FutureResult<TextureInfo> DefaultRenderingSystem::GetOrLoadTexture(
        const std::string& textureFileName)
    {
        std::scoped_lock<tbb::mutex> guard(_textureQueueVectorMutex);

        auto resultIterator =
            std::find_if(_namedTextureInfo.begin(), _namedTextureInfo.end(),
                         [textureFileName](const auto& ptr) { return textureFileName == ptr->textureName; });

        if (resultIterator == _namedTextureInfo.end())
        {
            auto concurrentPtr = Experimental::Threading::MakeShared<TextureInfo>();
            concurrentPtr->textureName = textureFileName;

            _texturesToInitialise.emplace(concurrentPtr);
            return Experimental::Threading::FutureResult<TextureInfo>(concurrentPtr);
        }

        return Experimental::Threading::FutureResult<TextureInfo>(*resultIterator);
    }

    /*
    void DefaultRenderingSystem::AttachSpriteRenderingToEntity(EntityId entity, const TextureInfo& texture)
    {

    }

    EntityId DefaultRenderingSystem::CreateSpriteEntity(const TextureInfo& texture)
    {

    }
     */
}
