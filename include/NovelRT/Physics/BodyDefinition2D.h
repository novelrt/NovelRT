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
        NovelRT::Maths::GeoVector2F Position;
        float Angle;
        NovelRT::Maths::GeoVector2F LinearVelocity;
        NovelRT::Maths::GeoVector2F AngularVelocity;
        float LinearDamping;
        float AngularDamping;
        bool AllowSleep;
        bool Awake;
        bool FixedRotation;
        bool UseConstantCollisionDetection;
        bool Enabled;
        float GravityScale
    };
}


#endif // !NOVELRT_PHYSICS_BODYDEFINITION2D_H