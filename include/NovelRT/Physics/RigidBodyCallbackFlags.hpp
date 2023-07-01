// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#pragma once

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics
{
    enum class RigidBodyCallbackFlags : std::int8_t
    {
        HasCollisionEnterCallback = 1 << 0,
        HasCollisionExitCallback = 1 << 1,
        HasCollisionStayCallback = 1 << 2,
        HasTriggerEnterCallback = 1 << 3,
        HasTriggerExitCallback = 1 << 4,
        HasTriggerStayCallback = 1 << 5,
    };
}