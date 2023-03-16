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
        BodyDefinition2D::BodyFlags _flags;


    public:
        inline NovelRT::Maths::GeoVector2F GetPosition() const noexcept{
            return _position;
        }

        inline NovelRT::Maths::GeoVector2F GetLinearVelocity() const noexcept{
            return _linearVelocity;
        }

        inline NovelRT::Maths::GeoVector2F GetAngularVelocity() const noexcept{
            return _angularVelocity
        }

        inline NovelRT::Maths::GeoVector2F GetOwnGravity() const noexcept{
            return _gravity;
        }

        inline float GetRotationAngle() const noexcept
        {
            return _rotationAngle;
        }

        inline float GetLinearDamping() const noexcept{
            return _linearDamping;
        }

        inline float GetAngularDamping() const noexcept
        {
            return _angularDamping;
        }

        inline BodyDefinition2D::BodyFlags GetBodyFlags() const noexcept
        {
            return _flags;
        }

        inline bool IsAllowedToSleep() const noexcept
        {
            return _flags & BodyDefinition2D::BodyFlags::AllowSleep;
        }

        inline bool IsAwakeOnStartUp() const noexcept
        {
            return _flags & BodyDefinition2D::BodyFlags::FixedRotation;
        }

        inline bool IsUsingConstantCollisionDetection() const noexcept
        {
            return _flags & BodyDefinition2D::BodyFlags::UseConstantCollisionDetection;
        }

        inline bool IsEnabled() const noexcept
        {
            return _flags & BodyDefinition2D::BodyFlags::Enabled;
        }

        inline bool IsApplyingWorldGravity() const noexcept
        {
            return _flags & BodyDefinition2D::BodyFlags::UseWorldGravity;
        }

        virtual void SetPosition(NovelRT::Maths::GeoVector2F position) = 0;

        virtual void SetLinearVelocity(NovelRT::Maths::GeoVector2F linearVelocity) = 0;

        virtual void SetAngularVelocity(NovelRT::Maths::GeoVector2F angularVelocity) = 0;

        virtual void SetOwnGravity(NovelRT::Maths::GeoVector2F gravity) = 0;

        virtual void SetRotationAngle(float angle) = 0;

        virtual void SetLinearDamping(float linearDamping) = 0;

        virtual void SetAngularDamping(float angularDamping) = 0;

        virtual void SetBodyFlags(BodyDefinition2D::BodyFlags flags) = 0;

        inline void SetAllowedToSleep(bool isAllowedToSleep) const {
            SetBodyFlags((_flags & ~BodyDefinition2D::BodyFlags::AllowSleep) | (isAllowedToSleep ? BodyDefinition2D::BodyFlags::AllowSleep : 0));
        }

        inline void SetUsingConstantCollisionDetection(bool isUsingConstantCollisionDetection) const {
            SetBodyFlags((_flags & ~BodyDefinition2D::BodyFlags::UseConstantCollisionDetection) | (isUsingConstantCollisionDetection ? BodyDefinition2D::BodyFlags::UseConstantCollisionDetection : 0));
        }

        inline void SetEnabled(bool isEnabled) const {
            SetBodyFlags((_flags & ~BodyDefinition2D::BodyFlags::Enabled) | (isEnabled ? BodyDefinition2D::BodyFlags::Enabled : 0));
        }

        inline void SetApplyingWorldGravity(bool isApplyingWorldGravity) const {
            SetBodyFlags((_flags & ~BodyDefinition2D::BodyFlags::UseWorldGravity) | (isApplyingWorldGravity ? BodyDefinition2D::BodyFlags::UseWorldGravity : 0));
        }
    };
}

#endif // !NOVELRT_PHYSICS_RIGIDBODY2D_H