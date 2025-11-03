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

    template <typename TGraphicsBackend>
    class EcsGraphicsBuilder
    {
    private:
        std::shared_ptr<NovelRT::Graphics::GraphicsProvider<TGraphicsBackend>> _graphicsProvider;
        BuiltCommandList _defaultBuiltCommandListComponent;

        EcsGraphicsBuilder(SystemSchedulerBuilder& builder)
            : _defaultBuiltCommandListComponent{nullptr, 0}
        {
            builder.Configure([this](SystemScheduler& scheduler) {
                // TODO: add systems and components for rendering
                auto& cache = scheduler.GetComponentCache();

                cache.RegisterComponentType(_defaultBuiltCommandListComponent, "NovelRT::Ecs::Graphics::BuiltCommandList");
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
    };

    template <typename TGraphicsBackend>
    EcsGraphicsBuilder<TGraphicsBackend> AddGraphics(SystemSchedulerBuilder& builder)
    {
        return EcsGraphicsBuilder<TGraphicsBackend>{builder};
    };
}
