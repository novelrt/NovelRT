// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PHYSICS_JOINTDEFINITION2D_H
#define NOVELRT_PHYSICS_JOINTDEFINITION2D_H

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics
{
    struct JointDefinition2D
    {
        RigidBody2D* PrimaryBody;
        RigidBody2D* SecondaryBody;
        NovelRT::Maths::GeoVector2F PrimaryBodyOffset;
        NovelRT::Maths::GeoVector2F SecondaryBodyOffset;
        float BreakForce;
        bool CollideConnectedBodies;

        [[nodiscard]] virtual JointType GetJointType() = 0;
    };
}

#endif // !NOVELRT_PHYSICS_JOINTDEFINITION2D_H