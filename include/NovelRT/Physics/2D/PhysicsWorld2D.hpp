// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#pragma once

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    /**
     * @brief
     * A 2D space for physics simulations.
     */
    class PhysicsWorld2D
    {
    public:
        /**
         * @brief
         * Simulates how the physics objects have moved over the given period.
         *
         * @param timeStep The time passed since the last step.
         */
        virtual void Step(float timeStep) = 0;

        /**
         * @brief
         * Adds a RigidBody2D to be simulated to the world.
         *
         * @details
         *
         *
         * @param bodyDefinition
         * @return RigidBody2D* A pointer to the RigidBody2D that has been added to this world instance.
         */
        [[nodiscard]] virtual RigidBody2D* AddRigidBody(const BodyDefinition2D& bodyDefinition) = 0;

        /**
         * @brief Removes a RigidBody2D from the world to stop simulating it.
         *
         * @param rigidBody The RigidBody2D to be removed from this world instance.
         */
        virtual void RemoveRigidBody(RigidBody2D* rigidBody) = 0;

        [[nodiscard]] virtual DistanceJoint2D* AddDistanceJoint(const DistanceJointDefinition2D& jointDefinition) = 0;

        [[nodiscard]] virtual FixedDistanceJoint2D* AddFixedJoint(
            const FixedDistanceJointDefinition2D& jointDefiniton) = 0;

        [[nodiscard]] virtual GearJoint2D* AddGearJoint2D(const GearJointDefinition2D& jointDefinition) = 0;

        [[nodiscard]] virtual HingeJoint2D* AddHingeJoint(const HingeJointDefinition2D& jointDefinition) = 0;

        [[nodiscard]] virtual SpringJoint2D* AddSpringJoint(const SpringJointDefinition2D& jointDefinition) = 0;

        virtual void RemoveJoint(Joint2D* joint) = 0;

        /**
         * @brief
         * Gets the current gravity that gets applied to this world.
         *
         * @details
         *
         *
         * @return NovelRT::Maths::GeoVector2F The gravity that gets applied to this world
         */
        [[nodiscard]] virtual NovelRT::Maths::GeoVector2F GetGravity() = 0;

        /**
         * @brief
         * Gets the current gravity that gets applied to this world.
         *
         * @param gravity
         */
        virtual void SetGravity(NovelRT::Maths::GeoVector2F gravity) = 0;

        [[nodiscard]] virtual BoxCollisionFixture2D* CreateSharedBoxFixture(
            BoxCollisionFixtureDefinition2D& fixtureDefinition) = 0;

        [[nodiscard]] virtual CapsuleCollisionFixture2D* CreateSharedBoxFixture(
            CapsuleCollisionFixtureDefinition2D& fixtureDefinition) = 0;

        [[nodiscard]] virtual CircleCollisionFixture2D* CreateSharedBoxFixture(
            CircleCollisionFixtureDefinition2D& fixtureDefinition) = 0;

        [[nodiscard]] virtual EdgeCollisionFixture2D* CreateSharedBoxFixture(
            EdgeCollisionFixtureDefinition2D& fixtureDefinition) = 0;

        [[nodiscard]] virtual PolygonCollisionFixture2D* CreateSharedBoxFixture(
            PolygonCollisionFixtureDefinition2D& fixtureDefinition) = 0;

        virtual void RemoveSharedFixture(CollisionFixture2D* fixture) = 0;

        [[nodiscard]] virtual std::optional<RayCastHit2D> RayCast(NovelRT::Maths::GeoVector2F origin,
                                                                  NovelRT::Maths::GeoVector2F direction,
                                                                  float length) const = 0;

        [[nodiscard]] virtual std::optional<RayCastHit2D> RayCast(NovelRT::Maths::GeoVector2F pointOne,
                                                                  NovelRT::Maths::GeoVector2F pointTwo) const = 0;

        [[nodiscard]] virtual size_t RayCast(NovelRT::Maths::GeoVector2F origin,
                                             NovelRT::Maths::GeoVector2F direction,
                                             float length,
                                             NovelRT::Utilities::Misc::Span<RayCastHit2D> buffer) const = 0;

        [[nodiscard]] virtual size_t RayCast(NovelRT::Maths::GeoVector2F pointOne,
                                             NovelRT::Maths::GeoVector2F pointTwo,
                                             NovelRT::Utilities::Misc::Span<RayCastHit2D> buffer) const = 0;

        [[nodiscard]] virtual std::vector<RayCastHit2D> RayCastAll(NovelRT::Maths::GeoVector2F origin,
                                                                   NovelRT::Maths::GeoVector2F direction,
                                                                   float length) const = 0;

        [[nodiscard]] virtual std::vector<RayCastHit2D> RayCastAll(NovelRT::Maths::GeoVector2F pointOne,
                                                                   NovelRT::Maths::GeoVector2F pointTwo) const = 0;

        [[nodiscard]] virtual size_t RayCastAll(NovelRT::Maths::GeoVector2F origin,
                                                NovelRT::Maths::GeoVector2F direction,
                                                float length,
                                                std::vector<RayCastHit2D> buffer) const = 0;

        [[nodiscard]] virtual size_t RayCastAll(NovelRT::Maths::GeoVector2F pointOne,
                                                NovelRT::Maths::GeoVector2F pointTwo,
                                                std::vector<RayCastHit2D> buffer) const = 0;

        [[nodiscard]] virtual bool RayCastHasHit(NovelRT::Maths::GeoVector2F origin,
                                                 NovelRT::Maths::GeoVector2F direction,
                                                 float length) const = 0;

        [[nodiscard]] virtual bool RayCastHasHit(NovelRT::Maths::GeoVector2F pointOne,
                                                 NovelRT::Maths::GeoVector2F pointTwo) const = 0;

        [[nodiscard]] virtual std::optional<OverlapHit2D> BoxOverlap(NovelRT::Maths::GeoVector2F position,
                                                                     NovelRT::Maths::GeoVector2F halfExtend,
                                                                     float rotation) const = 0;

        [[nodiscard]] virtual size_t BoxOverlap(NovelRT::Maths::GeoVector2F position,
                                                NovelRT::Maths::GeoVector2F halfExtend,
                                                float rotation,
                                                NovelRT::Utilities::Misc::Span<OverlapHit2D> buffer) const = 0;

        [[nodiscard]] virtual std::vector<OverlapHit2D> BoxOverlapAll(NovelRT::Maths::GeoVector2F position,
                                                                      NovelRT::Maths::GeoVector2F halfExtend,
                                                                      float rotation) const = 0;

        [[nodiscard]] virtual size_t BoxOverlapAll(NovelRT::Maths::GeoVector2F position,
                                                   NovelRT::Maths::GeoVector2F halfExtend,
                                                   float rotation,
                                                   std::vector<OverlapHit2D> buffer) const = 0;

        [[nodiscard]] virtual bool BoxHasOverlap(NovelRT::Maths::GeoVector2F position,
                                                 NovelRT::Maths::GeoVector2F halfExtend,
                                                 float rotation) const = 0;

        [[nodiscard]] virtual std::optional<OverlapHit2D> CircleOverlap(NovelRT::Maths::GeoVector2F position,
                                                                        float radius) const = 0;

        [[nodiscard]] virtual size_t CircleOverlap(NovelRT::Maths::GeoVector2F position,
                                                   float radius,
                                                   NovelRT::Utilities::Misc::Span<OverlapHit2D> buffer) const = 0;

        [[nodiscard]] virtual std::vector<OverlapHit2D> CircleOverlapAll(NovelRT::Maths::GeoVector2F position,
                                                                         float radius) const = 0;

        [[nodiscard]] virtual size_t CircleOverlapAll(NovelRT::Maths::GeoVector2F position,
                                                      float radius,
                                                      std::vector<OverlapHit2D> buffer) const = 0;

        [[nodiscard]] virtual bool CircleHasOverlap(NovelRT::Maths::GeoVector2F position, float radius) const = 0;
    };
}