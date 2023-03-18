// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PHYSICS_PHYSICS2D_H
#define NOVELRT_PHYSICS_PHYSICS2D_H

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

/**
 * @brief 
 * The plugin API for simulated physics in a two dimensional space.
 */
namespace NovelRT::Physics::Physics2D
{
    class PhysicsProvider2D;
    class PhysicsWorld2D;
    struct RayCastHit2D;
    struct OverlapHit2D;
    struct CollisionCallbackArgument2D;
    struct TriggerCallbackArgument2D;
    class RigidBody2D;
    struct BodyDefinition2D;
    enum struct RigidBodyFlags2D : std::int8_t;
    class CollisionFixture2D;
    class BoxCollisionFixture2D;
    class CircleCollisionFixture2D;
    class CapsuleCollisionFixture2D;
    class EdgeCollisionFixture2D;
    class PolygonCollisionFixture2D;
    struct CollisionFixtureDefinition2D;
    struct BoxCollisionFixtureDefinition2D;
    struct CircleCollisionFixtureDefinition2D;
    struct CapsuleCollisionFixtureDefinition2D;
    struct EdgeCollisionFixtureDefinition2D;
    struct PolygonCollisionFixtureDefinition2D;
    class Joint2D;
    class DistanceJoint2D;
    class GearJoint2D;
    class FixedDistanceJoint2D;
    class HingeJoint2D;
    class SlidingJoint2D;
    class SpringJoint2D;
    struct JointDefinition2D;
    struct DistanceJointDefinition2D;
    struct GearJointDefinition2D;
    struct FixedDistanceJointDefinition2D;
    struct HingeJointDefinition2D;
    struct SlidingJointDefinition2D;
    struct SpringJointDefinition2D;

    // TODO: figure out what arguments should be passed
    typedef void (*OnCollisionEnterCallbackDelegate2D)(CollisionCallbackArgument2D collisionEnterArgument);
    typedef void (*OnCollisionExitCallbackDelegate2D)(CollisionCallbackArgument2D collisionExitArgument);
    typedef void (*OnTriggerEnterCallbackDelegate2D)(TriggerCallbackArgument2D triggerEnterArgument);
    typedef void (*OnTriggerExitCallbackDelegate2D)(TriggerCallbackArgument2D triggerExitArgument);
}

// clang-format off

#include "PhysicsProvider2D.h"
#include "RigidBodyFlags2D.h"
#include "RigidBody2D.h"
#include "PhysicsWorld2D.h"
#include "OverlapHit2D.h"
#include "RayCastHit2D.h"
#include "CollisionCallbackArgument2D.h"
#include "TriggerCallbackArgument2D.h"
#include "BodyDefinition2D.h"
#include "CollisionFixture2D.h"
#include "BoxCollisionFixture2D.h"
#include "CircleCollisionFixture2D.h"
#include "CapsuleCollisionFixture2D.h"
#include "EdgeCollisionFixture2D.h"
#include "PolygonCollisionFixture2D.h"
#include "CollisionFixtureDefinition2D.h"
#include "BoxCollisionFixtureDefinition2D.h"
#include "CircleCollisionFixtureDefinition2D.h"
#include "CapsuleCollisionFixtureDefinition2D.h"
#include "EdgeCollisionFixtureDefinition2D.h"
#include "PolygonCollisionFixtureDefinition2D.h"
#include "Joint2D.h"
#include "DistanceJoint2D.h"
#include "FixedDistanceJoint2D.h"
#include "GearJoint2D.h"
#include "HingeJoint2D.h"
#include "SlidingJoint2D.h"
#include "SpringJoint2D.h"
#include "JointDefinition2D.h"
#include "DistanceJointDefinition2D.h"
#include "FixedDistanceJointDefinition2D.h"
#include "HingeJointDefinition2D.h"
#include "GearJointDefinition2D.h"
#include "SlidingJointDefinition2D.h"
#include "SpringJointDefinition2D.h"

// clang-format on

#endif // !NOVELRT_PHYSICS_PHYSICS2D_H