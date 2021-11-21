// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>
#include <NovelRT/Ecs/Graphics/DefaultRenderingSystem.h>

namespace NovelRT::Ecs::Graphics
{
    void DefaultRenderingSystem::ResolveVertexInfoFutureResults()
    {
        std::scoped_lock<tbb::mutex> guard(_vertexQueueVectorMutex);

        while (!_vertexDataToInitialise.empty())
        {
            Experimental::Threading::ConcurrentSharedPtr<VertexInfo> ptr = _vertexDataToInitialise.front();
            _texturesToInitialise.pop();

            auto& resourceManager = _resourceManager.getActual();

            ptr->gpuVertexRegion =
                resourceManager.LoadVertexDataUntyped(ptr->stagingPtr, ptr->sizeOfVert, ptr->stagingPtrLength);
            ptr->ecsId = Atom::GetNextEcsVertexDataId();
            free(ptr->stagingPtr);
            ptr->stagingPtr = nullptr;
        }
    }

    void DefaultRenderingSystem::ResolveTextureFutureResults()
    {
        std::scoped_lock<tbb::mutex> guard(_textureQueueVectorMutex);

        while (!_texturesToInitialise.empty())
        {
            Experimental::Threading::ConcurrentSharedPtr<TextureInfo> ptr = _texturesToInitialise.front();
            _texturesToInitialise.pop();

            auto& resourceManager = _resourceManager.getActual();
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
        std::scoped_lock guard(_existingEntityRenderComponentAttachQueueMutex);

        ComponentView<RenderComponent> renderComponentView = catalogue.GetComponentView<RenderComponent>();

        while (!_existingEntityRenderComponentAttachQueue.empty())
        {
            AttachRenderToExistingEntityRequestInfo requestInfo = _existingEntityRenderComponentAttachQueue.front();
            _existingEntityRenderComponentAttachQueue.pop();

            renderComponentView.AddComponent(requestInfo.entityId,
                                             RenderComponent{requestInfo.meshPtr->ecsId, requestInfo.texturePtr->ecsId,
                                                             requestInfo.pipelinePtr->ecsId});
        }
    }

    void DefaultRenderingSystem::ResolveCreatingNewEntities(Catalogue& catalogue)
    {
        std::scoped_lock guard(_createEntityWithRenderComponentQueueMutex);

        ComponentView<RenderComponent> renderComponentView = catalogue.GetComponentView<RenderComponent>();

        while (!_createEntityWithRenderComponentQueue.empty())
        {
            CreateRenderEntityRequestInfo requestInfo = _createEntityWithRenderComponentQueue.front();
            _createEntityWithRenderComponentQueue.pop();

            EntityId newEntity = catalogue.CreateEntity();
            *requestInfo.entityId = newEntity;

            renderComponentView.AddComponent(newEntity,
                                             RenderComponent{requestInfo.meshPtr->ecsId, requestInfo.texturePtr->ecsId,
                                                             requestInfo.pipelinePtr->ecsId});
        }
    }

    DefaultRenderingSystem::DefaultRenderingSystem(
        std::shared_ptr<PluginManagement::IGraphicsPluginProvider> graphicsPluginProvider,
        std::shared_ptr<PluginManagement::IWindowingPluginProvider> windowingPluginProvider,
        std::shared_ptr<PluginManagement::IResourceManagementPluginProvider> resourceManagementPluginProvider)
        : _resourceManager([&]() { return Experimental::Graphics::GraphicsResourceManager(_graphicsDevice); }),
          _graphicsPluginProvider(std::move(graphicsPluginProvider)),
          _windowingPluginProvider(std::move(windowingPluginProvider)),
          _resourceManagementPluginProvider(std::move(resourceManagementPluginProvider)),
          _surfaceContext(nullptr),
          _graphicsAdapter(nullptr),
          _graphicsDevice(nullptr),
          _inputResourceRegions{},
          _textureQueueVectorMutex(),
          _namedTextureInfo{},
          _texturesToInitialise{},
          _vertexQueueVectorMutex(),
          _namedVertexInfo{},
          _vertexDataToInitialise{},
          _defaultSpriteMeshPtr(nullptr),
          _existingEntityRenderComponentAttachQueueMutex(),
          _existingEntityRenderComponentAttachQueue{},
          _createEntityWithRenderComponentQueueMutex(),
          _createEntityWithRenderComponentQueue{},
          _namedGraphicsPipelineInfo{},
          _defaultGraphicsPipelinePtr(nullptr),
          _renderScene()
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

        _defaultGraphicsPipelinePtr = RegisterPipeline("default", pipeline);

        auto graphicsContext = _graphicsDevice->GetCurrentContext();

        graphicsContext->BeginFrame();
        auto pVertexBuffer = std::vector<TexturedVertexTest>{
            TexturedVertexTest{Maths::GeoVector3F(-1, 1, 0), Maths::GeoVector2F(0.0f, 0.0f)},
            TexturedVertexTest{Maths::GeoVector3F(1, 1, 0), Maths::GeoVector2F(1.0f, 0.0f)},
            TexturedVertexTest{Maths::GeoVector3F(1, -1, 0), Maths::GeoVector2F(1.0f, 1.0f)},
            TexturedVertexTest{Maths::GeoVector3F(1, -1, 0), Maths::GeoVector2F(1.0f, 1.0f)},
            TexturedVertexTest{Maths::GeoVector3F(-1, -1, 0), Maths::GeoVector2F(0.0f, 1.0f)},
            TexturedVertexTest{Maths::GeoVector3F(-1, 1, 0), Maths::GeoVector2F(0.0f, 0.0f)}};

        //auto texture2DRegionFuture = GetOrLoadTexture("novel-chan.png");
        auto spriteMeshFuture = LoadVertexDataRaw<TexturedVertexTest>("default", pVertexBuffer, elements);

        ResolveVertexInfoFutureResults();
        ResolveTextureFutureResults();

        _defaultSpriteMeshPtr = spriteMeshFuture.GetBackingConcurrentSharedPtr();

        /*
        std::vector<Experimental::Graphics::GraphicsMemoryRegion<Experimental::Graphics::GraphicsResource>>
            inputResourceRegions{texture2DRegion.gpuTextureRegion};
        */

        graphicsContext->EndFrame();
        _graphicsDevice->Signal(graphicsContext->GetFence());
        _graphicsDevice->WaitForIdle();
    }

