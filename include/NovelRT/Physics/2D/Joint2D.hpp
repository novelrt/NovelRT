// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#pragma once

#ifndef NOVELRT_PHYSICS_HPP
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    // TODO: validate if the current approach for the getters in joints is viable.
    // Will most likely have to do that with an actual implementation.

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
        [[nodiscard]] inline RigidBody2D* GetPrimaryBody() const noexcept
        {
            return _primaryBody;
        }

        [[nodiscard]] inline RigidBody2D* GetSecondaryBody() const noexcept
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

        virtual void SetPrimaryBody(RigidBody2D* body) = 0;

        virtual void SetSecondaryBody(RigidBody2D* body) = 0;

        virtual void SetPrimaryAnchorOffset(NovelRT::Maths::GeoVector2F offset) = 0;

        virtual void SetSecondaryAnchorOffset(NovelRT::Maths::GeoVector2F offset) = 0;

        virtual void SetBreakForce(float required) = 0;

        virtual void SetBreakTorque(float required) = 0;

        virtual void SetCollideConnectedBodies(bool shouldCollide) = 0;
    };
}