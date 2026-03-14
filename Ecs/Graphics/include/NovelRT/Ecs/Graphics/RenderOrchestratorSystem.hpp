#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Components/EntityGraphComponent.hpp>
#include <NovelRT/Ecs/Graphics/Components/BuiltCommandList.hpp>
#include <NovelRT/Ecs/Graphics/Components/RenderPass.hpp>

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/EntityGraphView.hpp>
#include <NovelRT/Ecs/IEcsSystem.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>

#include <NovelRT/Ecs/Graphics/RenderPassManager.hpp>
#include <NovelRT/Graphics/GraphicsDevice.hpp>
#include <NovelRT/Graphics/GraphicsRenderTarget.hpp>
#include <NovelRT/Graphics/GraphicsSemaphore.hpp>
#include <NovelRT/Graphics/GraphicsSurfaceContext.hpp>

#include <vulkan/vulkan.h>

#include <algorithm>
#include <deque>
#include <map>
#include <set>
#include <utility>
#include <vector>

namespace NovelRT::Ecs::Graphics
{
    template<typename TGraphicsBackend>
    class RenderOrchestratorSystem : public NovelRT::Ecs::IEcsSystem
    {
    private:
        struct PerFrameResources
        {
            uint64_t frameNumber;

            std::shared_ptr<NovelRT::Graphics::GraphicsSwapchainImage<TGraphicsBackend>> _frameImage;

            std::vector<std::shared_ptr<NovelRT::Graphics::GraphicsRenderTarget<TGraphicsBackend>>> renderTargets{};
            std::vector<std::shared_ptr<NovelRT::Graphics::GraphicsCmdList<TGraphicsBackend>>> commandLists{};
        };

        std::shared_ptr<NovelRT::Graphics::GraphicsDevice<TGraphicsBackend>> _graphicsDevice;
        std::shared_ptr<NovelRT::Graphics::GraphicsSurfaceContext<TGraphicsBackend>> _surfaceContext;

        std::shared_ptr<NovelRT::Graphics::GraphicsSemaphore<TGraphicsBackend>> _deletionSemaphore;
        std::deque<PerFrameResources> _frameResources;
        uint64_t _renderedFrames{0};

        RenderPassManager<TGraphicsBackend> _renderPassManager;

        EntityGraphView GetRoot(ComponentView<Ecs::Components::EntityGraphComponent>& view,
                                Catalogue& catalogue,
                                EntityId entity)
        {
            EntityGraphView it{catalogue, entity, view.GetComponent(entity)};

            while (it.HasParent())
            {
                it = {catalogue, it.GetRawComponentData().parent, view.GetComponent(it.GetRawComponentData().parent)};
            }

            return it;
        }

        void EnumerateChildren(EntityGraphView& graph,
                               ComponentView<Components::RenderPass<TGraphicsBackend>>& view,
                               std::vector<EntityId>& inOrder)
        {
            if (view.HasComponent(graph.GetRawEntityId()))
                inOrder.push_back(graph.GetRawEntityId());

            if (!graph.HasChildren())
                return;

            for (const auto& child : graph.GetOriginalChildren())
            {
                EnumerateChildren(child.get(), view, inOrder);
            }
        }

    public:
        RenderOrchestratorSystem(std::shared_ptr<NovelRT::Graphics::GraphicsDevice<TGraphicsBackend>> graphicsDevice,
                                 std::shared_ptr<NovelRT::Graphics::GraphicsSurfaceContext<TGraphicsBackend>> context,
                                 RenderPassManager<TGraphicsBackend> renderPassManager)
            : _graphicsDevice(std::move(graphicsDevice)),
              _surfaceContext(std::move(context)),
              _deletionSemaphore(_graphicsDevice->CreateSemaphore(0)),
              _renderPassManager(renderPassManager)
        {
        }

