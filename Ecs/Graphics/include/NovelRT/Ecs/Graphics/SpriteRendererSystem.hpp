#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Graphics/Components/BuiltCommandList.hpp>
#include <NovelRT/Ecs/Graphics/Components/RenderPass.hpp>
#include <NovelRT/Ecs/Graphics/Components/Sprite.hpp>
#include <NovelRT/Ecs/Graphics/Components/TrackedSemaphore.hpp>

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

#include <NovelRT/Graphics/NullGraphicsBackend.hpp> // God is dead and so are my preferred editors - Matt J.

#include <NovelRT/Maths/GeoMatrix4x4F.hpp>
#include <NovelRT/Maths/GeoVector3F.hpp>

#include <NovelRT/ResourceManagement/Desktop/DesktopResourceLoader.hpp>

#include <NovelRT/Utilities/Memory.hpp>

#include <span>

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
            float tintR;
            float tintG;
            float tintB;
            float tintA;
        };

        struct SpriteVertexShaderInputs
        {
            Maths::GeoVector3F Position;
            Maths::GeoVector2F UV;
        };

    private:
        struct PendingStagingBuffer
        {
            uint64_t uploadIndex;
            std::shared_ptr<NovelRT::Graphics::GraphicsBuffer<TGraphicsBackend>> stagingBuffer;
        };

        std::shared_ptr<ResourceManagement::Desktop::DesktopResourceLoader> _resourceLoader; // TODO: FUCK.
        std::shared_ptr<NovelRT::Graphics::GraphicsDevice<TGraphicsBackend>> _graphicsDevice;
        std::shared_ptr<NovelRT::Graphics::GraphicsMemoryAllocator<TGraphicsBackend>> _memoryAllocator;

        std::shared_ptr<NovelRT::Graphics::GraphicsBuffer<TGraphicsBackend>> _vertexBuffer;
        std::shared_ptr<
            NovelRT::Graphics::GraphicsResourceMemoryRegion<NovelRT::Graphics::GraphicsBuffer, TGraphicsBackend>>
            _vertexBufferRegion;
        std::shared_ptr<NovelRT::Graphics::GraphicsPipeline<TGraphicsBackend>> _pipeline;

        SpritePass _renderPass;

        std::shared_ptr<NovelRT::Graphics::GraphicsSurfaceContext<TGraphicsBackend>> _surfaceContext;

        std::unordered_map<
            uuids::uuid,
            std::shared_ptr<
                NovelRT::Graphics::GraphicsResourceMemoryRegion<NovelRT::Graphics::GraphicsTexture, TGraphicsBackend>>>
            _textureCache;
        std::unordered_set<uuids::uuid> _pendingLoads;

        std::shared_ptr<NovelRT::Graphics::GraphicsSemaphore<TGraphicsBackend>> _uploadSemaphore;
        uint64_t _submittedUploads{0};
        std::vector<PendingStagingBuffer> _pendingStagingBuffers;

        void HandleNewSpriteTextures(Catalogue catalogue)
        {
            auto lastCompletedUpload = _uploadSemaphore->GetValue();
            if (lastCompletedUpload > 0)
                lastCompletedUpload -= 1;

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
                        NovelRT::Graphics::GraphicsBufferCreateInfo bufferCreateInfo{};
                        bufferCreateInfo.cpuAccessKind = NovelRT::Graphics::GraphicsResourceAccess::Write;
                        bufferCreateInfo.gpuAccessKind = NovelRT::Graphics::GraphicsResourceAccess::Read;
                        bufferCreateInfo.size = (static_cast<size_t>(textureMetadata.width) * textureMetadata.height * 4) * 2;

                        auto textureStagingBuffer = _memoryAllocator->CreateBuffer(bufferCreateInfo);
                        auto texture2D = _memoryAllocator->CreateTexture2DRepeatGpuWriteOnly(textureMetadata.width,
                                                                                             textureMetadata.height);
                        auto texture2DRegion = texture2D->Allocate(texture2D->GetSize(), 4);
                        auto textureStagingBufferRegion = textureStagingBuffer->Allocate(texture2D->GetSize(), 4);

                        auto pTextureData = textureStagingBuffer->template Map<uint8_t>(textureStagingBufferRegion);
                        // std::memcpy(pTextureData, textureMetadata.data.data(), textureMetadata.data.size());

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

                        Components::TrackedSemaphore<TGraphicsBackend> newUploadTracker{};
                        newUploadTracker.semaphore =
                            new std::shared_ptr<NovelRT::Graphics::GraphicsSemaphore<TGraphicsBackend>>(
                                _uploadSemaphore);
                        newUploadTracker.signalValue = _submittedUploads;

                        auto id = completionCatalogue.CreateEntity();

                        completionCatalogue.GetComponentView<Components::TrackedSemaphore<TGraphicsBackend>>()
                            .AddComponent(id, newUploadTracker);

                        _pendingStagingBuffers.push_back({_submittedUploads, textureStagingBuffer});
                        _textureCache[assetId] = texture2DRegion;
                        _pendingLoads.erase(assetId);
                    });
            }
        }

        void SubmitToOrchestrator(Catalogue& catalogue)
        {
            float surfaceWidth = _surfaceContext->GetSurface()->GetWidth();
            float surfaceHeight = _surfaceContext->GetSurface()->GetHeight();

            auto [renderPassView, cmdListView, spriteView, transformView] =
                catalogue.GetComponentViews<Components::RenderPass<TGraphicsBackend>,
                                            Components::BuiltCommandList<TGraphicsBackend>, Components::Sprite,
                                            NovelRT::Ecs::Components::TransformComponent>();

            for (auto [entityId, sprite] : spriteView)
            {
                if (_textureCache.find(sprite.assetId) == _textureCache.end())
                {
                    continue;
                }

                auto& textureRegion = _textureCache.at(sprite.assetId);

                NovelRT::Ecs::Components::TransformComponent transform = transformView.GetComponent(entityId);

                auto model = Maths::GeoMatrix4x4F::GetDefaultIdentity();
                model.Translate(Maths::GeoVector3F(transform.position.x, transform.position.y, 0.0f));
                model.Rotate(transform.rotationInRadians);
                model.Scale(Maths::GeoVector2F(transform.scale.x, transform.scale.y));

                SpritePushConstant pushConstant{};
                pushConstant.model = model;
                pushConstant.tintR = sprite.tint.getRScalar();
                pushConstant.tintG = sprite.tint.getGScalar();
                pushConstant.tintB = sprite.tint.getBScalar();
                pushConstant.tintA = sprite.tint.getAScalar();

                auto context = _graphicsDevice->CreateGraphicsContext();
                auto currentCmdList =
                    context->CreateCmdList(std::optional<NovelRT::Graphics::SecondaryCmdListInfo<TGraphicsBackend>>(
                        {_renderPass.RenderPass, 0}));

                currentCmdList->Begin();

                NovelRT::Graphics::ViewportInfo viewportInfoStruct{};
                viewportInfoStruct.x = 0;
                viewportInfoStruct.y = surfaceHeight;
                viewportInfoStruct.width = surfaceWidth;
                viewportInfoStruct.height = -surfaceHeight;
                viewportInfoStruct.minDepth = 0.0f;
                viewportInfoStruct.maxDepth = 1.0f;

                currentCmdList->CmdSetViewport(viewportInfoStruct);
                currentCmdList->CmdSetScissor(Maths::GeoVector2F::Zero(),
                                              Maths::GeoVector2F(surfaceWidth, surfaceHeight));
                currentCmdList->CmdBindPipeline(_pipeline);

                std::array<
                    std::reference_wrapper<const std::shared_ptr<NovelRT::Graphics::GraphicsBuffer<TGraphicsBackend>>>,
                    1>
                    buffers{std::cref(_vertexBuffer)};
                std::array<size_t, 1> offsets{_vertexBufferRegion->GetOffset()};
                currentCmdList->CmdBindVertexBuffers(0, 1, buffers, offsets);

                std::vector<std::shared_ptr<NovelRT::Graphics::GraphicsResourceMemoryRegion<
                    NovelRT::Graphics::GraphicsResource, TGraphicsBackend>>>
                    inputRegions{textureRegion};
                auto descriptorSet = _pipeline->CreateDescriptorSet();
                descriptorSet->AddMemoryRegionsToInputs(inputRegions);
                descriptorSet->UpdateDescriptorSetData();

                std::array<std::reference_wrapper<
                               const std::shared_ptr<NovelRT::Graphics::GraphicsDescriptorSet<TGraphicsBackend>>>,
                           1>
                    descriptorData{std::cref(descriptorSet)};
                currentCmdList->CmdBindDescriptorSets(descriptorData);

                currentCmdList->CmdPushConstants(
                    _pipeline->GetSignature(), NovelRT::Graphics::ShaderProgramVisibility::All, 0,
                    NovelRT::Utilities::Span<uint8_t>(reinterpret_cast<uint8_t*>(&pushConstant),
                                                      sizeof(SpritePushConstant)));

                currentCmdList->CmdDraw(6, 1, 0, 0);

                currentCmdList->End();

                Components::RenderPass<TGraphicsBackend> passComponent{};
                passComponent.renderPassIndex = _renderPass.RenderPassId;
                passComponent.descriptorSet =
                    new std::shared_ptr<NovelRT::Graphics::GraphicsDescriptorSet<TGraphicsBackend>>(descriptorSet);

                Components::BuiltCommandList<TGraphicsBackend> cmdListComp{};
                cmdListComp.commandList =
                    new std::shared_ptr<NovelRT::Graphics::GraphicsCmdList<TGraphicsBackend>>(currentCmdList);

                if (!renderPassView.HasComponent(entityId))
                {
                    renderPassView.AddComponent(entityId, passComponent);
                    cmdListView.AddComponent(entityId, cmdListComp);
                }
                else
                {
                    renderPassView.PushComponentUpdateInstruction(entityId, passComponent);
                    cmdListView.PushComponentUpdateInstruction(entityId, cmdListComp);
                }
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
              _uploadSemaphore(_graphicsDevice->CreateSemaphore(0))
        {
            NovelRT::Graphics::GraphicsBufferCreateInfo bufferCreateInfo{};
            bufferCreateInfo.cpuAccessKind = NovelRT::Graphics::GraphicsResourceAccess::Write;
            bufferCreateInfo.gpuAccessKind = NovelRT::Graphics::GraphicsResourceAccess::Read;
            bufferCreateInfo.size = 64 * 1024;

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
                                                            NovelRT::Graphics::ShaderProgramVisibility::Pixel)};

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
