#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Graphics/Components/RenderPass.hpp>
#include <NovelRT/Ecs/Graphics/Components/BuiltCommandList.hpp>
#include <NovelRT/Ecs/Components/EntityGraphComponent.hpp>

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/EntityGraphView.hpp>
#include <NovelRT/Ecs/IEcsSystem.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>

#include <NovelRT/Graphics/GraphicsDevice.hpp>
#include<NovelRT/Ecs/Graphics/RenderPassManager.hpp>

#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <utility>

namespace NovelRT::Ecs::Graphics
{
    template <typename TGraphicsBackend>
    class RenderOrchestratorSystem : public NovelRT::Ecs::IEcsSystem
    {
    private:
        std::shared_ptr<NovelRT::Graphics::GraphicsDevice<TGraphicsBackend>> _graphicsDevice;
        RenderPassManager<TGraphicsBackend> _renderPassManager;

        EntityGraphView GetRoot(ComponentView<Ecs::Components::EntityGraphComponent>& view, Catalogue& catalogue, EntityId entity)
        {
            EntityGraphView it{catalogue, entity, view.GetComponent(entity)};

            while (it.HasParent())
            {
                it = {catalogue, it.GetRawComponentData().parent, view.GetComponent(it.GetRawComponentData().parent)};
            }

            return it;
        }

        void EnumerateChildren(EntityGraphView& graph, ComponentView<Components::RenderPass>& view, std::vector<EntityId>& inOrder)
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
        explicit RenderOrchestratorSystem(std::shared_ptr<NovelRT::Graphics::GraphicsDevice<TGraphicsBackend>> graphicsDevice, RenderPassManager<TGraphicsBackend> renderPassManager) : _graphicsDevice(std::move(graphicsDevice)), _renderPassManager(renderPassManager) {}

        void Update(Timing::Timestamp /* delta */, Catalogue catalogue) override
        {
            std::map<Components::RenderPassId, std::vector<EntityId>> passes{};
            std::set<EntityId> rootEntities{};
            std::vector<EntityGraphView> roots{};
            std::vector<EntityId> ordered{};
            // TODO: maybe come up with a more "standardized" way to do this?
            std::vector<std::shared_ptr<NovelRT::Graphics::GraphicsCmdList<TGraphicsBackend>>> perFrameCommandLists{};

            auto [renderPasses, commandLists, graph] = catalogue.GetComponentViews<Components::RenderPass, Components::BuiltCommandList<TGraphicsBackend>, Ecs::Components::EntityGraphComponent>();
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

            for (auto& root : roots)
            {
                EnumerateChildren(root, renderPasses, ordered);
            }

            auto image = _graphicsDevice->BeginFrame();
            auto context = _graphicsDevice->CreateGraphicsContext();
            auto cmdList = context->CreateCmdList(true);
            context->BeginFrame();

            auto sorter = [&ordered](EntityId left, EntityId right)
            {
                auto leftPos = std::distance(ordered.begin(), std::find(ordered.begin(), ordered.end(), left));
                auto rightPos = std::distance(ordered.begin(), std::find(ordered.begin(), ordered.end(), right));
                return leftPos < rightPos;
            };

            for (auto& [pass, entities] : passes)
            {
                std::sort(entities.begin(), entities.end(), sorter);

                auto pass = _renderPassManager.GetRenderPass(pass);
                cmdList->CmdBeginRenderPass(pass);

                for (auto& entity : entities)
                {
                    if (!commandLists.HasComponent(entity)) continue;
                    auto* subCmdListPtr = commandLists.GetComponent(entity).commandList;
                    auto subCmdList = perFrameCommandLists.emplace_back(*subCmdListPtr);
                    cmdList->CmdExecuteCommands(subCmdList);
                    renderPasses.RemoveComponent(entity);
                    commandLists.RemoveComponent(entity);
                    delete subCmdListPtr;
                }

                cmdList->CmdBeginRenderPass(pass);
            }

            context->EndFrame();
            image->QueueSubmit(cmdList);

            // TODO: should this be in ECS?
            _graphicsDevice->PresentFrame();
        }
    };
}
