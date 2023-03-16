// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PHYSICS_H
#define NOVELRT_PHYSICS_H

// physics dependencies
#include <memory>
#include "NovelRT/Maths/Maths.h"
#include "NovelRT/Utilities/Misc.h"
#include <vector>

/**
 * @brief
 * The plugin API for simulated physics.
 */
namespace NovelRT::Physics
{
    enum class BodyType;
    class PhysicsProvider;
}

#include "BodyType.h"
#include "PhysicsProvider.h"
#include "2D/Physics.2D.h"

#endif // !NOVELRT_PHYSICS_H