    void DefaultRenderingSystem::Update(Timing::Timestamp /*delta*/, Ecs::Catalogue catalogue)
    {
        auto context = _graphicsDevice->GetCurrentContext();
        context->BeginFrame();

        // TODO: This call is probably not supposed to be here but we have nowhere else for it to live right now. :)
        ResolveVertexInfoFutureResults();
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
        const std::string& textureName)
    {
        std::scoped_lock guard(_textureQueueVectorMutex);

        auto resultIterator = std::find_if(_namedTextureInfo.begin(), _namedTextureInfo.end(),
                                           [textureName](const auto& ptr) { return textureName == ptr->textureName; });

        if (resultIterator == _namedTextureInfo.end())
        {
            auto concurrentPtr = Experimental::Threading::MakeConcurrentShared<TextureInfo>();
            concurrentPtr->textureName = textureName;
            concurrentPtr->ecsId = Atom::GetNextEcsTextureId();

            _texturesToInitialise.emplace(concurrentPtr);
            return Experimental::Threading::FutureResult<TextureInfo>(concurrentPtr, TextureInfo{});
        }

        return Experimental::Threading::FutureResult<TextureInfo>(*resultIterator, TextureInfo{});
    }

    Experimental::Threading::ConcurrentSharedPtr<TextureInfo> DefaultRenderingSystem::GetExistingTextureBasedOnId(
        Atom ecsId)
    {
        std::scoped_lock guard(_textureQueueVectorMutex);

        for (auto&& ptr : _namedTextureInfo)
        {
            if (ptr->ecsId != ecsId)
            {
                continue;
            }

            return ptr;
        }

        throw Exceptions::KeyNotFoundException();
    }

