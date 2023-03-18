// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PHYSICS_PHYSICS2D_BODYDEFINITION2D_H
#define NOVELRT_PHYSICS_PHYSICS2D_BODYDEFINITION2D_H

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    struct BodyDefinition2D final
    {
        std::optional<OnCollisionEnterCallbackDelegate2D> OnCollisionEnter;
        std::optional<OnCollisionExitCallbackDelegate2D> OnCollisionExit;
        std::optional<OnTriggerEnterCallbackDelegate2D> OnTriggerEnter;
        std::optional<OnTriggerExitCallbackDelegate2D> OnTriggerExit;
        NovelRT::Maths::GeoVector2F Position;
        NovelRT::Maths::GeoVector2F LinearVelocity;
        NovelRT::Maths::GeoVector2F AngularVelocity;
        NovelRT::Maths::GeoVector2F Gravity;
        float RotationAngle;
        float LinearDamping;
        float AngularDamping;
        RigidBodyFlags2D Flags;
    };
}

// TODO: when implementing box2d, instead of relying on gravity scale, set it to 1 or 0 (depending on
// BodyFlags::UseWorldGravity) and apply a constant force during the world step.

#endif // !NOVELRT_PHYSICS_PHYSICS2D_BODYDEFINITION2D_H