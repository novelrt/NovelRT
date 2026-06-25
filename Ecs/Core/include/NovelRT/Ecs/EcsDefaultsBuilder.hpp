#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/ComponentCache.hpp>
#include <NovelRT/Ecs/Components/EntityGraphComponent.hpp>
#include <NovelRT/Ecs/Components/LinkedEntityListNodeComponent.hpp>
#include <NovelRT/Ecs/Components/TransformComponent.hpp>
#include <NovelRT/Ecs/SystemSchedulerBuilder.hpp>

namespace NovelRT::Ecs
{
    class EcsDefaultsBuilder
    {
    private:
        Components::EntityGraphComponent _defaultEntityGraphComponent;
        Components::LinkedEntityListNodeComponent _defaultLinkedEntityListNodeComponent;
        Components::TransformComponent _defaultTransformComponent;

        EcsDefaultsBuilder();
        friend EcsDefaultsBuilder& AddDefaults(SystemSchedulerBuilder&);

    public:
        // Intentionally disallow moving/copying
        EcsDefaultsBuilder(const EcsDefaultsBuilder& other) = delete;
        EcsDefaultsBuilder& operator=(const EcsDefaultsBuilder& other) = delete;
        EcsDefaultsBuilder(EcsDefaultsBuilder&& other) = default;
        EcsDefaultsBuilder& operator=(EcsDefaultsBuilder&& other) = default;
        ~EcsDefaultsBuilder() = default;

        EcsDefaultsBuilder& WithDefaultEntityGraphComponent(
            const Components::EntityGraphComponent& defaultGraphComponent);
        EcsDefaultsBuilder& WithDefaultLinkedEntityListNodeComponent(
            const Components::LinkedEntityListNodeComponent& defaultLinkedEntityListNodeComponent);
        EcsDefaultsBuilder& WithDefaultTransformComponent(
            const Components::TransformComponent& defaultTransformComponent);

        void operator()(SystemScheduler& scheduler);
    };

    EcsDefaultsBuilder& AddDefaults(SystemSchedulerBuilder& builder);
}