        void Update(Timing::Timestamp /* delta */, Catalogue catalogue) override
        {
            // 1. Clean up any resources that are no longer valid.
            auto lastRenderedFrame = _deletionSemaphore->GetValue();
            if (lastRenderedFrame > 0) lastRenderedFrame -= 1; // this is important to avoid underflow

            _frameResources.erase(
                std::remove_if(_frameResources.begin(), _frameResources.end(), [lastRenderedFrame](auto& it){ return it.frameNumber < lastRenderedFrame; }),
                _frameResources.end());

            // 2. Determine the order in which we should enumerate the entities based on their render pass
            std::map<Components::RenderPassId, std::vector<EntityId>> passes{};
            std::set<EntityId> rootEntities{};
            std::vector<EntityGraphView> roots{};
            std::vector<EntityId> ordered{};

            auto [renderPasses, commandLists, graph] =
                catalogue.GetComponentViews<Components::RenderPass<TGraphicsBackend>,
                                            Components::BuiltCommandList<TGraphicsBackend>,
                                            Ecs::Components::EntityGraphComponent>();
            for (auto [entity, component] : renderPasses)
            {
                auto [iterator, inserted] = passes.try_emplace(component.renderPassIndex);
                iterator->second.emplace_back(entity);

                if (graph.HasComponent(entity))
                {
                    auto root = GetRoot(graph, catalogue, entity);
                    auto [it, insertedTwo] = rootEntities.insert(root.GetRawEntityId());
                    if (insertedTwo)
                        roots.emplace_back(std::move(root));
                }
            }

            if (passes.empty())
            {
                return;
            }

            for (auto& root : roots)
            {
                EnumerateChildren(root, renderPasses, ordered);
            }

            auto sorter = [&ordered](EntityId left, EntityId right)
            {
                auto leftPos = std::distance(ordered.begin(), std::find(ordered.begin(), ordered.end(), left));
                auto rightPos = std::distance(ordered.begin(), std::find(ordered.begin(), ordered.end(), right));
                return leftPos < rightPos;
            };


            // 3. Prepare to render a frame
            auto image = _graphicsDevice->BeginFrame();
            auto surface = _surfaceContext->GetSurface();
            auto context = _graphicsDevice->CreateGraphicsContext();
            std::vector<VkImageView> imageViewData{image->GetVulkanImageView()};
            auto cmdList = context->CreateCmdList();
            context->BeginFrame();
            cmdList->Begin();

            auto& frameResources = _frameResources.emplace_back(PerFrameResources{ ++_renderedFrames, image });

            // 4. Enumerate all render passes in order
            for (auto& [passId, entities] : passes)
            {
                // 5. Sort the entities within this pass according to their scene graph order.
                std::sort(entities.begin(), entities.end(), sorter);

                // 6. Prepare the render pass
                auto pass = _renderPassManager.GetRenderPass(passId);
                auto target = frameResources.renderTargets.emplace_back(
                    std::make_shared<NovelRT::Graphics::GraphicsRenderTarget<TGraphicsBackend>>(
                        _graphicsDevice, imageViewData, pass, static_cast<uint32_t>(surface->GetWidth()),
                        static_cast<uint32_t>(surface->GetHeight())));

                NovelRT::Graphics::ClearValue colourDataStruct{};
                colourDataStruct.colour = NovelRT::Graphics::RGBAColour(0, 0, 255, 255);
                colourDataStruct.depth = 0;
                colourDataStruct.stencil = 0;

                cmdList->CmdBeginRenderPass(pass, target, std::vector<NovelRT::Graphics::ClearValue>{colourDataStruct});

                // 7. Enumerate over the entities and dispatch their individual command lists
                for (const auto& entity : entities)
                {
                    if (!commandLists.HasComponent(entity))
                        continue;

                    auto* subCmdListPtr = commandLists.GetComponent(entity).commandList;
                    auto subCmdList = frameResources.commandLists.emplace_back(*subCmdListPtr);

                    cmdList->CmdExecuteCommands(subCmdList);
                }

                cmdList->CmdEndRenderPass();
            }

            cmdList->End();

            context->EndFrame();
            image->QueueSubmit(cmdList, { _deletionSemaphore, frameResources.frameNumber });

            frameResources.commandLists.emplace_back(cmdList);

            // TODO: should this be in ECS?
            _graphicsDevice->EndFrame();
        }
    };
}
