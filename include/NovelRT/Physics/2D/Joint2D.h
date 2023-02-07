// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PHYSICS_PHYSICS2D_JOINT2D_H
#define NOVELRT_PHYSICS_PHYSICS2D_JOINT2D_H

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    class Joint2D
    {
    protected:
        RigidBody2D* _primaryBody;
        RigidBody2D* _secondaryBody;
        NovelRT::Maths::GeoVector2F _primaryAnchorOffset;
        NovelRT::Maths::GeoVector2F _secondaryAnchorOffset;
        float _breakForce;
        float _breakTorque;
        bool _collideConnectedBodies;

    public:
        [[nodiscard]] inline RigidBody2D* const GetPrimaryBody() const noexcept
        {
            return _primaryBody;
        }

        [[nodiscard]] inline RigidBody2D* const GetSecondaryBody() const noexcept
        {
            return _secondaryBody;
        }
        
        [[nodiscard]] inline NovelRT::Maths::GeoVector2F GetPrimaryAnchorOffset() const noexcept
        {
            return _primaryAnchorOffset;
        }

        [[nodiscard]] inline NovelRT::Maths::GeoVector2F GetSecondaryAnchorOffset() const noexcept
        {
            return _secondaryAnchorOffset;
        }

        [[nodiscard]] inline float GetBreakForce() const noexcept
        {
            return _breakForce;
        }

        [[nodiscard]] inline float GetBreakTorque() const noexcept
        {
            return _breakTorque;
        }

        [[nodiscard]] inline bool GetCollideConnectedBodies() const noexcept
        {
            return _collideConnectedBodies;
        }

        [[nodiscard]] virtual JointType GetJointType() = 0;

        virtual void SetPrimaryBody(RigidBody2D* body) = 0;

        virtual void SetSecondaryBody(RigidBody2D* body) = 0;

        virtual void SetPrimaryAnchorOffset(NovelRT::Maths::GeoVector2F offset) = 0;

        virtual void SetSecondaryAnchorOffset(NovelRT::Maths::GeoVector2F offset) = 0;

        virtual void SetBreakForce(float required) = 0;

        virtual void SetBreakTorque(float required) = 0;

        virtual void SetCollideConnectedBodies(bool shouldCollide) = 0;
    };
}

#endif // !NOVELRT_PHYSICS_PHYSICS2D_JOINT2D_H