// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#pragma once

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    class SpringJoint2D : public Joint2D
    {
    protected:
        float _minimumLength;
        float _maximumLength;
        float _restLength;
        float _stiffness;
        float _damping;

    public:
        [[nodiscard]] inline float GetMinimumLength() const noexcept
        {
            return _minimumLength;
        }

        [[nodiscard]] inline float GetMaximumLength() const noexcept
        {
            return _maximumLength;
        }

        [[nodiscard]] inline float GetRestLength() const noexcept
        {
            return _restLength;
        }

        [[nodiscard]] inline float GetStiffness() const noexcept
        {
            return _stiffness;
        }

        [[nodiscard]] inline float GetDamping() const noexcept
        {
            return _damping;
        }

        virtual void SetMinimumLength(float minimumLength) = 0;

        virtual void SetMaximumLength(float maximumLength) = 0;

        virtual void SetRestLength(float restLength) = 0;

        virtual void SetStiffness(float stiffness) = 0;

        virtual void SetDamping(float damping) = 0;
    };
}