    void DefaultRenderingSystem::AttachSpriteRenderingToEntity(
        EntityId entity,
        Experimental::Threading::ConcurrentSharedPtr<TextureInfo> texture)
    {
        std::scoped_lock<tbb::mutex> guard(_existingEntityRenderComponentAttachQueueMutex);

        _existingEntityRenderComponentAttachQueue.emplace(entity, std::move(texture));
    }

    Experimental::Threading::FutureResult<VertexInfo> DefaultRenderingSystem::LoadVertexDataRawUntyped(
        const std::string& vertexDataName,
        void* data,
        size_t dataTypeSize,
        size_t dataLength,
        std::vector<Experimental::Graphics::GraphicsPipelineInputElement> vertexShaderInputElements)
    {
        std::scoped_lock guard(_vertexQueueVectorMutex);

        auto ptr = Experimental::Threading::MakeConcurrentShared<VertexInfo>();
        size_t size = dataTypeSize * dataLength;
        ptr->stagingPtr = malloc(size);
        ptr->sizeOfVert = dataTypeSize;
        ptr->stagingPtrLength = dataLength;
        ptr->vertexShaderInputElements = std::move(vertexShaderInputElements);
        memcpy_s(ptr->stagingPtr, size, data, size);
        _vertexDataToInitialise.emplace(ptr);

        return Experimental::Threading::FutureResult<VertexInfo>(ptr, VertexInfo{});
    }

    Experimental::Threading::ConcurrentSharedPtr<VertexInfo> DefaultRenderingSystem::GetExistingVertexDataBasedOnName(
        const std::string& vertexDataName)
    {
        std::scoped_lock guard(_vertexQueueVectorMutex);

        for (auto&& ptr : _namedVertexInfo)
        {
            if (ptr->vertexInfoName != vertexDataName)
            {
                continue;
            }

            return ptr;
        }

        throw Exceptions::KeyNotFoundException();
    }

    Experimental::Threading::ConcurrentSharedPtr<VertexInfo> DefaultRenderingSystem::GetExistingVertexDataBasedOnId(
        Atom ecsId)
    {
        std::scoped_lock guard(_vertexQueueVectorMutex);

        for (auto&& ptr : _namedVertexInfo)
        {
            if (ptr->ecsId != ecsId)
            {
                continue;
            }

            return ptr;
        }

        throw Exceptions::KeyNotFoundException();
    }

    Experimental::Threading::ConcurrentSharedPtr<GraphicsPipelineInfo> DefaultRenderingSystem::RegisterPipeline(
        const std::string& pipelineName,
        std::shared_ptr<Experimental::Graphics::GraphicsPipeline> pipeline)
    {
        std::scoped_lock guard(_graphicsPipelineVectorMutex);

        auto ptr = Experimental::Threading::MakeConcurrentShared<GraphicsPipelineInfo>();
        ptr->gpuPipeline =
            Experimental::Threading::ConcurrentSharedPtr<Experimental::Graphics::GraphicsPipeline>(pipeline);
        ptr->pipelineName = pipelineName;
        ptr->ecsId = Atom::GetNextEcsGraphicsPipelineId();

        _namedGraphicsPipelineInfo.emplace_back(ptr);

        return ptr;
    }

    Experimental::Threading::FutureResult<EntityId> DefaultRenderingSystem::CreateSpriteEntity(
        Experimental::Threading::ConcurrentSharedPtr<TextureInfo> texture)
    {
        std::scoped_lock guard(_createEntityWithRenderComponentQueueMutex);

        auto ptr = Experimental::Threading::MakeConcurrentShared<EntityId>();
        _createEntityWithRenderComponentQueue.emplace(ptr, std::move(texture));

        // TODO: I don't like this. At ALL. There's gotta be a better way to symbolise an invalid entity. :(
        return Experimental::Threading::FutureResult(ptr, std::numeric_limits<EntityId>::max());
    }
}
