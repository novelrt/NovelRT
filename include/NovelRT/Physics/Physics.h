// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PHYSICS_H
#define NOVELRT_PHYSICS_H

// physics dependencies
#include <memory>
#include "NovelRT/Maths/Maths.h"

namespace NovelRT::Physics
{
    class PhysicsProvider;
    class PhysicsProvider2D;
    class PhysicsWorld2D;
    class RigidBody2D;
    class BodyDefinition2D;
}

#include "PhysicsProvider.h"
#include "PhysicsProvider2D.h"
#include "PhysicsWorld2D.h"
#include "RigidBody2D.h"
#include "BodyDefinition2D.h"

#endif // !NOVELRT_PHYSICS_H