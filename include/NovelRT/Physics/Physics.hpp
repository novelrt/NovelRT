// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PHYSICS_H
#define NOVELRT_PHYSICS_H

// physics dependencies
#include "NovelRT/Maths/Maths.h"
#include "NovelRT/Utilities/Misc.h"
#include <cstdint>
#include <memory>
#include <optional>
#include <vector>

/**
 * @brief
 * The plugin API for simulated physics.
 */
namespace NovelRT::Physics
{
    enum class BodyType;
    class PhysicsProvider;
    enum class RigidBodyCallbackFlags : std::int8_t;
}

// clang-format off

#include "BodyType.h"
#include "RigidBodyCallbackFlags.h"
#include "PhysicsProvider.h"
#include "2D/Physics.2D.h"

// clang-format on

#endif // !NOVELRT_PHYSICS_H