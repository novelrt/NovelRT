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
        Maths::GeoVector2F scale = Maths::GeoVector2F::zero();
        float rotationInEulerAngles = 0.0f;

        inline TransformComponent& operator+=(const TransformComponent& other)
        {
            positionAndLayer += other.positionAndLayer;
            rotationInEulerAngles += other.rotationInEulerAngles;
            scale += other.scale;

            if (rotationInEulerAngles > 359.999999f) // 360 == 0 pretty sure :]
            {
                rotationInEulerAngles -= 359.999999f;
            }
            else if (rotationInEulerAngles < 0)
            {
                rotationInEulerAngles += 359.999999f;
            }

            return *this;
        }
    };

    struct EntityGraphComponent
    {
        EntityId parent = 0;
        EntityId childrenStartNode = 0;

        inline EntityGraphComponent& operator+=(const EntityGraphComponent& other)
        {
            *this = other;
            return *this;
        }
    };

    struct QuadEntityBlockComponent
    {
        uint8_t blockWriteMap;

        EntityId previousBlock;

        EntityId zero;
        EntityId one;
        EntityId two;
        EntityId three;

        EntityId nextBlock;

        inline QuadEntityBlockComponent& operator+=(const QuadEntityBlockComponent& other)
        {
            *this = other;
            return *this;
        }
    };

    struct LinkedEntityListNodeComponent
    {
        EntityId previous = std::numeric_limits<EntityId>::max();
        EntityId next = std::numeric_limits<EntityId>::max();

        inline LinkedEntityListNodeComponent& operator+=(const LinkedEntityListNodeComponent& other)
        {
            *this = other;
            return *this;
        }
    };

}
#endif // NOVELRT_DEFAULTCOMPONENTTYPES_H
