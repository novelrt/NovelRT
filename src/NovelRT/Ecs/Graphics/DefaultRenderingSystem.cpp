// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>

namespace NovelRT::Ecs::Graphics
{
    void DefaultRenderingSystem::ResolveGpuResourceCleanup()
    {
        ResolveVertexInfoGpuCleanup();
        ResolveTextureInfoGpuCleanup();
    }

    void DefaultRenderingSystem::ResolveVertexInfoGpuCleanup()
    {
        std::scoped_lock guard(_vertexQueueMapMutex);

        while (!_vertexDataToDelete.empty())
        {
            Atom ecsId = _vertexDataToDelete.front();
            _vertexDataToDelete.pop();

            _resourceManager.getActual().FreeVertexData(_namedVertexInfoObjects.at(ecsId)->gpuVertexRegion);
            _namedVertexInfoObjects.erase(ecsId);
        }
    }

    void DefaultRenderingSystem::ResolveTextureInfoGpuCleanup()
    {
        std::scoped_lock guard(_textureQueueMapMutex);

        while (!_texturesToDelete.empty())
        {
            Atom ecsId = _texturesToDelete.front();
            _texturesToDelete.pop();

            _resourceManager.getActual().FreeTextureData(_namedTextureInfoObjects.at(ecsId)->gpuTextureRegion);
            _namedVertexInfoObjects.erase(ecsId);
        }
    }

    void DefaultRenderingSystem::ResolveGpuFutures()
    {
        ResolveVertexInfoFutureResults();
        ResolveTextureFutureResults();
    }

    void DefaultRenderingSystem::ResolveVertexInfoFutureResults()
    {
        static AtomFactory& vertexDataIdFactory = AtomFactoryDatabase::GetFactory("VertexDataId");

        std::scoped_lock guard(_vertexQueueMapMutex);

        while (!_vertexDataToInitialise.empty())
        {
            Threading::ConcurrentSharedPtr<VertexInfo> ptr = _vertexDataToInitialise.front();
            _vertexDataToInitialise.pop();

            std::scoped_lock innerGuard(ptr);

            auto& resourceManager = _resourceManager.getActual();

            ptr->gpuVertexRegion =
                resourceManager.LoadVertexDataUntyped(ptr->stagingPtr, ptr->sizeOfVert, ptr->stagingPtrLength);
            ptr->ecsId = vertexDataIdFactory.GetNext();
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
            Threading::ConcurrentSharedPtr<TextureInfo> ptr = _texturesToInitialise.front();
            _texturesToInitialise.pop();

            std::scoped_lock innerGuard(ptr);

            auto& resourceManager = _resourceManager.getActual();
            auto resourceLoader = _resourceManagementPluginProvider->GetResourceLoader();
            ResourceManagement::TextureMetadata texture;

            if (!ptr->textureData.empty())
            {
                texture.width = ptr->width;
                texture.height = ptr->height;
                texture.pixelCount = ptr->width * ptr->height;
                texture.data = ptr->textureData;
            }
            else
            {
                texture = resourceLoader->LoadTextureFromFile(ptr->textureName + ".png");
            }

            auto texture2DRegion =
                resourceManager.LoadTextureData(texture, NovelRT::Graphics::GraphicsTextureAddressMode::ClampToEdge,
                                                NovelRT::Graphics::GraphicsTextureKind::TwoDimensional);

            *ptr = TextureInfo{texture2DRegion, ptr->textureName, texture.width,
                               texture.height,  ptr->ecsId,       std::vector<uint8_t>{}};
            _namedTextureInfoObjects.emplace(ptr->ecsId, ptr);
        }
    }

    DefaultRenderingSystem::DefaultRenderingSystem(
        std::shared_ptr<PluginManagement::IGraphicsPluginProvider> graphicsPluginProvider,
        std::shared_ptr<PluginManagement::IWindowingPluginProvider> windowingPluginProvider,
        std::shared_ptr<PluginManagement::IResourceManagementPluginProvider> resourceManagementPluginProvider)
        : _resourceManager([&]() { return NovelRT::Graphics::GraphicsResourceManager(_graphicsDevice); }),
          _graphicsPluginProvider(std::move(graphicsPluginProvider)),
          _windowingPluginProvider(std::move(windowingPluginProvider)),
          _resourceManagementPluginProvider(std::move(resourceManagementPluginProvider)),
          _surfaceContext(nullptr),
          _graphicsAdapter(nullptr),
          _graphicsDevice(nullptr),
          _windowingDevice(nullptr),
          _frameMatrixConstantBufferRegion(),
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
        _windowingDevice = _windowingPluginProvider->GetWindowingDevice();
        _windowingDevice->Initialise(Windowing::WindowMode::Windowed, Maths::GeoVector2F(1920, 1080));

