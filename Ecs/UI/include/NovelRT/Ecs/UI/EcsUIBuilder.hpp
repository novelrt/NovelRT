#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/UI/ImGui/ImGuiUIProvider.hpp>
#include <NovelRT/Ecs/SystemSchedulerBuilder.hpp>
#include <NovelRT/Ecs/UI/UISystem.hpp>
#include <NovelRT/Ecs/UI/Components/UIWidgetContainer.hpp>
#include <NovelRT/Ecs/UI/Components/UIButton.hpp>
#include <NovelRT/Ecs/UI/Components/UISpriteButton.hpp>
#include <NovelRT/Ecs/UI/Components/UIText.hpp>
#include <NovelRT/Ecs/UI/Components/UIClickEvent.hpp>

#include <NovelRT/Utilities/Macros.hpp>

#include <limits>
#include <memory>
#include <utility>

namespace NovelRT::Ecs::UI
{
    template<typename TGraphicsBackend, typename TInputBackend, typename TWindowingBackend>
    class UISystem;

    template<typename TGraphicsBackend, typename TInputBackend, typename TWindowingBackend>
    class EcsUIBuilder
    {
    private:
        std::shared_ptr<NovelRT::UI::ImGui::ImGuiUIProvider<TGraphicsBackend, TInputBackend, TWindowingBackend>> _uiProvider;
        std::shared_ptr<NovelRT::Ecs::UI::UISystem<TGraphicsBackend, TInputBackend, TWindowingBackend>> _system;

        EcsUIBuilder(){}

        template<typename T1, typename T2, typename T3>
        friend EcsUIBuilder<T1, T2, T3>& AddUI(SystemSchedulerBuilder&);

    public:
        EcsUIBuilder(const EcsUIBuilder& other) = default;
        EcsUIBuilder& operator=(const EcsUIBuilder& other) = default;
        EcsUIBuilder(EcsUIBuilder&& other) = default;
        EcsUIBuilder& operator=(EcsUIBuilder&& other) = default;
        ~EcsUIBuilder() = default;

        EcsUIBuilder& WithUIProvider(
            std::shared_ptr<NovelRT::UI::ImGui::ImGuiUIProvider<TGraphicsBackend, TInputBackend, TWindowingBackend>>& provider)
        {
            _uiProvider = provider;
            return *this;
        }

        EcsUIBuilder& WithUISystem(
            const std::shared_ptr<NovelRT::Ecs::UI::UISystem<TGraphicsBackend, TInputBackend, TWindowingBackend>>& system)
        {
            _system = system;
            return *this;
        }

        EcsUIBuilder& WithDefaultUISystem()
        {
            return WithOrchestrator(
                std::make_shared<NovelRT::Ecs::UI::UISystem<TGraphicsBackend, TInputBackend, TWindowingBackend>>(_uiProvider));
        }

        void operator()(SystemScheduler& scheduler)
        {
            auto& cache = scheduler.GetComponentCache();

            cache.RegisterComponentType(NovelRT::Ecs::UI::Components::UIWidgetContainer{}, "NovelRT::Ecs::UI::UIWidgetContainer");
            cache.RegisterComponentType(NovelRT::Ecs::UI::Components::UIButton{}, "NovelRT::Ecs::UI::UIButton");
            cache.RegisterComponentType(NovelRT::Ecs::UI::Components::UIClickEvent, "NovelRT::Ecs::UI::UIClickEvent");
            cache.RegisterComponentType(NovelRT::Ecs::UI::Components::UIText, "NovelRT::Ecs::UI::UIText");
            
            unused(scheduler.RegisterSystemDependsOnAll(_system));
        }
    };

    template<typename TGraphicsBackend, typename TInputBackend, typename TWindowingBackend>
    EcsUIBuilder<TGraphicsBackend, TInputBackend, TWindowingBackend>& AddUI(SystemSchedulerBuilder& builder)
    {
        return builder.Configure(EcsUIBuilder<TGraphicsBackend, TInputBackend, TWindowingBackend>{});
    };
}
