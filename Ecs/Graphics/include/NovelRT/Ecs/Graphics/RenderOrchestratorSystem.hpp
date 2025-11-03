#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Graphics/GraphicsComponents.hpp>
#include <NovelRT/Ecs/DefaultComponentTypes.hpp>

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/EntityGraphView.hpp>
#include <NovelRT/Ecs/IEcsSystem.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>

#include <NovelRT/Graphics/GraphicsDevice.hpp>

#include <algorithm>
#include <map>
#include <set>

namespace NovelRT::Ecs::Graphics
{
    template <typename TGraphicsBackend>
    class RenderOrchestratorSystem : public NovelRT::Ecs::IEcsSystem
    {
    private:
        std::shared_ptr<NovelRT::Graphics::GraphicsDevice<TGraphicsBackend>> _graphicsDevice;

        EntityGraphView GetRoot(ComponentView<EntityGraphComponent>& view, Catalogue& catalogue, EntityId entity)
        {
            EntityGraphView it{catalogue, entity, view.GetComponent(entity)};
            if (!it.HasParent())
            {
                return it;
            }

            return GetRoot(view, catalogue, it.GetRawComponentData().parent);
        }

        void EnumerateChildren(EntityGraphView& graph, ComponentView<RenderPass>& view, std::vector<EntityId> inOrder)
        {
            if (view.HasComponent(graph.GetRawEntityId()))
                inOrder.push_back(graph.GetRawEntityId());

            if (!graph.HasChildren())
                return;

            for (auto& child : graph.GetOriginalChildren())
            {
                EnumerateChildren(child, view, inOrder);
            }
        }

    public:
        void Update(Timing::Timestamp delta, Catalogue catalogue) override
        {
            std::map<int, std::vector<EntityId>> passes{};
            std::set<EntityGraphView> roots{};
            std::vector<EntityId> ordered{};

            auto [renderPasses, graph] = catalogue.GetComponentViews<RenderPass, EntityGraphComponent>();
            for (auto [entity, component] : renderPasses)
            {
                auto [iterator, inserted] = passes.try_emplace(component.renderPassIndex);
                iterator->second.emplace_back(entity);

                if (graph.HasComponent(entity))
                {
                    roots.insert(GetRoot(graph, catalogue, entity));
                }
            }

            for (auto& root : roots)
            {
                EnumerateChildren(root, renderPasses, ordered);
            }

            auto image = _graphicsDevice->BeginFrame();
            auto context = image->CreateOrGetContext();
            auto cmdList = context->BeginFrame();

            auto sorter = [&ordered](EntityId left, EntityId right)
            {
                auto leftPos = std::distance(ordered.begin(), std::find(ordered.begin(), ordered.end(), left));
                auto rightPos = std::distance(ordered.begin(), std::find(ordered.begin(), ordered.end(), right));
                return leftPos < rightPos;
            };

            for (auto& [pass, entities] : passes)
            {
                std::sort(entities.begin(), entities.end(), sorter);

                // cmdList->CmdBeginRenderPass(...)

                for (auto& entity : entities)
                {
                    // cmdList->CmdDispatchCmdList(...)
                }

                // cmdList->CmdBeginRenderPass()
            }

            context->EndFrame();
            image->SubmitQueuesFromContexts();

            // TODO: should this be in ECS?
            _graphicsDevice->PresentFrame();
        }
    };
}