        _surfaceContext = _graphicsPluginProvider->CreateSurfaceContext(_windowingPluginProvider->GetWindowingDevice());
        _graphicsAdapter = _graphicsPluginProvider->GetDefaultSelectedGraphicsAdapterForContext(_surfaceContext);
        _graphicsDevice = _graphicsAdapter->CreateDevice(_surfaceContext, 2);

        auto resourceLoader = _resourceManagementPluginProvider->GetResourceLoader();
        auto vertShaderData = resourceLoader->LoadShaderSource("vert.spv");
        auto pixelShaderData = resourceLoader->LoadShaderSource("frag.spv");

        std::vector<NovelRT::Graphics::GraphicsPipelineInputElement> elements = {
            NovelRT::Graphics::GraphicsPipelineInputElement(
                typeid(NovelRT::Maths::GeoVector3F), NovelRT::Graphics::GraphicsPipelineInputElementKind::Position, 12),

            NovelRT::Graphics::GraphicsPipelineInputElement(
                typeid(NovelRT::Maths::GeoVector2F),
                NovelRT::Graphics::GraphicsPipelineInputElementKind::TextureCoordinate, 8)};

        std::vector<NovelRT::Graphics::GraphicsPipelineInput> inputs = {
            NovelRT::Graphics::GraphicsPipelineInput(elements)};

        std::vector<NovelRT::Graphics::GraphicsPipelineResource> resources = {
            NovelRT::Graphics::GraphicsPipelineResource(NovelRT::Graphics::GraphicsPipelineResourceKind::ConstantBuffer,
                                                        NovelRT::Graphics::ShaderProgramVisibility::Vertex),

            NovelRT::Graphics::GraphicsPipelineResource(NovelRT::Graphics::GraphicsPipelineResourceKind::ConstantBuffer,
                                                        NovelRT::Graphics::ShaderProgramVisibility::Vertex),

            NovelRT::Graphics::GraphicsPipelineResource(NovelRT::Graphics::GraphicsPipelineResourceKind::Texture,
                                                        NovelRT::Graphics::ShaderProgramVisibility::Pixel),
        };

        auto vertexShaderProgram =
            _graphicsDevice->CreateShaderProgram("main", NovelRT::Graphics::ShaderProgramKind::Vertex, vertShaderData);
        auto pixelShaderProgram =
            _graphicsDevice->CreateShaderProgram("main", NovelRT::Graphics::ShaderProgramKind::Pixel, pixelShaderData);
        auto signature = _graphicsDevice->CreatePipelineSignature(
            NovelRT::Graphics::GraphicsPipelineBlendFactor::SrcAlpha,
            NovelRT::Graphics::GraphicsPipelineBlendFactor::OneMinusSrcAlpha, inputs, resources);
        auto pipeline = _graphicsDevice->CreatePipeline(signature, vertexShaderProgram, pixelShaderProgram);

        _defaultGraphicsPipelinePtr = RegisterPipeline("default", pipeline);

        auto graphicsContext = _graphicsDevice->GetCurrentContext();

        graphicsContext->BeginFrame();
        auto pVertexBuffer = std::vector<TexturedVertex>{
            TexturedVertex{Maths::GeoVector3F(-0.5, +0.5, 0), Maths::GeoVector2F(0.0f, 0.0f)},
            TexturedVertex{Maths::GeoVector3F(+0.5, +0.5, 0), Maths::GeoVector2F(1.0f, 0.0f)},
            TexturedVertex{Maths::GeoVector3F(+0.5, -0.5, 0), Maths::GeoVector2F(1.0f, 1.0f)},
            TexturedVertex{Maths::GeoVector3F(+0.5, -0.5, 0), Maths::GeoVector2F(1.0f, 1.0f)},
            TexturedVertex{Maths::GeoVector3F(-0.5, -0.5, 0), Maths::GeoVector2F(0.0f, 1.0f)},
            TexturedVertex{Maths::GeoVector3F(-0.5, +0.5, 0), Maths::GeoVector2F(0.0f, 0.0f)}};

