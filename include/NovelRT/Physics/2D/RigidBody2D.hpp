// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PHYSICS_PHYSICS2D_RIGIDBODY2D_H
#define NOVELRT_PHYSICS_PHYSICS2D_RIGIDBODY2D_H

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    class RigidBody2D
    {
    protected:
        NovelRT::Maths::GeoVector2F _position;
        NovelRT::Maths::GeoVector2F _linearVelocity;
        NovelRT::Maths::GeoVector2F _angularVelocity;
        NovelRT::Maths::GeoVector2F _gravity;
        float _rotationAngle;
        float _linearDamping;
        float _angularDamping;
        RigidBodyFlags2D _flags;
        NovelRT::Physics::RigidBodyCallbackFlags _callbackFlags;

    public:
        [[nodiscard]] inline NovelRT::Maths::GeoVector2F GetPosition() const noexcept
        {
            return _position;
        }

        [[nodiscard]] inline NovelRT::Maths::GeoVector2F GetLinearVelocity() const noexcept
        {
            return _linearVelocity;
        }

        [[nodiscard]] inline NovelRT::Maths::GeoVector2F GetAngularVelocity() const noexcept
        {
            return _angularVelocity;
        }

        [[nodiscard]] inline NovelRT::Maths::GeoVector2F GetOwnGravity() const noexcept
        {
            return _gravity;
        }

        [[nodiscard]] inline float GetRotationAngle() const noexcept
        {
            return _rotationAngle;
        }

        [[nodiscard]] inline float GetLinearDamping() const noexcept
        {
            return _linearDamping;
        }

        [[nodiscard]] inline float GetAngularDamping() const noexcept
        {
            return _angularDamping;
        }

        [[nodiscard]] inline RigidBodyFlags2D GetBodyFlags() const noexcept
        {
            return _flags;
        }

        [[nodiscard]] inline bool IsAllowedToSleep() const noexcept
        {
            return (_flags & RigidBodyFlags2D::AllowSleep) == RigidBodyFlags2D::AllowSleep;
        }

        [[nodiscard]] inline bool IsAwakeOnStartUp() const noexcept
        {
            return (_flags & RigidBodyFlags2D::FixedRotation) == RigidBodyFlags2D::FixedRotation;
        }

        [[nodiscard]] inline bool IsUsingConstantCollisionDetection() const noexcept
        {
            return (_flags & RigidBodyFlags2D::UseConstantCollisionDetection) ==
                   RigidBodyFlags2D::UseConstantCollisionDetection;
        }

        [[nodiscard]] inline bool IsEnabled() const noexcept
        {
            return (_flags & RigidBodyFlags2D::Enabled) == RigidBodyFlags2D::Enabled;
        }

        [[nodiscard]] inline bool IsApplyingWorldGravity() const noexcept
        {
            return (_flags & RigidBodyFlags2D::UseWorldGravity) == RigidBodyFlags2D::UseWorldGravity;
        }

        virtual void SetPosition(NovelRT::Maths::GeoVector2F position) = 0;

        virtual void SetLinearVelocity(NovelRT::Maths::GeoVector2F linearVelocity) = 0;

        virtual void SetAngularVelocity(NovelRT::Maths::GeoVector2F angularVelocity) = 0;

        virtual void SetOwnGravity(NovelRT::Maths::GeoVector2F gravity) = 0;

        virtual void SetRotationAngle(float angle) = 0;

        virtual void SetLinearDamping(float linearDamping) = 0;

        virtual void SetAngularDamping(float angularDamping) = 0;

        virtual void SetBodyFlags(RigidBodyFlags2D flags) = 0;

        inline void SetAllowedToSleep(bool isAllowedToSleep)
        {
            SetBodyFlags((_flags & ~RigidBodyFlags2D::AllowSleep) |
                         (isAllowedToSleep ? RigidBodyFlags2D::AllowSleep : static_cast<RigidBodyFlags2D>(0)));
        }

        inline void SetUsingConstantCollisionDetection(bool isUsingConstantCollisionDetection)
        {
            SetBodyFlags((_flags & ~RigidBodyFlags2D::UseConstantCollisionDetection) |
                         (isUsingConstantCollisionDetection ? RigidBodyFlags2D::UseConstantCollisionDetection
                                                            : static_cast<RigidBodyFlags2D>(0)));
        }

        inline void SetEnabled(bool isEnabled)
        {
            SetBodyFlags((_flags & ~RigidBodyFlags2D::Enabled) |
                         (isEnabled ? RigidBodyFlags2D::Enabled : static_cast<RigidBodyFlags2D>(0)));
        }

        inline void SetApplyingWorldGravity(bool isApplyingWorldGravity)
        {
            SetBodyFlags(
                (_flags & ~RigidBodyFlags2D::UseWorldGravity) |
                (isApplyingWorldGravity ? RigidBodyFlags2D::UseWorldGravity : static_cast<RigidBodyFlags2D>(0)));
        }

        [[nodiscard]] virtual BoxCollisionFixture2D* AddBoxFixture(
            BoxCollisionFixtureDefinition2D& fixtureDefinition) = 0;

        [[nodiscard]] virtual CapsuleCollisionFixture2D* AddBoxFixture(
            CapsuleCollisionFixtureDefinition2D& fixtureDefinition) = 0;

        [[nodiscard]] virtual CircleCollisionFixture2D* AddBoxFixture(
            CircleCollisionFixtureDefinition2D& fixtureDefinition) = 0;

        [[nodiscard]] virtual EdgeCollisionFixture2D* AddBoxFixture(
            EdgeCollisionFixtureDefinition2D& fixtureDefinition) = 0;

        [[nodiscard]] virtual PolygonCollisionFixture2D* AddBoxFixture(
            PolygonCollisionFixtureDefinition2D& fixtureDefinition) = 0;

        virtual void RemoveFixture(const CollisionFixture2D* fixture) = 0;

        virtual void RemoveSharedFixture(const CollisionFixture2D* fixture) = 0;
    };
}

#endif // !NOVELRT_PHYSICS_RIGIDBODY2D_H