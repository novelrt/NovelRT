// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PHYSICS_BODYDEFINITION2D_H
#define NOVELRT_PHYSICS_BODYDEFINITION2D_H

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics
{
    struct BodyDefinition2D
    {
        enum class BodyFlags
        {
            AllowSleep = 1 << 0,
            Awake = 1 << 1,
            FixedRotation = 1 << 2,
            UseConstantCollisionDetection = 1 << 3,
            Enabled = 1 << 4,
            UseWorldGravity = 1 << 5
        };

        NovelRT::Maths::GeoVector2F Position;
        NovelRT::Maths::GeoVector2F LinearVelocity;
        NovelRT::Maths::GeoVector2F AngularVelocity;
        NovelRT::Maths::GeoVector2F Gravity;
        float Angle;
        float LinearDamping;
        float AngularDamping;
        BodyFlags Flags;
    };
}

// TODO: when implementing box2d, instead of relying on gravity scale, set it to 1 or 0 (depending on BodyFlags::UseWorldGravity) and apply a constant force during the world step.

#endif // !NOVELRT_PHYSICS_BODYDEFINITION2D_H