// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_DEFAULTCOMPONENTTYPES_H
#define NOVELRT_DEFAULTCOMPONENTTYPES_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs
{
    struct TransformComponent
    {
        Maths::GeoVector3F positionAndLayer = Maths::GeoVector3F::zero();
        Maths::GeoVector2F scale = Maths::GeoVector2F::one();
        float rotationInRadians = 0.0f;

        inline TransformComponent& operator+=(const TransformComponent& other)
        {
            positionAndLayer += other.positionAndLayer;
            rotationInRadians += other.rotationInRadians;
            scale += other.scale;

            if (rotationInRadians > Maths::Utilities::Tau<float>())
            {
                rotationInRadians -= Maths::Utilities::Tau<float>();
            }
            else if (rotationInRadians < -Maths::Utilities::Tau<float>())
            {
                rotationInRadians += Maths::Utilities::Tau<float>();
            }

            return *this;
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

}
#endif // NOVELRT_DEFAULTCOMPONENTTYPES_H
