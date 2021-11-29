// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>

namespace NovelRT::Ecs::Graphics
{
    void DefaultRenderingSystem::ResolveGpuFutures()
    {
        ResolveVertexInfoFutureResults();
        ResolveTextureFutureResults();
    }

    void DefaultRenderingSystem::ResolveVertexInfoFutureResults()
    {
        std::scoped_lock<tbb::mutex> guard(_vertexQueueMapMutex);

        while (!_vertexDataToInitialise.empty())
        {
            Experimental::Threading::ConcurrentSharedPtr<VertexInfo> ptr = _vertexDataToInitialise.front();
            _vertexDataToInitialise.pop();

            std::scoped_lock innerGuard(ptr);

            auto& resourceManager = _resourceManager.getActual();

            ptr->gpuVertexRegion =
                resourceManager.LoadVertexDataUntyped(ptr->stagingPtr, ptr->sizeOfVert, ptr->stagingPtrLength);
            ptr->ecsId = Atom::GetNextEcsVertexDataId();
            free(ptr->stagingPtr);
            ptr->stagingPtr = nullptr;
            _namedVertexInfoObjects.emplace(ptr->ecsId, ptr);
        }
    }

    void DefaultRenderingSystem::ResolveTextureFutureResults()
    {
        std::scoped_lock guard(_textureQueueMapMutex);

        while (!_texturesToInitialise.empty())
        {
            Experimental::Threading::ConcurrentSharedPtr<TextureInfo> ptr = _texturesToInitialise.front();
            _texturesToInitialise.pop();

            std::scoped_lock innerGuard(ptr);

            auto& resourceManager = _resourceManager.getActual();
            auto resourceLoader = _resourceManagementPluginProvider->GetResourceLoader();
            auto texture = resourceLoader->LoadTexture(ptr->textureName + ".png");

            auto texture2DRegion = resourceManager.LoadTextureData(
                texture, Experimental::Graphics::GraphicsTextureAddressMode::ClampToEdge,
                Experimental::Graphics::GraphicsTextureKind::TwoDimensional);

            *ptr = TextureInfo{texture2DRegion, ptr->textureName, ptr->ecsId};
            _namedTextureInfoObjects.emplace(ptr->ecsId, ptr);
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
          _matricesConstantBuffer(nullptr),
          //_projectionMatrixConstantBufferRegion(),
          _frameMatrixConstantBufferRegion(),
          _transformConstantBufferRegion(),
          _textureQueueMapMutex(),
          _namedTextureInfoObjects{},
          _texturesToInitialise(),
          _vertexQueueMapMutex(),
          _namedVertexInfoObjects{},
          _vertexDataToInitialise(),
          _defaultSpriteMeshPtr(nullptr),
          _namedGraphicsPipelineInfoObjects{},
          _defaultGraphicsPipelinePtr(nullptr),
          _renderScene()
    {
        _windowingPluginProvider->GetWindowingDevice()->Initialise(Windowing::WindowMode::Windowed,
                                                                   Maths::GeoVector2F(1920, 1080));

        EngineConfig::EnableDebugOutputFromEngineInternals() = true;
        EngineConfig::MinimumInternalLoggingLevel() = LogLevel::Debug;

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
                Experimental::Graphics::GraphicsPipelineResourceKind::ConstantBuffer,
                Experimental::Graphics::ShaderProgramVisibility::Vertex),

            /*
            Experimental::Graphics::GraphicsPipelineResource(
                Experimental::Graphics::GraphicsPipelineResourceKind::ConstantBuffer,
                Experimental::Graphics::ShaderProgramVisibility::Vertex),
                */

            Experimental::Graphics::GraphicsPipelineResource(
                Experimental::Graphics::GraphicsPipelineResourceKind::ConstantBuffer,
                Experimental::Graphics::ShaderProgramVisibility::Vertex),

            Experimental::Graphics::GraphicsPipelineResource(
                Experimental::Graphics::GraphicsPipelineResourceKind::Texture,
                Experimental::Graphics::ShaderProgramVisibility::Pixel),
        };

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
            TexturedVertexTest{Maths::GeoVector3F(-0.5, +0.5, 0), Maths::GeoVector2F(0.0f, 0.0f)},
            TexturedVertexTest{Maths::GeoVector3F(+0.5, +0.5, 0), Maths::GeoVector2F(1.0f, 0.0f)},
            TexturedVertexTest{Maths::GeoVector3F(+0.5, -0.5, 0), Maths::GeoVector2F(1.0f, 1.0f)},
            TexturedVertexTest{Maths::GeoVector3F(+0.5, -0.5, 0), Maths::GeoVector2F(1.0f, 1.0f)},
            TexturedVertexTest{Maths::GeoVector3F(-0.5, -0.5, 0), Maths::GeoVector2F(0.0f, 1.0f)},
            TexturedVertexTest{Maths::GeoVector3F(-0.5, +0.5, 0), Maths::GeoVector2F(0.0f, 0.0f)}};

