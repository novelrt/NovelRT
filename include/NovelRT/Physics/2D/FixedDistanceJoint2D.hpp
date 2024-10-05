// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#pragma once

#ifndef NOVELRT_PHYSICS_HPP
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    /**
     * @brief
     * A joint that keeps the anchors of the attached bodies at a set distance.
     */
    class FixedDistanceJoint2D : public Joint2D
    {
    protected:
        float _restLength;
        bool _isOnlyMaxLengthEnforced;

    public:
        [[nodiscard]] inline float GetRestLength() const noexcept
        {
            return _restLength;
        }

        [[nodiscard]] inline bool GetIsOnlyMaxLengthEnforced() const noexcept
        {
            return _isOnlyMaxLengthEnforced;
        }

        virtual void SetRestLength(float restLength) = 0;

        virtual void SetIsOnlyMaxLengthEnforced(bool isOnlyMaxLengthEnforced) = 0;
    };
}