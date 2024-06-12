// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#pragma once

#ifndef NOVELRT_PHYSICS_HPP
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

#include "PhysicsProvider2D.hpp"
#include "RigidBodyFlags2D.hpp"
#include "RigidBody2D.hpp"
#include "PhysicsWorld2D.hpp"
#include "OverlapHit2D.hpp"
#include "RayCastHit2D.hpp"
#include "CollisionCallbackArgument2D.hpp"
#include "TriggerCallbackArgument2D.hpp"
#include "BodyDefinition2D.hpp"
#include "CollisionFixture2D.hpp"
#include "BoxCollisionFixture2D.hpp"
#include "CircleCollisionFixture2D.hpp"
#include "CapsuleCollisionFixture2D.hpp"
#include "EdgeCollisionFixture2D.hpp"
#include "PolygonCollisionFixture2D.hpp"
#include "CollisionFixtureDefinition2D.hpp"
#include "BoxCollisionFixtureDefinition2D.hpp"
#include "CircleCollisionFixtureDefinition2D.hpp"
#include "CapsuleCollisionFixtureDefinition2D.hpp"
#include "EdgeCollisionFixtureDefinition2D.hpp"
#include "PolygonCollisionFixtureDefinition2D.hpp"
#include "Joint2D.hpp"
#include "DistanceJoint2D.hpp"
#include "FixedDistanceJoint2D.hpp"
#include "GearJoint2D.hpp"
#include "HingeJoint2D.hpp"
#include "SlidingJoint2D.hpp"
#include "SpringJoint2D.hpp"
#include "JointDefinition2D.hpp"
#include "DistanceJointDefinition2D.hpp"
#include "FixedDistanceJointDefinition2D.hpp"
#include "HingeJointDefinition2D.hpp"
#include "GearJointDefinition2D.hpp"
#include "SlidingJointDefinition2D.hpp"
#include "SpringJointDefinition2D.hpp"

// clang-format on