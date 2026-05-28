#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/UI/ImGui/ImGuiUIProvider.hpp>

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/EntityGraphView.hpp>
#include <NovelRT/Ecs/IEcsSystem.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>

namespace NovelRT::Ecs::UI
{
    template<typename TGraphicsBackend, typename TInputBackend, typename TWindowingBackend>
    class UISystem : public NovelRT::Ecs::IEcsSystem
    {
    private:
        std::shared_ptr<NovelRT::UI::ImGui::ImGuiUIProvider<TGraphicsBackend, TInputBackend, TWindowingBackend>> _uiProvider;
        bool _firstSpin = true;

        // EntityGraphView GetRoot(ComponentView<Ecs::Components::EntityGraphComponent>& view,
        //                         Catalogue& catalogue,
        //                         EntityId entity)
        // {
        //     EntityGraphView it{catalogue, entity, view.GetComponent(entity)};

        //     while (it.HasParent())
        //     {
        //         it = {catalogue, it.GetRawComponentData().parent, view.GetComponent(it.GetRawComponentData().parent)};
        //     }

        //     return it;
        // }

        // void EnumerateChildren(EntityGraphView& graph,
        //                        ComponentView<Components::RenderPass<TGraphicsBackend>>& view,
        //                        std::vector<EntityId>& inOrder)
        // {
        //     if (view.HasComponent(graph.GetRawEntityId()))
        //         inOrder.push_back(graph.GetRawEntityId());

        //     if (!graph.HasChildren())
        //         return;

        //     for (const auto& child : graph.GetOriginalChildren())
        //     {
        //         EnumerateChildren(child.get(), view, inOrder);
        //     }
        // }

    public:
        UISystem(std::shared_ptr<NovelRT::UI::ImGui::ImGuiUIProvider<TGraphicsBackend, TInputBackend, TWindowingBackend>> uiProvider)
            : _uiProvider(std::move(uiProvider))
        {
        }

        void Update(Timing::Timestamp /* delta */, Catalogue catalogue) override
        {
            unused(catalogue);
            if(_firstSpin)
            {
                _uiProvider->UploadFontData();
                _firstSpin = false;
            }
        }
    };
}
