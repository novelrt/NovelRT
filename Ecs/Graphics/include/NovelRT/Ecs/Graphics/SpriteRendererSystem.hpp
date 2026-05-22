#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Graphics/Components/BuiltCommandList.hpp>
#include <NovelRT/Ecs/Graphics/Components/Camera.hpp>
#include <NovelRT/Ecs/Graphics/Components/RenderPass.hpp>
#include <NovelRT/Ecs/Graphics/Components/Sprite.hpp>
#include <NovelRT/Ecs/Graphics/Components/TrackedSemaphore.hpp>
#include <NovelRT/Ecs/Graphics/Components/Viewport.hpp>

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/Components/TransformComponent.hpp>
#include <NovelRT/Ecs/EntityGraphView.hpp>
#include <NovelRT/Ecs/IEcsSystem.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>

#include <NovelRT/Graphics/GraphicsBuffer.hpp>
#include <NovelRT/Graphics/GraphicsCmdList.hpp>
#include <NovelRT/Graphics/GraphicsContext.hpp>
#include <NovelRT/Graphics/GraphicsDevice.hpp>
#include <NovelRT/Graphics/GraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInput.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInputElement.hpp>
#include <NovelRT/Graphics/GraphicsPipelineResource.hpp>
#include <NovelRT/Graphics/GraphicsPipelineResourceKind.hpp>
#include <NovelRT/Graphics/GraphicsResourceMemoryRegion.hpp>
#include <NovelRT/Graphics/GraphicsSemaphore.hpp>

#include <NovelRT/Graphics/NullGraphicsBackend.hpp>

#include <NovelRT/Maths/GeoMatrix4x4F.hpp>
#include <NovelRT/Maths/GeoVector3F.hpp>

#include <NovelRT/ResourceManagement/Desktop/DesktopResourceLoader.hpp>

#include <NovelRT/Utilities/Memory.hpp>

