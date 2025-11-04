#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/ComponentCache.hpp>
#include <NovelRT/Ecs/SystemSchedulerBuilder.hpp>
#include <NovelRT/Ecs/Components/TransformComponent.hpp>
#include <NovelRT/Ecs/Components/EntityGraphComponent.hpp>
#include <NovelRT/Ecs/Components/LinkedEntityListNodeComponent.hpp>

namespace NovelRT::Ecs
{
    class EcsDefaultsBuilder
    {
    private:
        Components::EntityGraphComponent _defaultEntityGraphComponent;
        Components::LinkedEntityListNodeComponent _defaultLinkedEntityListNodeComponent;
        Components::TransformComponent _defaultTransformComponent;

        explicit EcsDefaultsBuilder(SystemSchedulerBuilder& builder);
        friend EcsDefaultsBuilder AddDefaults(SystemSchedulerBuilder&);

    public:
        // Intentionally disallow moving/copying
        EcsDefaultsBuilder(const EcsDefaultsBuilder& other) = delete;
        EcsDefaultsBuilder& operator=(const EcsDefaultsBuilder& other) = delete;
        EcsDefaultsBuilder(EcsDefaultsBuilder&& other) = delete;
        EcsDefaultsBuilder& operator=(EcsDefaultsBuilder&& other) = delete;
        ~EcsDefaultsBuilder() = default;

        EcsDefaultsBuilder& WithDefaultEntityGraphComponent(
            const Components::EntityGraphComponent& defaultGraphComponent);
        EcsDefaultsBuilder& WithDefaultLinkedEntityListNodeComponent(
            const Components::LinkedEntityListNodeComponent& defaultLinkedEntityListNodeComponent);
        EcsDefaultsBuilder& WithDefaultTransformComponent(
            const Components::TransformComponent& defaultTransformComponent);
    };

    EcsDefaultsBuilder AddDefaults(SystemSchedulerBuilder& builder);
}