        auto spriteMeshFuture = LoadVertexDataRaw<TexturedVertex>("default", pVertexBuffer);

        ResolveGpuFutures();

        _defaultSpriteMeshPtr = spriteMeshFuture.GetBackingConcurrentSharedPtr();

        auto windowingDevice = _windowingPluginProvider->GetWindowingDevice();

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
        auto projectionMatrix = Maths::GeoMatrix4x4F::CreateOrthographic(left, right, bottom, top, 0.1f, 65535.0f);
        auto viewMatrix = Maths::GeoMatrix4x4F::CreateFromLookAt(Maths::GeoVector3F(position.x, position.y, -1.0f),
                                                                 Maths::GeoVector3F(position.x, position.y, 0.0f),
                                                                 Maths::GeoVector3F(0, -1, 0));

        // This is correct for row-major. :]
        auto frameTransform = viewMatrix * projectionMatrix;

        _frameMatrixConstantBufferRegion = _resourceManager.getActual().LoadConstantBufferDataToNewRegion(
            &frameTransform, sizeof(Maths::GeoMatrix4x4F));

        graphicsContext->EndFrame();
        _graphicsDevice->Signal(graphicsContext->GetFence());
        _graphicsDevice->WaitForIdle();

        windowingDevice->SizeChanged += [&](Maths::GeoVector2F newSize) {
            float width = newSize.x;
            float height = newSize.y;
            float halfWidth = width / 2.0f;
            float halfHeight = height / 2.0f;
            float left = -halfWidth;
            float right = +halfWidth;
            float top = -halfHeight;
            float bottom = +halfHeight;

            auto position = Maths::GeoVector2F::zero();
            auto projectionMatrix = Maths::GeoMatrix4x4F::CreateOrthographic(left, right, bottom, top, 0.1f, 65535.0f);
            auto viewMatrix = Maths::GeoMatrix4x4F::CreateFromLookAt(Maths::GeoVector3F(position.x, position.y, -1.0f),
                                                                     Maths::GeoVector3F(position.x, position.y, 0.0f),
                                                                     Maths::GeoVector3F(0, -1, 0));

            auto frameTransform = viewMatrix * projectionMatrix; // This is correct for row-major. :]

            _frameMatrixConstantBufferRegion = _resourceManager.getActual().LoadConstantBufferDataToNewRegion(
                &frameTransform, sizeof(Maths::GeoMatrix4x4F));
            ;
        };
    }

    void DefaultRenderingSystem::Update(Timing::Timestamp delta, Ecs::Catalogue catalogue)
    {
        auto dummyRegion = NovelRT::Graphics::GraphicsMemoryRegion<NovelRT::Graphics::GraphicsResource>(
            0, nullptr, _graphicsDevice, false, 0, 0);
        auto& gpuResourceManager = _resourceManager.getActual();

        auto context = _graphicsDevice->GetCurrentContext();
        context->BeginFrame();

        ResolveGpuResourceCleanup();
        ResolveGpuFutures();

        context->BeginDrawing(NovelRT::Graphics::RGBAColour(0, 0, 255, 255));

        auto [renderComponents, transformComponents, entityGraphComponents] =
            catalogue.GetComponentViews<RenderComponent, TransformComponent, EntityGraphComponent>();

        std::map<int32_t, std::vector<EntityId>> transformLayerMap{};

        for (auto [entity, transformComponent] : transformComponents)
        {
            RenderComponent renderComponent{};

            if (!renderComponents.TryGetComponent(entity, renderComponent))
            {
                continue;
            }

            int32_t layer = static_cast<int32_t>(transformComponent.positionAndLayer.z);

            if (transformLayerMap.find(layer) == transformLayerMap.end())
            {
                transformLayerMap[layer] = std::vector<EntityId>{};
                transformLayerMap[layer].reserve(1000);
            }

            transformLayerMap[layer].emplace_back(entity);
        }

        struct GpuSpanCounter
        {
            Maths::GeoMatrix4x4F* gpuData = nullptr;
            size_t currentIndex = 0;
        };

        std::unordered_map<Atom, std::map<int32_t, GpuSpanCounter>, AtomHashFunction> gpuSpanCounterMap{};

        for (auto reverseIt = transformLayerMap.rbegin(); reverseIt != transformLayerMap.rend(); reverseIt++)
        {
            auto&& [layer, entityVector] = *reverseIt;

            for (EntityId entity : entityVector)
            {
                RenderComponent renderComponent = renderComponents.GetComponentUnsafe(entity);
                TransformComponent transformComponent = transformComponents.GetComponentUnsafe(entity);

                if (gpuSpanCounterMap.find(renderComponent.primitiveInfoId) == gpuSpanCounterMap.end())
                {
                    gpuSpanCounterMap[renderComponent.primitiveInfoId] = std::map<int32_t, GpuSpanCounter>{};
                    gpuSpanCounterMap[renderComponent.primitiveInfoId][layer] =
                        GpuSpanCounter{gpuResourceManager.MapConstantBufferRegionForWriting<Maths::GeoMatrix4x4F>(
                                           _primitiveConfigurations[renderComponent.primitiveInfoId]
                                               .gpuTransformConstantBufferRegions[layer]),
                                       0};
                }

                auto textureInfo = GetExistingTexture(renderComponent.textureId);
                GpuSpanCounter& tempSpanCounter = gpuSpanCounterMap[renderComponent.primitiveInfoId][layer];
                auto scaleValue = Maths::GeoVector2F::uniform(500);
                float aspect = static_cast<float>(textureInfo->height) / static_cast<float>(textureInfo->width);
                scaleValue.y *= aspect;
                Maths::GeoMatrix4x4F matrixToInsert = Maths::GeoMatrix4x4F::getDefaultIdentity();

                std::vector<TransformComponent> parentTransforms{};

                auto graphComponent = entityGraphComponents.GetComponentUnsafe(entity);

                while (graphComponent.parent != std::numeric_limits<EntityId>::max())
                {
                    TransformComponent transform = transformComponents.GetComponentUnsafe(graphComponent.parent);
                    parentTransforms.emplace_back(transform);
                    graphComponent = entityGraphComponents.GetComponentUnsafe(graphComponent.parent);
                }

                scaleValue *= transformComponent.scale;

                // TODO: There is definitely a better way to handle this but I'm being stupid.
                for (auto it = parentTransforms.rbegin(); it != parentTransforms.rend(); it++)
                {
                    matrixToInsert.Translate(it->positionAndLayer);
                    matrixToInsert.Rotate(it->rotationInRadians);
                    scaleValue *= it->scale;
                }

                matrixToInsert.Translate(transformComponent.positionAndLayer);
                matrixToInsert.Rotate(transformComponent.rotationInRadians);
                matrixToInsert.Scale(scaleValue); // scale based on aspect. :]

                tempSpanCounter.gpuData[tempSpanCounter.currentIndex++] = matrixToInsert;
            }
        }

        gpuResourceManager.UnmapAndWriteAllConstantBuffers();

        int32_t farthestLayer = transformLayerMap.rbegin()->first;
        int32_t closestLayer = transformLayerMap.begin()->first;

        std::vector<std::shared_ptr<NovelRT::Graphics::GraphicsPrimitive>> primitiveCache{};
        primitiveCache.reserve(1000);

        for (int32_t layer = farthestLayer; layer >= closestLayer; layer--)
        {
            for (auto&& [primitiveInfoId, spanCounterMap] : gpuSpanCounterMap)
            {
                auto& primitiveInfo = _primitiveConfigurations[primitiveInfoId];
                auto pipelineInfo = GetExistingPipelineInfo(primitiveInfo.ecsPipelineId);
                auto texture = GetExistingTexture(primitiveInfo.ecsTextureId);
                auto mesh = GetExistingVertexData(primitiveInfo.ecsVertexDataId);

                std::vector<NovelRT::Graphics::GraphicsMemoryRegion<NovelRT::Graphics::GraphicsResource>>
                    inputResourceRegions{};

                if (pipelineInfo->useEcsTransforms)
                {
                    size_t customConstantBuffersCount = (pipelineInfo->gpuCustomConstantBuffers != nullptr)
                                                            ? pipelineInfo->gpuCustomConstantBuffers->size()
                                                            : 0;
                    inputResourceRegions.reserve(
                        2 + customConstantBuffersCount); // 2 for the frame transform and the ecs transform data
                    inputResourceRegions.emplace_back(_frameMatrixConstantBufferRegion);
                    inputResourceRegions.emplace_back(primitiveInfo.gpuTransformConstantBufferRegions[layer]);
                }
                else
                {
                    size_t customConstantBuffersCount = (pipelineInfo->gpuCustomConstantBuffers != nullptr)
                                                            ? pipelineInfo->gpuCustomConstantBuffers->size()
                                                            : 0;
                    inputResourceRegions.reserve(customConstantBuffersCount);
                }

                inputResourceRegions.emplace_back(texture->gpuTextureRegion);

                if (pipelineInfo->gpuCustomConstantBuffers != nullptr)
                {
                    for (auto&& region : *pipelineInfo->gpuCustomConstantBuffers)
                    {
                        inputResourceRegions.emplace_back(region);
                    }
                }

                size_t amountToDraw = spanCounterMap[layer].currentIndex;

                auto primitive = _graphicsDevice->CreatePrimitive(pipelineInfo->gpuPipeline.GetUnderlyingSharedPtr(),
                                                                  mesh->gpuVertexRegion, sizeof(TexturedVertex),
                                                                  dummyRegion, 0, inputResourceRegions);
                context->Draw(primitive, static_cast<int32_t>(amountToDraw));
                primitiveCache.emplace_back(primitive);
            }
        }

        UIRenderEvent(*this, UIRenderEventArgs{delta, catalogue, _surfaceContext, _graphicsAdapter, _graphicsDevice,
                                               context, gpuResourceManager, _frameMatrixConstantBufferRegion});

        context->EndDrawing();
        context->EndFrame();
        _graphicsDevice->PresentFrame();
        _graphicsDevice->WaitForIdle();
    }

    Threading::FutureResult<TextureInfo> DefaultRenderingSystem::GetOrLoadTexture(const std::string& textureName)
    {
        std::scoped_lock guard(_textureQueueMapMutex);

        auto resultIterator =
            std::find_if(_namedTextureInfoObjects.begin(), _namedTextureInfoObjects.end(),
                         [textureName](const auto& pair) { return textureName == pair.second->textureName; });

        if (resultIterator == _namedTextureInfoObjects.end())
        {
            auto concurrentPtr = Threading::MakeConcurrentShared<TextureInfo>();
            concurrentPtr->textureName = textureName;
            concurrentPtr->ecsId = _textureIdFactory.GetNext();

            _texturesToInitialise.push(concurrentPtr);
            return Threading::FutureResult<TextureInfo>(concurrentPtr, *concurrentPtr);
        }

        return Threading::FutureResult<TextureInfo>(resultIterator->second, TextureInfo{});
    }

    Threading::FutureResult<TextureInfo> DefaultRenderingSystem::LoadTextureDataRawUntyped(
        const std::string& textureDataName,
        void* data,
        size_t dataTypeSize,
        size_t dataLength,
        uint32_t width,
        uint32_t height)
    {
        std::scoped_lock guard(_textureQueueMapMutex);

        auto ptr = Threading::MakeConcurrentShared<TextureInfo>();
        std::vector<uint8_t> textureData{};
        textureData.resize(dataTypeSize * dataLength);

        memcpy(textureData.data(), data, dataTypeSize * dataLength);

        ptr->textureName = textureDataName;
        ptr->textureData = textureData;
        ptr->width = width;
        ptr->height = height;
        ptr->ecsId = _textureIdFactory.GetNext();
        _texturesToInitialise.push(ptr);

        return Threading::FutureResult<TextureInfo>(ptr, *ptr);
    }

    Threading::ConcurrentSharedPtr<TextureInfo> DefaultRenderingSystem::GetExistingTexture(Atom ecsId)
    {
        std::scoped_lock guard(_textureQueueMapMutex);
        return _namedTextureInfoObjects.at(ecsId);
    }

    Threading::ConcurrentSharedPtr<TextureInfo> DefaultRenderingSystem::GetExistingTexture(const std::string& name)
    {
        std::scoped_lock guard(_textureQueueMapMutex);

        for (auto&& pair : _namedTextureInfoObjects)
        {
            if (pair.second->textureName != name)
            {
                continue;
            }

            return pair.second;
        }

        throw Exceptions::KeyNotFoundException();
    }

    void DefaultRenderingSystem::DeleteTexture(Threading::ConcurrentSharedPtr<TextureInfo> texture)
    {
        std::scoped_lock guard(_textureQueueMapMutex);

        std::optional<Atom> ecsId;

        for (auto&& pair : _namedTextureInfoObjects)
        {
            if (pair.second != texture)
            {
                continue;
            }

            ecsId = pair.first;
            break;
        }

        _texturesToDelete.push(ecsId.value());
    }

    void DefaultRenderingSystem::DeleteTexture(Atom ecsId)
    {
        std::scoped_lock guard(_textureQueueMapMutex);

        auto it = _namedTextureInfoObjects.find(ecsId);

        if (it == _namedTextureInfoObjects.end())
        {
            throw Exceptions::KeyNotFoundException();
        }

        _texturesToDelete.push(ecsId);
    }

    void DefaultRenderingSystem::DeleteTexture(const std::string& name)
    {
        std::scoped_lock guard(_textureQueueMapMutex);

        std::optional<Atom> ecsId;
        for (auto&& pair : _namedTextureInfoObjects)
        {
            if (pair.second->textureName != name)
            {
                continue;
            }

            ecsId = pair.first;
            break;
        }

        if (!ecsId.has_value())
        {
            throw Exceptions::KeyNotFoundException();
        }

        _texturesToDelete.push(ecsId.value());
    }

    Threading::FutureResult<VertexInfo> DefaultRenderingSystem::LoadVertexDataRawUntyped(
        const std::string& vertexDataName,
        void* data,
        size_t dataTypeSize,
        size_t dataLength)
    {
        std::scoped_lock guard(_vertexQueueMapMutex);

        auto ptr = Threading::MakeConcurrentShared<VertexInfo>();
        size_t size = dataTypeSize * dataLength;
        ptr->vertexInfoName = vertexDataName;
        ptr->stagingPtr = malloc(size);
        ptr->sizeOfVert = dataTypeSize;
        ptr->stagingPtrLength = dataLength;

#ifdef WIN32
        memcpy_s(ptr->stagingPtr, size, data, size);
#else
        memcpy(ptr->stagingPtr, data, size);
#endif
        _vertexDataToInitialise.push(ptr);

        return Threading::FutureResult<VertexInfo>(ptr, VertexInfo{});
    }

    Threading::ConcurrentSharedPtr<VertexInfo> DefaultRenderingSystem::GetExistingVertexData(
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

    Threading::ConcurrentSharedPtr<VertexInfo> DefaultRenderingSystem::GetExistingVertexData(Atom ecsId)
    {
        std::scoped_lock guard(_vertexQueueMapMutex);
        return _namedVertexInfoObjects.at(ecsId);
    }

    void DefaultRenderingSystem::DeleteVertexData(Threading::ConcurrentSharedPtr<VertexInfo> vertexData)
    {
        std::scoped_lock guard(_vertexQueueMapMutex);

        std::optional<Atom> ecsId;
        for (auto&& pair : _namedVertexInfoObjects)
        {
            if (pair.second != vertexData)
            {
                continue;
            }

            ecsId = pair.first;
        }

        if (!ecsId.has_value())
        {
            throw Exceptions::KeyNotFoundException();
        }

        _vertexDataToDelete.push(ecsId.value());
    }

    void DefaultRenderingSystem::DeleteVertexData(Atom ecsId)
    {
        std::scoped_lock guard(_vertexQueueMapMutex);

        auto it = _namedVertexInfoObjects.find(ecsId);

        if (it == _namedVertexInfoObjects.end())
        {
            throw Exceptions::KeyNotFoundException();
        }

        _vertexDataToDelete.push(ecsId);
    }

    void DefaultRenderingSystem::DeleteVertexData(const std::string& name)
    {
        std::scoped_lock guard(_vertexQueueMapMutex);

        std::optional<Atom> ecsId;
        for (auto&& pair : _namedVertexInfoObjects)
        {
            if (pair.second->vertexInfoName != name)
            {
                continue;
            }

            ecsId = pair.first;
            break;
        }

        if (!ecsId.has_value())
        {
            throw Exceptions::KeyNotFoundException();
        }

        _vertexDataToDelete.push(ecsId.value());
    }

    Threading::ConcurrentSharedPtr<GraphicsPipelineInfo> DefaultRenderingSystem::GetExistingPipelineInfo(
        const std::string& name)
    {
        std::scoped_lock guard(_graphicsPipelineMapMutex);

        for (auto&& pair : _namedGraphicsPipelineInfoObjects)
        {
            if (pair.second->pipelineName != name)
            {
                continue;
            }

            return pair.second;
        }

        throw Exceptions::KeyNotFoundException();
    }

    Threading::ConcurrentSharedPtr<GraphicsPipelineInfo> DefaultRenderingSystem::GetExistingPipelineInfo(Atom ecsId)
    {
        std::scoped_lock guard(_graphicsPipelineMapMutex);
        return _namedGraphicsPipelineInfoObjects.at(ecsId);
    }

    Threading::ConcurrentSharedPtr<GraphicsPipelineInfo> DefaultRenderingSystem::RegisterPipeline(
        const std::string& pipelineName,
        std::shared_ptr<NovelRT::Graphics::GraphicsPipeline> pipeline,
        std::vector<NovelRT::Graphics::GraphicsMemoryRegion<NovelRT::Graphics::GraphicsResource>>
            customConstantBufferRegions,
        bool useEcsTransforms)
    {
        static AtomFactory& ecsGraphicsPipelineIdFactory = AtomFactoryDatabase::GetFactory("EcsGraphicsPipelineId");

        std::scoped_lock guard(_graphicsPipelineMapMutex);

        auto ptr = Threading::MakeConcurrentShared<GraphicsPipelineInfo>();
        ptr->gpuPipeline = Threading::ConcurrentSharedPtr<NovelRT::Graphics::GraphicsPipeline>(std::move(pipeline));
        ptr->pipelineName = pipelineName;
        ptr->ecsId = ecsGraphicsPipelineIdFactory.GetNext();
        ptr->useEcsTransforms = useEcsTransforms;

        if (!customConstantBufferRegions.empty())
        {
            auto rawShared = std::make_shared<
                std::vector<NovelRT::Graphics::GraphicsMemoryRegion<NovelRT::Graphics::GraphicsResource>>>();
            *rawShared = std::move(customConstantBufferRegions);
            ptr->gpuCustomConstantBuffers = Threading::ConcurrentSharedPtr<
                std::vector<NovelRT::Graphics::GraphicsMemoryRegion<NovelRT::Graphics::GraphicsResource>>>(
                std::move(rawShared));
        }

        _namedGraphicsPipelineInfoObjects.emplace(ptr->ecsId, ptr);

        return ptr;
    }

    void DefaultRenderingSystem::UnregisterPipeline(Threading::ConcurrentSharedPtr<GraphicsPipelineInfo> pipelineInfo)
    {
        std::lock_guard guard(_graphicsPipelineMapMutex);

        std::optional<Atom> ecsId;
        for (auto&& pair : _namedGraphicsPipelineInfoObjects)
        {
            if (pair.second != pipelineInfo)
            {
                continue;
            }

            ecsId = pair.first;
            break;
        }

        if (!ecsId.has_value())
        {
            throw Exceptions::KeyNotFoundException();
        }

        _namedGraphicsPipelineInfoObjects.erase(ecsId.value());
    }

    void DefaultRenderingSystem::UnregisterPipeline(Atom ecsId)
    {
        std::lock_guard guard(_graphicsPipelineMapMutex);
        auto it = _namedGraphicsPipelineInfoObjects.find(ecsId);

        if (it == _namedGraphicsPipelineInfoObjects.end())
        {
            throw Exceptions::KeyNotFoundException();
        }

        _namedGraphicsPipelineInfoObjects.erase(ecsId);
    }

    void DefaultRenderingSystem::UnregisterPipeline(const std::string& name)
    {
        std::lock_guard guard(_graphicsPipelineMapMutex);

        std::optional<Atom> ecsId;
        for (auto&& pair : _namedGraphicsPipelineInfoObjects)
        {
            if (pair.second->pipelineName != name)
            {
                continue;
            }

            ecsId = pair.first;
            break;
        }

        if (!ecsId.has_value())
        {
            throw Exceptions::KeyNotFoundException();
        }

        _namedGraphicsPipelineInfoObjects.erase(ecsId.value());
    }

    void DefaultRenderingSystem::AttachSpriteRenderingToEntity(EntityId entity,
                                                               Threading::ConcurrentSharedPtr<TextureInfo> texture,
                                                               Catalogue& catalogue)
    {
        auto [renderComponentView, transformComponentView, entityGraphComponentView] =
            catalogue.GetComponentViews<RenderComponent, TransformComponent, EntityGraphComponent>();

        auto newRenderComponent =
            RenderComponent{_defaultSpriteMeshPtr->ecsId, texture->ecsId, _defaultGraphicsPipelinePtr->ecsId};

        bool assigned = false;
        for (auto&& [primitiveInfoId, primitiveInfo] : _primitiveConfigurations)
        {
            if (primitiveInfo == newRenderComponent)
            {
                newRenderComponent.primitiveInfoId = primitiveInfoId;
                assigned = true;
                break;
            }
        }

        if (!assigned)
        {
            Atom newId = _ecsPrimitiveInfoConfigurationIdFactory.GetNext();
            GraphicsPrimitiveInfo newPrimitiveInfo{_defaultSpriteMeshPtr->ecsId, texture->ecsId,
                                                   _defaultGraphicsPipelinePtr->ecsId};
            newPrimitiveInfo.gpuTransformConstantBufferRegions[0] =
                _resourceManager.getActual().AllocateConstantBufferRegion(sizeof(Maths::GeoMatrix4x4F) * 1000);

            _primitiveConfigurations.emplace(newId, newPrimitiveInfo);
            newRenderComponent.primitiveInfoId = newId;
        }

        renderComponentView.AddComponent(entity, newRenderComponent);

        if (!transformComponentView.HasComponent(entity))
        {
            transformComponentView.AddComponent(entity);
        }

        if (!entityGraphComponentView.HasComponent(entity))
        {
            entityGraphComponentView.AddComponent(entity);
        }
    }

    EntityId DefaultRenderingSystem::CreateSpriteEntity(Threading::ConcurrentSharedPtr<TextureInfo> texture,
                                                        Catalogue& catalogue)
    {
        EntityId entity = catalogue.CreateEntity();
        AttachSpriteRenderingToEntity(entity, std::move(texture), catalogue);
        return entity;
    }

    EntityId DefaultRenderingSystem::CreateSpriteEntityOutsideOfSystem(
        Threading::ConcurrentSharedPtr<TextureInfo> texture,
        SystemScheduler& scheduler)
    {
        static AtomFactory& _entityIdFactory = AtomFactoryDatabase::GetFactory("EntityId");

        EntityId entity = _entityIdFactory.GetNext();

        auto newRenderComponent =
            RenderComponent{_defaultSpriteMeshPtr->ecsId, texture->ecsId, _defaultGraphicsPipelinePtr->ecsId};

        bool assigned = false;
        for (auto&& [primitiveInfoId, primitiveInfo] : _primitiveConfigurations)
        {
            if (primitiveInfo == newRenderComponent)
            {
                newRenderComponent.primitiveInfoId = primitiveInfoId;
                assigned = true;
                break;
            }
        }

        if (!assigned)
        {
            Atom newId = _ecsPrimitiveInfoConfigurationIdFactory.GetNext();
            GraphicsPrimitiveInfo newPrimitiveInfo{_defaultSpriteMeshPtr->ecsId, texture->ecsId,
                                                   _defaultGraphicsPipelinePtr->ecsId};
            newPrimitiveInfo.gpuTransformConstantBufferRegions[0] =
                _resourceManager.getActual().AllocateConstantBufferRegion(sizeof(Maths::GeoMatrix4x4F) * 1000);

            _primitiveConfigurations.emplace(newId, newPrimitiveInfo);
            newRenderComponent.primitiveInfoId = newId;
        }

        scheduler.GetComponentCache().GetComponentBuffer<RenderComponent>().PushComponentUpdateInstruction(
            0, entity, newRenderComponent);

        scheduler.GetComponentCache().GetComponentBuffer<TransformComponent>().PushComponentUpdateInstruction(
            0, entity, TransformComponent{});

        scheduler.GetComponentCache().GetComponentBuffer<EntityGraphComponent>().PushComponentUpdateInstruction(
            0, entity, EntityGraphComponent{});

        scheduler.GetComponentCache().PrepAllBuffersForNextFrame(std::vector<EntityId>{});
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