        auto spriteMeshFuture = LoadVertexDataRaw<TexturedVertexTest>("default", pVertexBuffer);

        ResolveGpuFutures();

        _defaultSpriteMeshPtr = spriteMeshFuture.GetBackingConcurrentSharedPtr();

        _matricesConstantBuffer = _graphicsDevice->GetMemoryAllocator()->CreateBufferWithDefaultArguments(
            Experimental::Graphics::GraphicsBufferKind::Constant, Experimental::Graphics::GraphicsResourceAccess::Write,
            Experimental::Graphics::GraphicsResourceAccess::Read, 64 * 1024);

        auto windowingDevice = _windowingPluginProvider->GetWindowingDevice();

        /*
        _projectionMatrixConstantBufferRegion = _matricesConstantBuffer->Allocate(sizeof(Maths::GeoMatrix4x4F), 256);
        Maths::GeoMatrix4x4F* pProjectionMatrix =
            _matricesConstantBuffer->Map<Maths::GeoMatrix4x4F>(_projectionMatrixConstantBufferRegion);
        pProjectionMatrix[0] = Maths::GeoMatrix4x4F::CreateOrthographic(
            0.0f, windowingDevice->GetWidth(), windowingDevice->GetHeight(), 0.0f, 0.0f, 65535.0f);
        // pProjectionMatrix->y.y *= -1;
        _matricesConstantBuffer->UnmapAndWrite();
         */

        auto size = windowingDevice->GetSize();
        float width = size.x;
        float height = size.y;
        float halfWidth = width / 2.0f;
        float halfHeight = height / 2.0f;
        float left = -halfWidth;
        float right = +halfWidth;
        float top = -halfHeight;
        float bottom = +halfHeight;

        auto position = Maths::GeoVector2F::zero();
        auto projectionMatrix = Maths::GeoMatrix4x4F::CreateOrthographic(
            left, right, bottom, top, 0.1f, 65535.0f);
        auto viewMatrix = Maths::GeoMatrix4x4F::CreateFromLookAt(Maths::GeoVector3F(position.x, position.y, -1.0f),
                                                                 Maths::GeoVector3F(position.x, position.y, 0.0f),
                                                                 Maths::GeoVector3F(0, -1, 0));

        auto frameTransform = viewMatrix * projectionMatrix;
        frameTransform.Transpose();

        _frameMatrixConstantBufferRegion = _matricesConstantBuffer->Allocate(sizeof(Maths::GeoMatrix4x4F) * 2, 256);

        Maths::GeoMatrix4x4F* pFrameMatrix =
            _matricesConstantBuffer->Map<Maths::GeoMatrix4x4F>(_frameMatrixConstantBufferRegion);
        pFrameMatrix[0] = frameTransform;
        _matricesConstantBuffer->UnmapAndWrite();


        //Maths::GeoVector2F::uniform(500);
        /*float aspectRatio = 762.0f / 881.0f;
        scaleValue.y *= aspectRatio;*/

        _transformConstantBufferRegion = _matricesConstantBuffer->Allocate(sizeof(Maths::GeoMatrix4x4F), 256);

