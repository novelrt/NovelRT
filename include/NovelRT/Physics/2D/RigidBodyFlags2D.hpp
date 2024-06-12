// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#pragma once

#ifndef NOVELRT_PHYSICS_HPP
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    enum class RigidBodyFlags2D : std::int8_t
    {
        AllowSleep = 1 << 0,
        Awake = 1 << 1,
        FixedRotation = 1 << 2,
        UseConstantCollisionDetection = 1 << 3,
        Enabled = 1 << 4,
        UseWorldGravity = 1 << 5
    };
}