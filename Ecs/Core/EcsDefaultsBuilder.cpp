// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/EcsDefaultsBuilder.hpp>

using namespace NovelRT::Ecs;

EcsDefaultsBuilder::EcsDefaultsBuilder()
    : _defaultEntityGraphComponent{false, std::numeric_limits<EntityId>::max(), std::numeric_limits<EntityId>::max()},
      _defaultLinkedEntityListNodeComponent{false, std::numeric_limits<EntityId>::max(),
                                            std::numeric_limits<EntityId>::max()},
      _defaultTransformComponent{Maths::GeoVector3F::Uniform(NAN), Maths::GeoVector2F::Uniform(NAN), NAN} {};

EcsDefaultsBuilder& NovelRT::Ecs::EcsDefaultsBuilder::WithDefaultEntityGraphComponent(
    const Components::EntityGraphComponent& defaultGraphComponent)
{
    _defaultEntityGraphComponent = defaultGraphComponent;
    return *this;
}

EcsDefaultsBuilder& EcsDefaultsBuilder::WithDefaultLinkedEntityListNodeComponent(
    const Components::LinkedEntityListNodeComponent& defaultLinkedEntityListNodeComponent)
{
    _defaultLinkedEntityListNodeComponent = defaultLinkedEntityListNodeComponent;
    return *this;
}

EcsDefaultsBuilder& EcsDefaultsBuilder::WithDefaultTransformComponent(
    const Components::TransformComponent& defaultTransformComponent)
{
    _defaultTransformComponent = defaultTransformComponent;
    return *this;
}

void EcsDefaultsBuilder::operator()(SystemScheduler& scheduler)
{
    auto& cache = scheduler.GetComponentCache();

    cache.RegisterComponentType(_defaultEntityGraphComponent, "NovelRT::Ecs::EntityGraphComponent");
    cache.RegisterComponentType(_defaultLinkedEntityListNodeComponent, "NovelRT::Ecs::LinkedEntityListNodeComponent");
    cache.RegisterComponentType(_defaultTransformComponent, "NovelRT::Ecs::TransformComponent");
}

EcsDefaultsBuilder& NovelRT::Ecs::AddDefaults(SystemSchedulerBuilder& builder)
{
    return builder.Configure(EcsDefaultsBuilder{});
}
