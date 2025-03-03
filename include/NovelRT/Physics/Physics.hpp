// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#pragma once
#define NOVELRT_PHYSICS_HPP

// TODO: replace *.h with *.hpp when they get renamed.

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

#include "BodyType.hpp"
#include "RigidBodyCallbackFlags.hpp"
#include "PhysicsProvider.hpp"
#include "2D/Physics.2D.hpp"

// clang-format on