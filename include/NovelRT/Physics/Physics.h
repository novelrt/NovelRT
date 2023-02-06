// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PHYSICS_H
#define NOVELRT_PHYSICS_H

// physics dependencies
#include <memory>
#include "NovelRT/Maths/Maths.h"

/**
 * @brief
 * The plugin API for simulated physics.
 */
namespace NovelRT::Physics
{
    enum class BodyType;
    enum class JointType;
    class PhysicsProvider;
    class PhysicsProvider2D;
    class PhysicsWorld2D;
    class RigidBody2D;
    struct BodyDefinition2D;
    class Joint2D;
    class FixedJoint2D;
    class HingeJoint2D;
    struct JointDefinition2D;
    struct DistanceJointDefinition2D;
}

#include "BodyType.h"
#include "JointType.h"
#include "PhysicsProvider.h"
#include "PhysicsProvider2D.h"
#include "PhysicsWorld2D.h"
#include "RigidBody2D.h"
#include "BodyDefinition2D.h"
#include "Joint2D.h"
#include "FixedJoint2D.h"
#include "HingeJoint2D.h"
#include "JointDefinition2D.h"
#include "DistanceJointDefinition2D.h"
#include "FixedJointDefinition2D.h"


#endif // !NOVELRT_PHYSICS_H