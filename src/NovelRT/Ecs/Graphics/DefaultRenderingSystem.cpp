// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>

namespace NovelRT::Ecs::Graphics
{
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

            auto texture2DRegion = resourceManager.LoadTextureData(
                texture, Experimental::Graphics::GraphicsTextureAddressMode::ClampToEdge,
                Experimental::Graphics::GraphicsTextureKind::TwoDimensional);

            *ptr = TextureInfo{texture2DRegion, ptr->textureName, ptr->ecsId};
            _namedTextureInfo.emplace_back(ptr);
        }
    }

    void DefaultRenderingSystem::ResolveExistingEntityAttachments(Catalogue& catalogue)
    {
        std::scoped_lock guard(_existingEntityRenderComponentAttachQueueMutex, _meshQueueVectorMutex,
                               _textureQueueVectorMutex, _ecsPrimitiveMapMutex, _graphicsPipelineVectorQueueMutex);

        ComponentView<RenderComponent> renderComponentView = catalogue.GetComponentView<RenderComponent>();

        while (!_existingEntityRenderComponentAttachQueue.empty())
        {
            Atom primitiveId = 0;
            AttachRenderToExistingEntityRequestInfo requestInfo = _existingEntityRenderComponentAttachQueue.front();
            _existingEntityRenderComponentAttachQueue.pop();

            if (requestInfo.primitivePtr == nullptr)
            {
                auto iteratorResult =
                    std::find_if(_ecsPrimitiveMap.begin(), _ecsPrimitiveMap.end(),
                                 [requestInfoCopy = requestInfo](const auto& pair)
                                 {
                                     auto& value = pair.second;
                                     return (value.ecsMeshDataId == requestInfoCopy.meshPtr->ecsId) &&
                                            (value.ecsTextureId == requestInfoCopy.texturePtr->ecsId) &&
                                            (value.ecsPipelineId == requestInfoCopy.pipelinePtr->ecsId);
                                 });

                if (iteratorResult == _ecsPrimitiveMap.end())
                {
                    auto& meshInfoPtr = _namedMeshInfo.at(_defaultSpriteMeshIndex);
                    auto dummyRegion =
                        Experimental::Graphics::GraphicsMemoryRegion<Experimental::Graphics::GraphicsResource>(
                            0, nullptr, _graphicsDevice, false, 0, 0);

                    std::vector<Experimental::Graphics::GraphicsMemoryRegion<Experimental::Graphics::GraphicsResource>>
                        inputResourceRegions{requestInfo.texturePtr->gpuTextureRegion};

                    auto newPrimitive = _graphicsDevice->CreatePrimitive(
                        _defaultGraphicsPipelinePtr.GetUnderlyingSharedPtr(), _defaultSpriteMeshPtr->gpuVertexRegion,
                        sizeof(TexturedVertexTest), dummyRegion, 0, inputResourceRegions);
                    primitiveId = Atom::GetNextEcsPrimitiveId();
                    _ecsPrimitiveMap.emplace(primitiveId, newPrimitive);
                }
            }
            else
            {
                primitiveId = requestInfo.primitivePtr->ecsId;
            }

            renderComponentView.AddComponent(requestInfo.entityId,
                                             RenderComponent{requestInfo.meshPtr->ecsId, requestInfo.texturePtr->ecsId,
                                                             requestInfo.pipelinePtr->ecsId, primitiveId});
        }
    }

    void DefaultRenderingSystem::ResolveCreatingNewEntities(Catalogue& catalogue)
    {

    }

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

        //_primitive = _graphicsDevice->CreatePrimitive(pipeline, vertexBufferRegion, sizeof(TexturedVertexTest),
        //                                            dummyRegion, 0, inputResourceRegions);
        graphicsContext->EndFrame();
        _graphicsDevice->Signal(graphicsContext->GetFence());
        _graphicsDevice->WaitForIdle();
    }

    void DefaultRenderingSystem::Update(Timing::Timestamp /*delta*/, Ecs::Catalogue catalogue)
    {
        auto context = _graphicsDevice->GetCurrentContext();
        context->BeginFrame();

        // TODO: This call is probably not supposed to be here but we have nowhere else for it to live right now. :)
        ResolveTextureFutureResults();
        ResolveExistingEntityAttachments(catalogue);
        ResolveCreatingNewEntities(catalogue);

        context->BeginDrawing(NovelRT::Graphics::RGBAColour(0, 0, 255, 255));
        // context->Draw(_primitive);
        context->EndDrawing();
        context->EndFrame();
        _graphicsDevice->PresentFrame();
        _graphicsDevice->WaitForIdle();
    }

    Experimental::Threading::FutureResult<TextureInfo> DefaultRenderingSystem::GetOrLoadTexture(
        const std::string& textureFileName)
    {
        std::scoped_lock guard(_textureQueueVectorMutex);

        auto resultIterator =
            std::find_if(_namedTextureInfo.begin(), _namedTextureInfo.end(),
                         [textureFileName](const auto& ptr) { return textureFileName == ptr->textureName; });

        if (resultIterator == _namedTextureInfo.end())
        {
            auto concurrentPtr = Experimental::Threading::MakeShared<TextureInfo>();
            concurrentPtr->textureName = textureFileName;
            concurrentPtr->ecsId = Atom::GetNextEcsTextureId();

            _texturesToInitialise.emplace(concurrentPtr);
            return Experimental::Threading::FutureResult<TextureInfo>(concurrentPtr);
        }

        return Experimental::Threading::FutureResult<TextureInfo>(*resultIterator);
    }

    Experimental::Threading::ConcurrentSharedPtr<TextureInfo> DefaultRenderingSystem::GetExistingTextureBasedOnId(
        Atom ecsId)
    {
        std::scoped_lock guard(_textureQueueVectorMutex);

        auto resultIterator = std::find_if(_namedTextureInfo.begin(), _namedTextureInfo.end(),
                                           [ecsId](const auto& ptr) { return ptr->ecsId == ecsId; });

        if (resultIterator == _namedTextureInfo.end())
        {
            throw Exceptions::KeyNotFoundException("The specified ECS texture ID does not exist.");
        }

        return *resultIterator;
    }

    void DefaultRenderingSystem::AttachSpriteRenderingToEntity(
        EntityId entity,
        Experimental::Threading::ConcurrentSharedPtr<TextureInfo> texture)
    {
        std::scoped_lock<tbb::mutex> guard(_existingEntityRenderComponentAttachQueueMutex);

        _existingEntityRenderComponentAttachQueue.emplace(entity, std::move(texture));
    }

    Experimental::Threading::FutureResult<EntityId> DefaultRenderingSystem::CreateSpriteEntity(
        Experimental::Threading::ConcurrentSharedPtr<TextureInfo> texture)
    {
        std::scoped_lock guard(_createEntityWithRenderComponentQueueMutex);

        auto ptr = Experimental::Threading::MakeShared<EntityId>();
        _createEntityWithRenderComponentQueue.emplace(ptr, std::move(texture));

        return Experimental::Threading::FutureResult(ptr);
    }
}
