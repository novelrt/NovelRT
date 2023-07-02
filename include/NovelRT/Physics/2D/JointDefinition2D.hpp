// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#pragma once

#ifndef NOVELRT_PHYSICS_HPP
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    struct JointDefinition2D
    {
        RigidBody2D* PrimaryBody;
        RigidBody2D* SecondaryBody;
        NovelRT::Maths::GeoVector2F PrimaryBodyOffset;
        NovelRT::Maths::GeoVector2F SecondaryBodyOffset;
        float BreakForce;
        bool CollideConnectedBodies;

        virtual ~JointDefinition2D() = 0;
    };
}