#include <optional>
#include <span>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace NovelRT::Ecs::Graphics
{
    template<typename TGraphicsBackend>
    class SpriteRendererSystem : public NovelRT::Ecs::IEcsSystem
    {
    public:
        struct SpritePass
        {
            std::shared_ptr<NovelRT::Graphics::GraphicsRenderPass<TGraphicsBackend>> RenderPass;
            Components::RenderPassId RenderPassId;
        };

    private:
        struct SpritePushConstant
        {
            Maths::GeoMatrix4x4F model;
            Maths::GeoVector4F tintColour;
        };

        struct CameraConstantBuffer
        {
            Maths::GeoMatrix4x4F view;
            Maths::GeoMatrix4x4F projection;
        };

        struct SpriteVertexShaderInputs
        {
            Maths::GeoVector3F Position;
            Maths::GeoVector2F UV;
        };

        struct PendingStagingBuffer
        {
            uint64_t uploadIndex;
            std::shared_ptr<NovelRT::Graphics::GraphicsBuffer<TGraphicsBackend>> stagingBuffer;
            std::shared_ptr<NovelRT::Graphics::GraphicsContext<TGraphicsBackend>> uploadContext;
            std::shared_ptr<NovelRT::Graphics::GraphicsCmdList<TGraphicsBackend>> uploadCmdList;
        };

        struct PendingGraphicsContext
        {
            uint64_t frameIndex;
            std::shared_ptr<NovelRT::Graphics::GraphicsContext<TGraphicsBackend>> context;
        };

        struct CameraData
        {
            EntityId entityId;
            Components::Camera camera;
            Components::Viewport viewport;
            NovelRT::Ecs::Components::TransformComponent transform;
        };

        using TextureRegion = std::shared_ptr<
            NovelRT::Graphics::GraphicsResourceMemoryRegion<NovelRT::Graphics::GraphicsTexture, TGraphicsBackend>>;

        using BufferRegion = std::shared_ptr<
            NovelRT::Graphics::GraphicsResourceMemoryRegion<NovelRT::Graphics::GraphicsBuffer, TGraphicsBackend>>;

        struct TextureCacheItem
        {
            TextureRegion textureRegion;
            Maths::GeoVector2F textureSize;
        };

        std::shared_ptr<ResourceManagement::Desktop::DesktopResourceLoader> _resourceLoader;
        std::shared_ptr<NovelRT::Graphics::GraphicsDevice<TGraphicsBackend>> _graphicsDevice;
        std::shared_ptr<NovelRT::Graphics::GraphicsMemoryAllocator<TGraphicsBackend>> _memoryAllocator;

        std::shared_ptr<NovelRT::Graphics::GraphicsBuffer<TGraphicsBackend>> _vertexBuffer;
        BufferRegion _vertexBufferRegion;
        std::shared_ptr<NovelRT::Graphics::GraphicsPipeline<TGraphicsBackend>> _pipeline;

        SpritePass _renderPass;

        std::shared_ptr<NovelRT::Graphics::GraphicsSurfaceContext<TGraphicsBackend>> _surfaceContext;

        std::unordered_map<uuids::uuid, TextureCacheItem> _textureCache;
        std::unordered_set<uuids::uuid> _pendingLoads;

        std::shared_ptr<NovelRT::Graphics::GraphicsSemaphore<TGraphicsBackend>> _uploadSemaphore;
        uint64_t _submittedUploads{0};
        std::vector<PendingStagingBuffer> _pendingStagingBuffers;

        std::vector<PendingGraphicsContext> _pendingContexts;

        uint64_t _frameCounter{0};
        std::shared_ptr<NovelRT::Graphics::GraphicsSemaphore<TGraphicsBackend>> _orchestratorSubmissionSemaphore;
        std::optional<EntityId> _orchestratorSubmissionSemaphoreEntity;

        std::unordered_map<EntityId, BufferRegion> _cameraConstantBuffers;

        void HandleNewSpriteTextures(Catalogue catalogue)
        {
            auto lastCompletedUpload = _uploadSemaphore->GetValue();
            if (lastCompletedUpload > 0)
            {
                lastCompletedUpload -= 1;
            }

            _pendingStagingBuffers.erase(std::remove_if(_pendingStagingBuffers.begin(), _pendingStagingBuffers.end(),
                                                        [lastCompletedUpload](const auto& pending)
                                                        { return pending.uploadIndex <= lastCompletedUpload; }),
                                         _pendingStagingBuffers.end());

            auto spriteView = catalogue.GetComponentView<Components::Sprite>();

            for (auto [entityId, sprite] : spriteView)
            {
                if (_textureCache.find(sprite.assetId) != _textureCache.end() ||
                    _pendingLoads.find(sprite.assetId) != _pendingLoads.end())
                {
                    continue;
                }

                _pendingLoads.insert(sprite.assetId);

                catalogue.ScheduleWithCompletion(
                    [this, assetId = sprite.assetId]() { return _resourceLoader->LoadTexture(assetId); },
                    [this, assetId = sprite.assetId](Timing::Timestamp /*delta*/, Catalogue completionCatalogue,
                                                     ResourceManagement::TextureMetadata textureMetadata)
                    {
                        NovelRT::Graphics::GraphicsBufferCreateInfo bufferCreateInfo{
                            .cpuAccessKind = NovelRT::Graphics::GraphicsResourceAccess::Write,
                            .gpuAccessKind = NovelRT::Graphics::GraphicsResourceAccess::Read,
                            .size = (static_cast<size_t>(textureMetadata.width) * textureMetadata.height * 4) * 2};

                        auto textureStagingBuffer = _memoryAllocator->CreateBuffer(bufferCreateInfo);
                        auto texture2D = _memoryAllocator->CreateTexture2DRepeatGpuWriteOnly(textureMetadata.width,
                                                                                             textureMetadata.height);
                        auto texture2DRegion = texture2D->Allocate(texture2D->GetSize(), 4);
                        auto textureStagingBufferRegion = textureStagingBuffer->Allocate(texture2D->GetSize(), 4);

                        auto pTextureData = textureStagingBuffer->template Map<uint8_t>(textureStagingBufferRegion);

                        NovelRT::Utilities::Memory::Copy(std::span<const uint8_t>(textureMetadata.data), pTextureData);

                        textureStagingBuffer->UnmapAndWrite(textureStagingBufferRegion);

                        auto gfxContext = _graphicsDevice->CreateGraphicsContext();
                        auto uploadCmdList = gfxContext->CreateCmdList();
                        uploadCmdList->Begin();
                        uploadCmdList->CmdBeginTexturePipelineBarrierLegacyVersion(texture2D);
                        uploadCmdList->CmdCopy(texture2D, textureStagingBufferRegion);
                        uploadCmdList->CmdEndTexturePipelineBarrierLegacyVersion(texture2D);
                        uploadCmdList->End();

                        std::vector<std::shared_ptr<NovelRT::Graphics::GraphicsCmdList<TGraphicsBackend>>> lists{
                            uploadCmdList};

                        std::vector<std::pair<std::shared_ptr<NovelRT::Graphics::GraphicsSemaphore<TGraphicsBackend>>,
                                              uint64_t>>
                            signalSemaphores{std::make_pair(_uploadSemaphore, ++_submittedUploads)};

                        _graphicsDevice->QueueSubmit(lists, signalSemaphores);

                        Components::TrackedSemaphore<TGraphicsBackend> newUploadTracker{
                            .semaphore = new std::shared_ptr<NovelRT::Graphics::GraphicsSemaphore<TGraphicsBackend>>(
                                _uploadSemaphore),
                            .signalValue = _submittedUploads};

                        auto id = completionCatalogue.CreateEntity();

                        completionCatalogue.GetComponentView<Components::TrackedSemaphore<TGraphicsBackend>>()
                            .AddComponent(id, newUploadTracker);

                        _pendingStagingBuffers.push_back(
                            {_submittedUploads, textureStagingBuffer, gfxContext, uploadCmdList});
                        _textureCache.emplace(
                            assetId, TextureCacheItem{texture2DRegion,
                                                      Maths::GeoVector2F(static_cast<float>(textureMetadata.width),
                                                                         static_cast<float>(textureMetadata.height))});
                        _pendingLoads.erase(assetId);
                    });
            }
        }

        void SubmitToOrchestrator(Catalogue& catalogue)
        {
            auto lastSubmittedFrame = _orchestratorSubmissionSemaphore->GetValue();

            if (lastSubmittedFrame > 0)
            {
                lastSubmittedFrame -= 1;
            }

            _pendingContexts.erase(std::remove_if(_pendingContexts.begin(), _pendingContexts.end(),
                                                  [lastSubmittedFrame](const auto& pending)
                                                  { return pending.frameIndex <= lastSubmittedFrame; }),
                                   _pendingContexts.end());

            auto [renderPassView, cmdListView, spriteView, transformView, trackedSemaphoresView, cameraView,
                  viewportView] =
                catalogue.GetComponentViews<
                    Components::RenderPass<TGraphicsBackend>, Components::BuiltCommandList<TGraphicsBackend>,
                    Components::Sprite, NovelRT::Ecs::Components::TransformComponent,
                    Components::TrackedSemaphore<TGraphicsBackend>, Components::Camera, Components::Viewport>();

            std::vector<CameraData> worldSpaceCameras{};

            for (auto [cameraEntityId, camera] : cameraView)
            {
                if (camera.isScreenSpace)
                {
                    continue;
                }

                Components::Viewport viewport = viewportView.GetComponent(cameraEntityId);

                NovelRT::Ecs::Components::TransformComponent cameraTransform =
                    transformView.GetComponent(cameraEntityId);

                worldSpaceCameras.push_back({cameraEntityId, camera, viewport, cameraTransform});

                if (_cameraConstantBuffers.find(cameraEntityId) == _cameraConstantBuffers.end())
                {
                    NovelRT::Graphics::GraphicsBufferCreateInfo bufferCreateInfo
                    {
                        .bufferKind = NovelRT::Graphics::GraphicsBufferKind::Constant,
                        .cpuAccessKind = NovelRT::Graphics::GraphicsResourceAccess::Write,
                        .gpuAccessKind = NovelRT::Graphics::GraphicsResourceAccess::Read,
                        .size = sizeof(CameraConstantBuffer)
                    };

                    auto constantBuffer = _memoryAllocator->CreateBuffer(bufferCreateInfo);
                    auto constantBufferRegion = constantBuffer->Allocate(sizeof(CameraConstantBuffer), 16);
                    _cameraConstantBuffers[cameraEntityId] = constantBufferRegion;
                }
            }

            if (worldSpaceCameras.empty())
            {
                return; // Not the sprite renderer's job to manage the window or surface
            }

            auto context = _graphicsDevice->CreateGraphicsContext();

            if (!_orchestratorSubmissionSemaphoreEntity.has_value())
            {
                _orchestratorSubmissionSemaphoreEntity = catalogue.CreateEntity();
            }

            Components::TrackedSemaphore<TGraphicsBackend> signalSemaComponent{};
            signalSemaComponent.isWaitSemaphore = false;
            signalSemaComponent.semaphore = new std::shared_ptr<NovelRT::Graphics::GraphicsSemaphore<TGraphicsBackend>>(
                _orchestratorSubmissionSemaphore);
            signalSemaComponent.signalValue = ++_frameCounter;

            trackedSemaphoresView.AddComponent(_orchestratorSubmissionSemaphoreEntity.value(), signalSemaComponent);

            _pendingContexts.emplace_back(_frameCounter, context);

            for (auto [entityId, sprite] : spriteView)
            {
                auto textureCacheIterator = _textureCache.find(sprite.assetId);

                if (textureCacheIterator == _textureCache.end())
                {
                    continue;
                }

                auto& texture = (*textureCacheIterator).second;

                NovelRT::Ecs::Components::TransformComponent transform = transformView.GetComponent(entityId);

                auto currentCmdList =
                    context->CreateCmdList(std::optional<NovelRT::Graphics::SecondaryCmdListInfo<TGraphicsBackend>>(
                        {_renderPass.RenderPass, 0}));

                currentCmdList->Begin();
                currentCmdList->CmdBindPipeline(_pipeline);

                std::array<
                    std::reference_wrapper<const std::shared_ptr<NovelRT::Graphics::GraphicsBuffer<TGraphicsBackend>>>,
                    1>
                    buffers{std::cref(_vertexBuffer)};
                std::array<size_t, 1> offsets{_vertexBufferRegion->GetOffset()};
                currentCmdList->CmdBindVertexBuffers(0, 1, buffers, offsets);

                auto* descriptorSetArray = new std::shared_ptr<
                    NovelRT::Graphics::GraphicsDescriptorSet<TGraphicsBackend>>[worldSpaceCameras.size()];
                size_t descriptorSetIndex = 0;

                for (auto& cameraData : worldSpaceCameras)
                {

                    auto finalScale = Maths::GeoVector2F(
                        (texture.textureSize.x / static_cast<float>(cameraData.camera.referenceResolutionWidth)) *
                            transform.scale.x,
                        (texture.textureSize.y / static_cast<float>(cameraData.camera.referenceResolutionHeight)) *
                            transform.scale.y);

                    auto model = Maths::GeoMatrix4x4F::GetDefaultIdentity();
                    model.Translate(Maths::GeoVector3F(transform.position.x, transform.position.y, 0.0f));
                    model.Rotate(transform.rotationInRadians);
                    model.Scale(finalScale);

                    SpritePushConstant pushConstant{
                        .model = model,
                        .tintColour = Maths::GeoVector4F(sprite.tint.getRScalar(), sprite.tint.getGScalar(),
                                                         sprite.tint.getBScalar(), sprite.tint.getAScalar())};

                    currentCmdList->CmdPushConstants(
                        _pipeline->GetSignature(), NovelRT::Graphics::ShaderProgramVisibility::All, 0,
                        NovelRT::Utilities::Span<uint8_t>(reinterpret_cast<uint8_t*>(&pushConstant),
                                                          sizeof(SpritePushConstant)));

                    NovelRT::Graphics::ViewportInfo viewportInfoStruct{.x = cameraData.viewport.x,
                                                                       .y = cameraData.viewport.y +
                                                                            cameraData.viewport.height,
                                                                       .width = cameraData.viewport.width,
                                                                       .height = -(cameraData.viewport.height),
                                                                       .minDepth = 0.0f,
                                                                       .maxDepth = 1.0f};

                    currentCmdList->CmdSetViewport(viewportInfoStruct);
                    currentCmdList->CmdSetScissor(
                        Maths::GeoVector2F(cameraData.viewport.x, cameraData.viewport.y),
                        Maths::GeoVector2F(cameraData.viewport.width, cameraData.viewport.height));

                    auto view = Maths::GeoMatrix4x4F::CreateFromLookAt(
                        Maths::GeoVector3F(cameraData.transform.position.x, cameraData.transform.position.y, -1.0f),
                        Maths::GeoVector3F(cameraData.transform.position.x, cameraData.transform.position.y, 0.0f),
                        Maths::GeoVector3F(0.0f, -1.0f, 0.0f));

                    auto projection = Maths::GeoMatrix4x4F::CreateOrthographic(
                        cameraData.camera.left, cameraData.camera.right, cameraData.camera.bottom,
                        cameraData.camera.top, cameraData.camera.nearPlane, cameraData.camera.farPlane);

                    auto& constantBufferRegion = _cameraConstantBuffers.at(cameraData.entityId);
                    auto pCameraData = constantBufferRegion->GetOwningResource()->template Map<CameraConstantBuffer>(
                        constantBufferRegion);
                    pCameraData[0].view = view;
                    pCameraData[0].projection = projection;
                    constantBufferRegion->GetOwningResource()->UnmapAndWrite(constantBufferRegion);

                    std::vector<std::shared_ptr<NovelRT::Graphics::GraphicsResourceMemoryRegion<
                        NovelRT::Graphics::GraphicsResource, TGraphicsBackend>>>
                        inputRegions{texture.textureRegion, constantBufferRegion};

                    auto descriptorSet = _pipeline->CreateDescriptorSet();
                    descriptorSet->AddMemoryRegionsToInputs(inputRegions);
                    descriptorSet->UpdateDescriptorSetData();

                    descriptorSetArray[descriptorSetIndex] = descriptorSet;

                    std::array<std::reference_wrapper<
                                   const std::shared_ptr<NovelRT::Graphics::GraphicsDescriptorSet<TGraphicsBackend>>>,
                               1>
                        descriptorData{std::cref(descriptorSetArray[descriptorSetIndex])};

                    currentCmdList->CmdBindDescriptorSets(descriptorData);

                    descriptorSetIndex++;

                    currentCmdList->CmdDraw(6, 1, 0, 0);
                }

                currentCmdList->End();

                Components::RenderPass<TGraphicsBackend> passComponent{.renderPassIndex = _renderPass.RenderPassId,
                                                                       .descriptorSets = descriptorSetArray,
                                                                       .descriptorSetCount = worldSpaceCameras.size()};

                Components::BuiltCommandList<TGraphicsBackend> cmdListComp{
                    .commandList =
                        new std::shared_ptr<NovelRT::Graphics::GraphicsCmdList<TGraphicsBackend>>(currentCmdList)};

                renderPassView.AddComponent(entityId, passComponent);
                cmdListView.AddComponent(entityId, cmdListComp);
            }
        }

    public:
        SpriteRendererSystem(
            std::shared_ptr<NovelRT::Graphics::GraphicsDevice<TGraphicsBackend>> device,
            SpritePass renderPass,
            std::shared_ptr<ResourceManagement::Desktop::DesktopResourceLoader> resourceLoader,
            std::shared_ptr<NovelRT::Graphics::GraphicsMemoryAllocator<TGraphicsBackend>> memoryAllocator,
            std::shared_ptr<NovelRT::Graphics::GraphicsSurfaceContext<TGraphicsBackend>> surfaceContext)
            : _resourceLoader(std::move(resourceLoader)),
              _graphicsDevice(std::move(device)),
              _memoryAllocator(std::move(memoryAllocator)),
              _renderPass(std::move(renderPass)),
              _surfaceContext(std::move(surfaceContext)),
              _uploadSemaphore(_graphicsDevice->CreateSemaphore(0)),
              _orchestratorSubmissionSemaphore(_graphicsDevice->CreateSemaphore(0))
        {
            NovelRT::Graphics::GraphicsBufferCreateInfo bufferCreateInfo{
                .cpuAccessKind = NovelRT::Graphics::GraphicsResourceAccess::Write,
                .gpuAccessKind = NovelRT::Graphics::GraphicsResourceAccess::Read,
                .size = 64 * 1024};

            auto stagingBuffer = _memoryAllocator->CreateBuffer(bufferCreateInfo);

            bufferCreateInfo.bufferKind = NovelRT::Graphics::GraphicsBufferKind::Vertex;
            bufferCreateInfo.cpuAccessKind = NovelRT::Graphics::GraphicsResourceAccess::None;
            bufferCreateInfo.gpuAccessKind = NovelRT::Graphics::GraphicsResourceAccess::Write;

            _vertexBuffer = _memoryAllocator->CreateBuffer(bufferCreateInfo);
            _vertexBufferRegion = _vertexBuffer->Allocate(sizeof(SpriteVertexShaderInputs) * 6, 16);
            auto stagingRegion = stagingBuffer->Allocate(sizeof(SpriteVertexShaderInputs) * 6, 16);

            auto pVertexBuffer = stagingBuffer->template Map<SpriteVertexShaderInputs>(stagingRegion);

            pVertexBuffer[0] =
                SpriteVertexShaderInputs{Maths::GeoVector3F(-0.5f, 0.5f, 0.0f), Maths::GeoVector2F(0.0f, 0.0f)};
            pVertexBuffer[1] =
                SpriteVertexShaderInputs{Maths::GeoVector3F(0.5f, 0.5f, 0.0f), Maths::GeoVector2F(1.0f, 0.0f)};
            pVertexBuffer[2] =
                SpriteVertexShaderInputs{Maths::GeoVector3F(-0.5f, -0.5f, 0.0f), Maths::GeoVector2F(0.0f, 1.0f)};
            pVertexBuffer[3] =
                SpriteVertexShaderInputs{Maths::GeoVector3F(-0.5f, -0.5f, 0.0f), Maths::GeoVector2F(0.0f, 1.0f)};
            pVertexBuffer[4] =
                SpriteVertexShaderInputs{Maths::GeoVector3F(0.5f, 0.5f, 0.0f), Maths::GeoVector2F(1.0f, 0.0f)};
            pVertexBuffer[5] =
                SpriteVertexShaderInputs{Maths::GeoVector3F(0.5f, -0.5f, 0.0f), Maths::GeoVector2F(1.0f, 1.0f)};

            stagingBuffer->UnmapAndWrite(stagingRegion);

            auto vertShaderData = _resourceLoader->LoadShaderSource("SpriteVertex.spv");
            auto pixelShaderData = _resourceLoader->LoadShaderSource("SpritePixel.spv");

            std::vector<NovelRT::Graphics::GraphicsPipelineInputElement> elements{
                NovelRT::Graphics::GraphicsPipelineInputElement(
                    typeid(Maths::GeoVector3F), NovelRT::Graphics::GraphicsPipelineInputElementKind::Position, 12),
                NovelRT::Graphics::GraphicsPipelineInputElement(
                    typeid(Maths::GeoVector2F), NovelRT::Graphics::GraphicsPipelineInputElementKind::TextureCoordinate,
                    8)};

            std::vector<NovelRT::Graphics::GraphicsPipelineInput> inputs{
                NovelRT::Graphics::GraphicsPipelineInput(elements)};

            std::vector<NovelRT::Graphics::GraphicsPipelineResource> resources{
                NovelRT::Graphics::GraphicsPipelineResource(NovelRT::Graphics::GraphicsPipelineResourceKind::Texture,
                                                            NovelRT::Graphics::ShaderProgramVisibility::Pixel),
                NovelRT::Graphics::GraphicsPipelineResource(
                    NovelRT::Graphics::GraphicsPipelineResourceKind::ConstantBuffer,
                    NovelRT::Graphics::ShaderProgramVisibility::Vertex)};

            std::vector<NovelRT::Graphics::GraphicsPushConstantRange> pushConstantRanges{
                NovelRT::Graphics::GraphicsPushConstantRange{NovelRT::Graphics::ShaderProgramVisibility::All, 0,
                                                             sizeof(SpritePushConstant)}};

            auto signature = _graphicsDevice->CreatePipelineSignature(
                NovelRT::Graphics::GraphicsPipelineBlendFactor::SrcAlpha,
                NovelRT::Graphics::GraphicsPipelineBlendFactor::OneMinusSrcAlpha, inputs, resources,
                NovelRT::Utilities::Span<NovelRT::Graphics::GraphicsPushConstantRange>(pushConstantRanges));

            auto vertShaderProg = _graphicsDevice->CreateShaderProgram(
                "main", NovelRT::Graphics::ShaderProgramKind::Vertex, vertShaderData.shaderCode);
            auto pixelShaderProg = _graphicsDevice->CreateShaderProgram(
                "main", NovelRT::Graphics::ShaderProgramKind::Pixel, pixelShaderData.shaderCode);

            _pipeline =
                _graphicsDevice->CreatePipeline(signature, vertShaderProg, pixelShaderProg, _renderPass.RenderPass);

            auto gfxContext = _graphicsDevice->CreateGraphicsContext();
            auto cmdList = gfxContext->CreateCmdList();
            cmdList->Begin();
            cmdList->CmdCopy(_vertexBufferRegion, stagingRegion);
            cmdList->End();

            std::vector<std::shared_ptr<NovelRT::Graphics::GraphicsCmdList<TGraphicsBackend>>> lists{cmdList};

            _graphicsDevice->QueueSubmit(lists);
            _graphicsDevice->WaitForIdle();
        }

        void Update(Timing::Timestamp /*delta*/, Catalogue catalogue)
        {
            HandleNewSpriteTextures(catalogue);
            SubmitToOrchestrator(catalogue);
        }
    };
}