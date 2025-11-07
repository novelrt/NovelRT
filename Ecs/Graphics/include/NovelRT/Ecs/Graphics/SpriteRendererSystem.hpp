#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Graphics/Components/BuiltCommandList.hpp>
#include <NovelRT/Ecs/Graphics/Components/RenderPass.hpp>
#include <NovelRT/Ecs/Graphics/Components/Sprite.hpp>

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/EntityGraphView.hpp>
#include <NovelRT/Ecs/IEcsSystem.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>

#include <NovelRT/Graphics/GraphicsDevice.hpp>
#include <NovelRT/Graphics/GraphicsContext.hpp>
#include <NovelRT/Graphics/GraphicsCmdList.hpp>
#include <NovelRT/Graphics/GraphicsBuffer.hpp>
#include <NovelRT/Graphics/GraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/GraphicsResourceMemoryRegion.hpp>

#include <NovelRT/Graphics/NullGraphicsBackend.hpp> // God is dead and so are my preferred editors - Matt J.

#include <NovelRT/Maths/GeoVector3F.hpp>

namespace NovelRT::Ecs::Graphics
{
    template<typename TGraphicsBackend>
    class SpriteRendererSystem : public NovelRT::Ecs::IEcsSystem
    {
    private:
        std::shared_ptr<NovelRT::Graphics::GraphicsDevice<TGraphicsBackend>> _graphicsDevice;
        std::shared_ptr<NovelRT::Graphics::GraphicsMemoryAllocator<TGraphicsBackend>> _memoryAllocator;
        std::shared_ptr<NovelRT::Graphics::GraphicsBuffer<TGraphicsBackend>> _vertexBuffer;
        std::shared_ptr<NovelRT::Graphics::GraphicsBuffer<TGraphicsBackend>> _indexBuffer;
        std::shared_ptr<NovelRT::Graphics::GraphicsResourceMemoryRegion<NovelRT::Graphics::GraphicsBuffer, TGraphicsBackend>>
            _vertexRegion;
        std::shared_ptr<NovelRT::Graphics::GraphicsResourceMemoryRegion<NovelRT::Graphics::GraphicsBuffer, TGraphicsBackend>>
            _indexRegion;

        struct TexturedVertex
        {
            NovelRT::Maths::GeoVector3F Position;
            NovelRT::Maths::GeoVector2F UV;
        };

