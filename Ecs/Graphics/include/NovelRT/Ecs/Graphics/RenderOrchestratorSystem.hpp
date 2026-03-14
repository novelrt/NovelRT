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
#include <NovelRT/Graphics/GraphicsSurfaceContext.hpp>

#include <vulkan/vulkan.h>

#include <algorithm>
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
        std::shared_ptr<NovelRT::Graphics::GraphicsDevice<TGraphicsBackend>> _graphicsDevice;
        std::shared_ptr<NovelRT::Graphics::GraphicsSurfaceContext<TGraphicsBackend>> _surfaceContext;

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
              _renderPassManager(renderPassManager)
        {
        }

        void Update(Timing::Timestamp /* delta */, Catalogue catalogue) override
        {
            std::map<Components::RenderPassId, std::vector<EntityId>> passes{};
            std::set<EntityId> rootEntities{};
            std::vector<EntityGraphView> roots{};
            std::vector<EntityId> ordered{};
            std::vector<std::shared_ptr<NovelRT::Graphics::GraphicsRenderTarget<TGraphicsBackend>>> renderTargetCache{};
            // TODO: maybe come up with a more "standardized" way to do this?
            std::vector<std::shared_ptr<NovelRT::Graphics::GraphicsCmdList<TGraphicsBackend>>> perFrameCommandLists{};
            std::vector<std::shared_ptr<NovelRT::Graphics::GraphicsDescriptorSet<TGraphicsBackend>>>
                perFrameDescriptorSets{};

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

            auto image = _graphicsDevice->BeginFrame();
            auto surface = _surfaceContext->GetSurface();
            std::vector<VkImageView> imageViewData{image->GetVulkanImageView()};
            auto context = _graphicsDevice->CreateGraphicsContext();
            auto cmdList = context->CreateCmdList();
            context->BeginFrame();
            cmdList->Begin();

            auto sorter = [&ordered](EntityId left, EntityId right)
            {
                auto leftPos = std::distance(ordered.begin(), std::find(ordered.begin(), ordered.end(), left));
                auto rightPos = std::distance(ordered.begin(), std::find(ordered.begin(), ordered.end(), right));
                return leftPos < rightPos;
            };

            for (auto& [passId, entities] : passes)
            {
                std::sort(entities.begin(), entities.end(), sorter);

                auto pass = _renderPassManager.GetRenderPass(passId);
                auto target = std::make_shared<NovelRT::Graphics::GraphicsRenderTarget<TGraphicsBackend>>(
                    _graphicsDevice, imageViewData, pass, static_cast<uint32_t>(surface->GetWidth()),
                    static_cast<uint32_t>(surface->GetHeight()));

                NovelRT::Graphics::ClearValue colourDataStruct{};
                colourDataStruct.colour = NovelRT::Graphics::RGBAColour(0, 0, 255, 255);
                colourDataStruct.depth = 0;
                colourDataStruct.stencil = 0;

                cmdList->CmdBeginRenderPass(pass, target, std::vector<NovelRT::Graphics::ClearValue>{colourDataStruct});

                for (const auto& entity : entities)
                {
                    if (!commandLists.HasComponent(entity))
                        continue;

                    auto* subCmdListPtr = commandLists.GetComponent(entity).commandList;
                    auto subCmdList = perFrameCommandLists.emplace_back(*subCmdListPtr);
                    auto* descriptorSetPtr = renderPasses.GetComponent(entity).descriptorSet;
                    perFrameDescriptorSets.emplace_back(*descriptorSetPtr);

                    cmdList->CmdExecuteCommands(subCmdList);
                }

                cmdList->CmdEndRenderPass();

                renderTargetCache.emplace_back(target);
            }

            cmdList->End();

            context->EndFrame();
            image->QueueSubmit(cmdList);

            // TODO: should this be in ECS?
            _graphicsDevice->PresentFrame();
        }
    };
}
