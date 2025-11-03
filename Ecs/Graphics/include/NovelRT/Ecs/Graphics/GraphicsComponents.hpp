#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/SystemSchedulerBuilder.hpp>
#include <NovelRT/Graphics/GraphicsProvider.hpp>

#include <memory>

namespace NovelRT::Ecs::Graphics
{
    struct BuiltCommandList
    {
        void* SomeOpaqueHandleThingIGuess;
        int priority;
    };

    struct RenderPass
    {
        int renderPassIndex;
    };

    template <typename TGraphicsBackend>
    class RenderOrchestratorSystem;

    template <typename TGraphicsBackend>
    class EcsGraphicsBuilder
    {
    private:
        std::shared_ptr<NovelRT::Graphics::GraphicsProvider<TGraphicsBackend>> _graphicsProvider;
        std::shared_ptr<RenderOrchestratorSystem<TGraphicsBackend>> _orchestrator;

        BuiltCommandList _defaultBuiltCommandListComponent;
        RenderPass _defaultRenderPassComponent;

        EcsGraphicsBuilder(SystemSchedulerBuilder& builder)
            : _defaultBuiltCommandListComponent{nullptr, 0}
        {
            builder.Configure([this](SystemScheduler& scheduler) {
                // TODO: add systems and components for rendering
                auto& cache = scheduler.GetComponentCache();

                cache.RegisterComponentType(_defaultBuiltCommandListComponent, "NovelRT::Ecs::Graphics::BuiltCommandList");
                cache.RegisterComponentType(_defaultRenderPassComponent, "NovelRT::Ecs::Graphics::RenderPass");

                scheduler.RegisterSystem(_orchestrator);
            });
        };

        friend EcsGraphicsBuilder AddGraphics(SystemSchedulerBuilder&);

    public:
        EcsGraphicsBuilder& WithGraphicsProvider(std::shared_ptr<NovelRT::Graphics::GraphicsProvider<TGraphicsBackend>>& provider)
        {
            _graphicsProvider = provider;
            return *this;
        }

        EcsGraphicsBuilder& WithDefaultBuiltCommandListComponent(const BuiltCommandList& defaultBuiltCommandListComponent)
        {
            _defaultBuiltCommandListComponent = defaultBuiltCommandListComponent;
            return *this;
        }

        EcsGraphicsBuilder& WithDefaultRenderPassComponent(const RenderPass& defaultRenderPassComponent)
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
