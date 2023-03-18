// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PHYSICS_H
#define NOVELRT_PHYSICS_H

// physics dependencies
#include <cstdint>
#include <memory>
#include "NovelRT/Maths/Maths.h"
#include "NovelRT/Utilities/Misc.h"
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

#include "BodyType.h"
#include "RigidBodyCallbackFlags.h"
#include "PhysicsProvider.h"
#include "2D/Physics.2D.h"

#endif // !NOVELRT_PHYSICS_H