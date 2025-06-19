#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/SystemSchedulerBuilder.hpp>
#include <NovelRT/Graphics/GraphicsProvider.hpp>

#include <memory>

namespace NovelRT::Ecs::Graphics
{
    template <typename TGraphicsBackend>
    class EcsGraphicsBuilder
    {
    private:
        std::shared_ptr<NovelRT::Graphics::GraphicsProvider<TGraphicsBackend>> _graphicsProvider;

        EcsGraphicsBuilder(SystemSchedulerBuilder& builder)
        {
            builder.Configure([this](SystemScheduler& scheduler) {
                // TODO: add systems and components for rendering
            });
        };

        friend EcsGraphicsBuilder AddGraphics(SystemSchedulerBuilder&);

    public:
        EcsGraphicsBuilder& WithGraphicsProvider(std::shared_ptr<NovelRT::Graphics::GraphicsProvider<TGraphicsBackend>>& provider)
        {
            _graphicsProvider = provider;
            return *this;
        }
    };

    template <typename TGraphicsBackend>
    EcsGraphicsBuilder<TGraphicsBackend> AddGraphics(SystemSchedulerBuilder& builder)
    {
        return EcsGraphicsBuilder<TGraphicsBackend>{builder};
    };
}
