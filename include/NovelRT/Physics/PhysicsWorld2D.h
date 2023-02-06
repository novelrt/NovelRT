// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PHYSICS_PHYSICSWORLD2D_H
#define NOVELRT_PHYSICS_PHYSICSWORLD2D_H

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics
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

        [[nodiscard]] virtual FixedJoint2D* AddFixedJoint(const FixedJointDefinition2D& jointDefiniton) = 0;

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
    };
}

#endif // !NOVELRT_PHYSICS_PHYSICSWORLD2D_H