    public:
        SpriteRendererSystem(
            std::shared_ptr<NovelRT::Graphics::GraphicsDevice<TGraphicsBackend>> graphicsDevice, std::shared_ptr<NovelRT::Graphics::GraphicsMemoryAllocator<TGraphicsBackend>> memoryAllocator)
            : _graphicsDevice(std::move(graphicsDevice)),
              _memoryAllocator(std::move(memoryAllocator)),
              _vertexBuffer(nullptr),
              _indexBuffer(nullptr),
              _vertexRegion(nullptr),
              _indexRegion(nullptr)
        {
            NovelRT::Graphics::GraphicsBufferCreateInfo stagingCreateInfo{};
            stagingCreateInfo.cpuAccessKind = NovelRT::Graphics::GraphicsResourceAccess::Write;
            stagingCreateInfo.gpuAccessKind = NovelRT::Graphics::GraphicsResourceAccess::Read;
            stagingCreateInfo.size = 64 * 1024;

            auto stagingBuffer = _memoryAllocator->CreateBuffer(stagingCreateInfo);

            NovelRT::Graphics::GraphicsBufferCreateInfo vertexReadOnlyCreateInfo{};
            vertexReadOnlyCreateInfo.bufferKind = NovelRT::Graphics::GraphicsBufferKind::Vertex;
            vertexReadOnlyCreateInfo.cpuAccessKind = NovelRT::Graphics::GraphicsResourceAccess::None;
            vertexReadOnlyCreateInfo.gpuAccessKind = NovelRT::Graphics::GraphicsResourceAccess::Write;
            vertexReadOnlyCreateInfo.size = 64 * 1024;

            _vertexBuffer = _memoryAllocator->CreateBuffer(vertexReadOnlyCreateInfo);

            NovelRT::Graphics::GraphicsBufferCreateInfo indexReadOnlyCreateInfo{};
            vertexReadOnlyCreateInfo.bufferKind = NovelRT::Graphics::GraphicsBufferKind::Index;
            vertexReadOnlyCreateInfo.cpuAccessKind = NovelRT::Graphics::GraphicsResourceAccess::None;
            vertexReadOnlyCreateInfo.gpuAccessKind = NovelRT::Graphics::GraphicsResourceAccess::Write;
            vertexReadOnlyCreateInfo.size = 64 * 1024;

            _indexBuffer = _memoryAllocator->CreateBuffer(indexReadOnlyCreateInfo);

            _vertexRegion = _vertexBuffer->Allocate(sizeof(TexturedVertex) * 4, 16);
            auto vertexStagingRegion = stagingBuffer->Allocate(sizeof(TexturedVertex) * 4, 16);
            _indexRegion = _indexBuffer->Allocate(sizeof(uint16_t) * 6, 16);
            auto indexStagingRegion = stagingBuffer->Allocate(sizeof(uint16_t) * 6, 16);

            auto pVertexRegion = stagingBuffer->template Map<TexturedVertex>(_vertexRegion);

            pVertexRegion[0] = TexturedVertex{NovelRT::Maths::GeoVector3F(-1, 1, 0), NovelRT::Maths::GeoVector2F(0.0f, 0.0f)};
            pVertexRegion[1] = TexturedVertex{NovelRT::Maths::GeoVector3F(1, 1, 0), NovelRT::Maths::GeoVector2F(1.0f, 0.0f)};
            pVertexRegion[2] = TexturedVertex{NovelRT::Maths::GeoVector3F(1, -1, 0), NovelRT::Maths::GeoVector2F(1.0f, 1.0f)};
            pVertexRegion[3] = TexturedVertex{NovelRT::Maths::GeoVector3F(-1, -1, 0), NovelRT::Maths::GeoVector2F(0.0f, 1.0f)};

            stagingBuffer->UnmapAndWrite(_vertexRegion);

            auto pIndexRegion = stagingBuffer->template Map<uint16_t>(_indexRegion);

            // Clockwise order
            pIndexRegion[0] = 0;
            pIndexRegion[1] = 1;
            pIndexRegion[2] = 2;
            pIndexRegion[3] = 0;
            pIndexRegion[4] = 2;
            pIndexRegion[5] = 3;

            stagingBuffer->UnmapAndWrite(_indexRegion);

            auto gfxContext = _graphicsDevice->CreateGraphicsContext();
            

            auto cmdList = gfxContext->CreateCmdList(true);

            cmdList->Begin();
            cmdList->CmdCopy(_vertexRegion, vertexStagingRegion);
            cmdList->CmdCopy(_indexRegion, indexStagingRegion);
            cmdList->End();

            _graphicsDevice->QueueSubmit(cmdList);
            _graphicsDevice->WaitForIdle(); 
        }


        void Update(Timing::Timestamp /*delta*/, Catalogue catalogue) override
        {
            auto [sprites, renderPasses, commandLists] = catalogue.GetComponentViews<Components::Sprite, Components::RenderPass, Components::BuiltCommandList<TGraphicsBackend>>();

            auto context = _graphicsDevice->CreateGraphicsContext();


            for (auto [entity, sprite] : sprites)
            {
                auto cmdList = context->CreateCmdList(false);

                cmdList->Begin();
                // rendering la la la
                cmdList->CmdBindPipeline(nullptr); // TODO: sort this

                
                std::array<std::reference_wrapper<const std::shared_ptr<NovelRT::Graphics::GraphicsBuffer<TGraphicsBackend>>>, 1>
                    buffers{std::cref(_vertexBuffer)};

                std::array<size_t, 1> offsets{_vertexRegion->GetOffset()};

                cmdList->CmdBindVertexBuffers(0, 1, buffers, offsets);
                cmdList->CmdBindIndexBuffer(_indexRegion, NovelRT::Graphics::IndexType::UInt16);
                //cmdList->CmdBindDescriptorSets(nullptr); // TODO: sort this
                cmdList->CmdDrawIndexed(6, 1, 0, 0, 0);
                cmdList->End();

                Components::BuiltCommandList<TGraphicsBackend> temp{new std::shared_ptr<NovelRT::Graphics::GraphicsCmdList<TGraphicsBackend>>};

                *(temp.commandList) = cmdList;
                renderPasses.AddComponent(entity, {1});
                commandLists.AddComponent(entity, temp);
            }

        }
    };
}
