#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Graphics/Components/BuiltCommandList.hpp>
#include <NovelRT/Ecs/Graphics/Components/RenderPass.hpp>

#include <NovelRT/Ecs/SystemSchedulerBuilder.hpp>

#include <limits>
#include <memory>
#include <utility>

namespace NovelRT::Ecs::Graphics
{
    template <typename TGraphicsBackend>
    class RenderOrchestratorSystem;

    template <typename TGraphicsBackend>
    class RenderPassManager;

    template <typename TGraphicsBackend>
    class EcsGraphicsBuilder
    {
    private:
        std::shared_ptr<NovelRT::Graphics::GraphicsProvider<TGraphicsBackend>> _graphicsProvider;
        std::shared_ptr<RenderOrchestratorSystem<TGraphicsBackend>> _orchestrator;

        Components::BuiltCommandList<TGraphicsBackend> _defaultBuiltCommandListComponent;
        Components::RenderPass _defaultRenderPassComponent;

        RenderPassManager<TGraphicsBackend> _passManager;

        EcsGraphicsBuilder(SystemSchedulerBuilder& builder)
            : _defaultBuiltCommandListComponent{nullptr},
            _defaultRenderPassComponent{std::numeric_limits<Components::RenderPassId>::max()}
        {
            builder.Configure([this](SystemScheduler& scheduler) {
                // TODO: add systems and components for rendering
                auto& cache = scheduler.GetComponentCache();

                cache.RegisterComponentType(_defaultBuiltCommandListComponent, "NovelRT::Ecs::Graphics::BuiltCommandList");
                cache.RegisterComponentType(_defaultRenderPassComponent, "NovelRT::Ecs::Graphics::RenderPass");

                scheduler.RegisterSystem([orchestrator = _orchestrator](auto&& delta, auto&& catalogue) {
                    orchestrator->Update(std::forward<decltype(delta)>(delta), std::forward<decltype(catalogue)>(catalogue));
                });
            });
        };

        template <typename T>
        friend EcsGraphicsBuilder<T> AddGraphics(SystemSchedulerBuilder&);

    public:
        // Intentionally disallow moving/copying
        EcsGraphicsBuilder(const EcsGraphicsBuilder& other) = delete;
        EcsGraphicsBuilder& operator=(const EcsGraphicsBuilder& other) = delete;
        EcsGraphicsBuilder(EcsGraphicsBuilder&& other) = delete;
        EcsGraphicsBuilder& operator=(EcsGraphicsBuilder&& other) = delete;
        ~EcsGraphicsBuilder() = default;

        EcsGraphicsBuilder& WithGraphicsProvider(std::shared_ptr<NovelRT::Graphics::GraphicsProvider<TGraphicsBackend>>& provider)
        {
            _graphicsProvider = provider;
            return *this;
        }

        EcsGraphicsBuilder& ConfigureRenderPasses(std::function<void(RenderPassManager<TGraphicsBackend>&)> configure)
        {
            configure(_passManager);
            return *this;
        }

        EcsGraphicsBuilder& WithDefaultBuiltCommandListComponent(
            const Components::BuiltCommandList<TGraphicsBackend>& defaultBuiltCommandListComponent)
        {
            _defaultBuiltCommandListComponent = defaultBuiltCommandListComponent;
            return *this;
        }

        EcsGraphicsBuilder& WithDefaultRenderPassComponent(
            const Components::RenderPass& defaultRenderPassComponent)
        {
            _defaultRenderPassComponent = defaultRenderPassComponent;
            return *this;
        }

        EcsGraphicsBuilder& WithOrchestrator(const std::shared_ptr<RenderOrchestratorSystem<TGraphicsBackend>>& orchestrator)
        {
            _orchestrator = orchestrator;
            return *this;
        }
    };

    template <typename TGraphicsBackend>
    EcsGraphicsBuilder<TGraphicsBackend> AddGraphics(SystemSchedulerBuilder& builder)
    {
        return EcsGraphicsBuilder<TGraphicsBackend>{builder};
    };
}