        graphicsContext->EndFrame();
        _graphicsDevice->Signal(graphicsContext->GetFence());
        _graphicsDevice->WaitForIdle();
    }

    void DefaultRenderingSystem::Update(Timing::Timestamp /*delta*/, Ecs::Catalogue catalogue)
    {
        std::vector<GraphicsPrimitiveInfo> primitiveCache{};
        primitiveCache.reserve(32); // TODO: make this configurable.

        auto context = _graphicsDevice->GetCurrentContext();
        context->BeginFrame();

        // TODO: This call is probably not supposed to be here but we have nowhere else for it to live right now. :)
        ResolveGpuFutures();

        context->BeginDrawing(NovelRT::Graphics::RGBAColour(0, 0, 255, 255));

        ComponentView<RenderComponent> renderComponents = catalogue.GetComponentView<RenderComponent>();

        for (auto [entity, component] : renderComponents)
        {
            std::optional<GraphicsPrimitiveInfo> primitiveInfo;

            for (auto&& primitive : primitiveCache)
            {
                if ((primitive.ecsPipelineId != component.pipelineId) ||
                    (primitive.ecsTextureId != component.textureId) ||
                    (primitive.ecsVertexDataId != component.vertexDataId))
                {
                    continue;
                }

                primitiveInfo = primitive;
            }

            if (!primitiveInfo.has_value())
            {
                auto& vertexData = _namedVertexInfoObjects.at(component.vertexDataId);
                auto& textureData = _namedTextureInfoObjects.at(component.textureId);
                auto& pipelineData = _namedGraphicsPipelineInfoObjects.at(component.pipelineId);

                std::vector<Experimental::Graphics::GraphicsMemoryRegion<Experimental::Graphics::GraphicsResource>>
                    resourceRegions{/*_projectionMatrixConstantBufferRegion,*/ _frameMatrixConstantBufferRegion,
                                    _transformConstantBufferRegion, textureData->gpuTextureRegion};

                auto dummyRegion =
                    Experimental::Graphics::GraphicsMemoryRegion<Experimental::Graphics::GraphicsResource>(
                        0, nullptr, _graphicsDevice, false, 0, 0);
                primitiveCache.emplace_back(GraphicsPrimitiveInfo{
                    _graphicsDevice->CreatePrimitive(pipelineData->gpuPipeline.GetUnderlyingSharedPtr(),
                                                     vertexData->gpuVertexRegion,
                                                     static_cast<uint32_t>(vertexData->sizeOfVert), dummyRegion,
                                                     vertexData->stride, resourceRegions),
                    vertexData->ecsId, textureData->ecsId, pipelineData->ecsId});

                primitiveInfo = primitiveCache.back();
            }

            auto size = _windowingPluginProvider->GetWindowingDevice()->GetSize();
            float width = size.x;
            float height = size.y;
            auto testTransformOne = Maths::GeoMatrix4x4F::getDefaultIdentity();
            auto scaleValue = Maths::GeoVector2F(500, 500);
            float aspect = (width < height) ? (width / height) : (height / width);
            unused(aspect);

            /*
            if (aspect == 1)
            {
                aspect = width / 762; //pretend the "512" is either the width or height, whichever is smaller
            }
             */

            float imageAspect = (881.0f / 762.0f);
            scaleValue.y *= imageAspect;
            //scaleValue *= 0.25f;
            //testTransformOne.Translate(Maths::GeoVector3F(-100, 0, 0));
            testTransformOne.Scale(scaleValue);
            testTransformOne.Transpose();


            auto testTransformTwo = Maths::GeoMatrix4x4F::getDefaultIdentity();
            scaleValue = Maths::GeoVector2F(50, 100);
            //scaleValue *= aspect;
            testTransformTwo.Translate(Maths::GeoVector3F(100, 0, 0));
            testTransformTwo.Scale(scaleValue);
            testTransformTwo.Transpose();

            Maths::GeoMatrix4x4F* pTransformMatrix =
                _matricesConstantBuffer->Map<Maths::GeoMatrix4x4F>(_transformConstantBufferRegion);
            pTransformMatrix[0] = testTransformOne;
            pTransformMatrix[1] = testTransformTwo;
            _matricesConstantBuffer->UnmapAndWrite();

            context->Draw(primitiveInfo->primitive, 1);
        }

        context->EndDrawing();
        context->EndFrame();
        _graphicsDevice->PresentFrame();
        _graphicsDevice->WaitForIdle();
    }

    Experimental::Threading::FutureResult<TextureInfo> DefaultRenderingSystem::GetOrLoadTexture(
        const std::string& textureName)
    {
        std::scoped_lock guard(_textureQueueMapMutex);

        auto resultIterator =
            std::find_if(_namedTextureInfoObjects.begin(), _namedTextureInfoObjects.end(),
                         [textureName](const auto& pair) { return textureName == pair.second->textureName; });

        if (resultIterator == _namedTextureInfoObjects.end())
        {
            auto concurrentPtr = Experimental::Threading::MakeConcurrentShared<TextureInfo>();
            concurrentPtr->textureName = textureName;
            concurrentPtr->ecsId = Atom::GetNextEcsTextureId();

            _texturesToInitialise.push(concurrentPtr);
            return Experimental::Threading::FutureResult<TextureInfo>(concurrentPtr, TextureInfo{});
        }

        return Experimental::Threading::FutureResult<TextureInfo>(resultIterator->second, TextureInfo{});
    }

    Experimental::Threading::ConcurrentSharedPtr<TextureInfo> DefaultRenderingSystem::GetExistingTextureBasedOnId(
        Atom ecsId)
    {
        std::scoped_lock guard(_textureQueueMapMutex);
        return _namedTextureInfoObjects.at(ecsId);
    }

    Experimental::Threading::FutureResult<VertexInfo> DefaultRenderingSystem::LoadVertexDataRawUntyped(
        const std::string& vertexDataName,
        void* data,
        size_t dataTypeSize,
        size_t dataLength)
    {
        std::scoped_lock guard(_vertexQueueMapMutex);

        auto ptr = Experimental::Threading::MakeConcurrentShared<VertexInfo>();
        size_t size = dataTypeSize * dataLength;
        ptr->vertexInfoName = vertexDataName;
        ptr->stagingPtr = malloc(size);
        ptr->sizeOfVert = dataTypeSize;
        ptr->stagingPtrLength = dataLength;
        memcpy_s(ptr->stagingPtr, size, data, size);
        _vertexDataToInitialise.push(ptr);

        return Experimental::Threading::FutureResult<VertexInfo>(ptr, VertexInfo{});
    }

    Experimental::Threading::ConcurrentSharedPtr<VertexInfo> DefaultRenderingSystem::GetExistingVertexDataBasedOnName(
        const std::string& vertexDataName)
    {
        std::scoped_lock guard(_vertexQueueMapMutex);

        for (auto&& pair : _namedVertexInfoObjects)
        {
            if (pair.second->vertexInfoName != vertexDataName)
            {
                continue;
            }

            return pair.second;
        }

        throw Exceptions::KeyNotFoundException();
    }

    Experimental::Threading::ConcurrentSharedPtr<VertexInfo> DefaultRenderingSystem::GetExistingVertexDataBasedOnId(
        Atom ecsId)
    {
        std::scoped_lock guard(_vertexQueueMapMutex);
        return _namedVertexInfoObjects.at(ecsId);
    }

    Experimental::Threading::ConcurrentSharedPtr<GraphicsPipelineInfo> DefaultRenderingSystem::RegisterPipeline(
        const std::string& pipelineName,
        std::shared_ptr<Experimental::Graphics::GraphicsPipeline> pipeline)
    {
        std::scoped_lock guard(_graphicsPipelineMapMutex);

        auto ptr = Experimental::Threading::MakeConcurrentShared<GraphicsPipelineInfo>();
        ptr->gpuPipeline =
            Experimental::Threading::ConcurrentSharedPtr<Experimental::Graphics::GraphicsPipeline>(std::move(pipeline));
        ptr->pipelineName = pipelineName;
        ptr->ecsId = Atom::GetNextEcsGraphicsPipelineId();

        _namedGraphicsPipelineInfoObjects.emplace(ptr->ecsId, ptr);

        return ptr;
    }

    void DefaultRenderingSystem::AttachSpriteRenderingToEntity(
        EntityId entity,
        Experimental::Threading::ConcurrentSharedPtr<TextureInfo> texture,
        Catalogue& catalogue)
    {
        ComponentView<RenderComponent> renderComponentView = catalogue.GetComponentView<RenderComponent>();

        renderComponentView.AddComponent(
            entity, RenderComponent{_defaultSpriteMeshPtr->ecsId, texture->ecsId, _defaultGraphicsPipelinePtr->ecsId});
    }

    EntityId DefaultRenderingSystem::CreateSpriteEntity(
        Experimental::Threading::ConcurrentSharedPtr<TextureInfo> texture,
        Catalogue& catalogue)
    {
        EntityId entity = catalogue.CreateEntity();
        AttachSpriteRenderingToEntity(entity, std::move(texture), catalogue);
        return entity;
    }

    EntityId DefaultRenderingSystem::CreateSpriteEntityOutsideOfSystem(
        Experimental::Threading::ConcurrentSharedPtr<TextureInfo> texture,
        SystemScheduler& scheduler)
    {
        EntityId entity = Atom::GetNextEntityId();

        scheduler.GetComponentCache().GetComponentBuffer<RenderComponent>().PushComponentUpdateInstruction(
            0, entity,
            RenderComponent{_defaultSpriteMeshPtr->ecsId, texture->ecsId, _defaultGraphicsPipelinePtr->ecsId});
        return entity;
    }

    void DefaultRenderingSystem::ForceVertexTextureFutureResolution()
    {
        auto currentContext = _graphicsDevice->GetCurrentContext();
        currentContext->BeginFrame();
        ResolveGpuFutures();
        currentContext->EndFrame();
        _graphicsDevice->Signal(currentContext->GetFence());
        _graphicsDevice->WaitForIdle();
    }
}
