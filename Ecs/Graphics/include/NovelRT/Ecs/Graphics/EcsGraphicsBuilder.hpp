#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Graphics/Components/BuiltCommandList.hpp>
#include <NovelRT/Ecs/Graphics/Components/Camera.hpp>
#include <NovelRT/Ecs/Graphics/Components/RenderPass.hpp>
#include <NovelRT/Ecs/Graphics/Components/Sprite.hpp>
#include <NovelRT/Ecs/Graphics/Components/TrackedSemaphore.hpp>
#include <NovelRT/Ecs/Graphics/Components/Viewport.hpp>
#include <NovelRT/Graphics/GraphicsSurfaceContext.hpp>

#include <NovelRT/Ecs/SystemSchedulerBuilder.hpp>

#include <NovelRT/Utilities/Macros.hpp>

#include <limits>
#include <memory>
#include <utility>

namespace NovelRT::Ecs::Graphics
{
    template<typename TGraphicsBackend>
    class RenderOrchestratorSystem;

    template<typename TGraphicsBackend>
    class RenderPassManager;

    template<typename TGraphicsBackend>
    class EcsGraphicsBuilder
    {
    private:
        std::shared_ptr<NovelRT::Graphics::GraphicsDevice<TGraphicsBackend>> _graphicsDevice;
        std::shared_ptr<RenderOrchestratorSystem<TGraphicsBackend>> _orchestrator;
        std::shared_ptr<NovelRT::Graphics::GraphicsSurfaceContext<TGraphicsBackend>> _context;

        Components::BuiltCommandList<TGraphicsBackend> _defaultBuiltCommandListComponent;
        Components::RenderPass<TGraphicsBackend> _defaultRenderPassComponent;
        Components::TrackedSemaphore<TGraphicsBackend> _defaultTrackedSemaphoreComponent;
        Components::Sprite _defaultSpriteComponent;
        Components::Camera _defaultCameraComponent;
        Components::Viewport _defaultViewportComponent;

        RenderPassManager<TGraphicsBackend> _passManager;

        EcsGraphicsBuilder()
            : _defaultBuiltCommandListComponent{nullptr},
              _defaultRenderPassComponent{std::numeric_limits<Components::RenderPassId>::max(), nullptr},
              _defaultTrackedSemaphoreComponent{nullptr, 0},
              _defaultSpriteComponent{},
              _defaultCameraComponent{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, false},
              _defaultViewportComponent{0.0f, 0.0f, 0.0f, 0.0f}
        {
        }

        template<typename T>
        friend EcsGraphicsBuilder<T>& AddGraphics(SystemSchedulerBuilder&);

    public:
        EcsGraphicsBuilder(const EcsGraphicsBuilder& other) = default;
        EcsGraphicsBuilder& operator=(const EcsGraphicsBuilder& other) = default;
        EcsGraphicsBuilder(EcsGraphicsBuilder&& other) = default;
        EcsGraphicsBuilder& operator=(EcsGraphicsBuilder&& other) = default;
        ~EcsGraphicsBuilder() = default;

        EcsGraphicsBuilder& WithGraphicsDevice(
            std::shared_ptr<NovelRT::Graphics::GraphicsDevice<TGraphicsBackend>>& device)
        {
            _graphicsDevice = device;
            return *this;
        }

        EcsGraphicsBuilder& WithSurfaceContext(
            std::shared_ptr<NovelRT::Graphics::GraphicsSurfaceContext<TGraphicsBackend>>& context)
        {
            _context = context;
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
            const Components::RenderPass<TGraphicsBackend>& defaultRenderPassComponent)
        {
            _defaultRenderPassComponent = defaultRenderPassComponent;
            return *this;
        }

        EcsGraphicsBuilder& WithOrchestrator(
            const std::shared_ptr<RenderOrchestratorSystem<TGraphicsBackend>>& orchestrator)
        {
            _orchestrator = orchestrator;
            return *this;
        }

        EcsGraphicsBuilder& WithDefaultOrchestrator()
        {
            return WithOrchestrator(
                std::make_shared<RenderOrchestratorSystem<TGraphicsBackend>>(_graphicsDevice, _context, _passManager));
        }

        void operator()(SystemScheduler& scheduler)
        {
            // TODO: add systems and components for rendering
            auto& cache = scheduler.GetComponentCache();

            cache.RegisterComponentType(_defaultBuiltCommandListComponent, "NovelRT::Ecs::Graphics::BuiltCommandList");
            cache.RegisterComponentType(_defaultRenderPassComponent, "NovelRT::Ecs::Graphics::RenderPass");
            cache.RegisterComponentType(_defaultTrackedSemaphoreComponent, "NovelRT::Ecs::Graphics::TrackedSemaphore");
            cache.RegisterComponentType(_defaultSpriteComponent, "NovelRT::Ecs::Graphics::Sprite");
            cache.RegisterComponentType(_defaultCameraComponent, "NovelRT::Ecs::Graphics::Camera");
            cache.RegisterComponentType(_defaultViewportComponent, "NovelRT::Ecs::Graphics::Viewport");

            unused(scheduler.RegisterSystemDependsOnAll(_orchestrator));
        }
    };

    template<typename TGraphicsBackend>
    EcsGraphicsBuilder<TGraphicsBackend>& AddGraphics(SystemSchedulerBuilder& builder)
    {
        return builder.Configure(EcsGraphicsBuilder<TGraphicsBackend>{});
    };
}
