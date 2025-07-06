#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/ComponentCache.hpp>
#include <NovelRT/Ecs/EcsUtils.hpp>
#include <NovelRT/Ecs/SystemSchedulerBuilder.hpp>
#include <NovelRT/Maths/GeoVector2F.hpp>
#include <NovelRT/Maths/GeoVector3F.hpp>
#include <NovelRT/Maths/Constants.hpp>

namespace NovelRT::Ecs
{
    struct TransformComponent
    {
        Maths::GeoVector3F positionAndLayer = Maths::GeoVector3F::Zero();
        Maths::GeoVector2F scale = Maths::GeoVector2F::One();
        float rotationInRadians = 0.0f;

        inline TransformComponent& operator+=(const TransformComponent& other)
        {
            positionAndLayer += other.positionAndLayer;
            rotationInRadians += other.rotationInRadians;
            scale += other.scale;

            if (rotationInRadians > Maths::Tau<float>)
            {
                rotationInRadians -= Maths::Tau<float>;
            }
            else if (rotationInRadians < -Maths::Tau<float>)
            {
                rotationInRadians += Maths::Tau<float>;
            }

            return *this;
        }

        friend inline bool operator==(const TransformComponent& lhs, const TransformComponent& rhs) noexcept
        {
            return lhs.positionAndLayer == rhs.positionAndLayer && lhs.scale == rhs.scale &&
                   lhs.rotationInRadians == rhs.rotationInRadians;
        }

        friend inline bool operator!=(const TransformComponent& lhs, const TransformComponent& rhs) noexcept
        {
            return !(lhs == rhs);
        }
    };

    struct EntityGraphComponent
    {
        bool isValid = true;
        EntityId parent = std::numeric_limits<EntityId>::max();
        EntityId childrenStartNode = std::numeric_limits<EntityId>::max();

        inline EntityGraphComponent& operator+=(const EntityGraphComponent& other)
        {
            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const EntityGraphComponent& other) const noexcept
        {
            return isValid == other.isValid && parent == other.parent && childrenStartNode == other.childrenStartNode;
        }

        [[nodiscard]] inline bool operator!=(const EntityGraphComponent& other) const noexcept
        {
            return !(*this == other);
        }
    };

    struct LinkedEntityListNodeComponent
    {
        bool IsValid = true;
        EntityId previous = std::numeric_limits<EntityId>::max();
        EntityId next = std::numeric_limits<EntityId>::max();

        inline LinkedEntityListNodeComponent& operator+=(const LinkedEntityListNodeComponent& other)
        {
            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const LinkedEntityListNodeComponent& other) const noexcept
        {
            return IsValid == other.IsValid && previous == other.previous && next == other.next;
        }

        [[nodiscard]] inline bool operator!=(const LinkedEntityListNodeComponent& other) const noexcept
        {
            return !(*this == other);
        }
    };

    class EcsDefaultsBuilder
    {
    private:
        EntityGraphComponent _defaultEntityGraphComponent;
        LinkedEntityListNodeComponent _defaultLinkedEntityListNodeComponent;
        TransformComponent _defaultTransformComponent;

        EcsDefaultsBuilder(SystemSchedulerBuilder& builder)
        : _defaultEntityGraphComponent{false, std::numeric_limits<EntityId>::max(), std::numeric_limits<EntityId>::max()},
        _defaultLinkedEntityListNodeComponent{false, std::numeric_limits<EntityId>::max(), std::numeric_limits<EntityId>::max()},
        _defaultTransformComponent{Maths::GeoVector3F::Uniform(NAN), Maths::GeoVector2F::Uniform(NAN), NAN}
        {
            builder.Configure([this](SystemScheduler& scheduler) {
                auto& cache = scheduler.GetComponentCache();

                cache.RegisterComponentType(_defaultEntityGraphComponent, "NovelRT::Ecs::EntityGraphComponent");
                cache.RegisterComponentType(_defaultLinkedEntityListNodeComponent, "NovelRT::Ecs::LinkedEntityListNodeComponent");
                cache.RegisterComponentType(_defaultTransformComponent, "NovelRT::Ecs::TransformComponent");
            });
        };

        friend EcsDefaultsBuilder AddDefaults(SystemSchedulerBuilder&);

    public:
        EcsDefaultsBuilder& WithDefaultEntityGraphComponent(const EntityGraphComponent& defaultGraphComponent)
        {
            _defaultEntityGraphComponent = defaultGraphComponent;
            return *this;
        }

        EcsDefaultsBuilder& WithDefaultLinkedEntityListNodeComponent(const LinkedEntityListNodeComponent& defaultLinkedEntityListNodeComponent)
        {
            _defaultLinkedEntityListNodeComponent = defaultLinkedEntityListNodeComponent;
            return *this;
        }

        EcsDefaultsBuilder& WithDefaultTransformComponent(const TransformComponent& defaultTransformComponent)
        {
            _defaultTransformComponent = defaultTransformComponent;
            return *this;
        }
    };

    EcsDefaultsBuilder AddDefaults(SystemSchedulerBuilder& builder)
    {
        return EcsDefaultsBuilder{builder};
    }
}
