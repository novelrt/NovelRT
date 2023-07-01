// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PHYSICS_PHYSICS2D_DISTANCEJOINT2D_H
#define NOVELRT_PHYSICS_PHYSICS2D_DISTANCEJOINT2D_H

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    /**
     * @brief
     * A joint that keeps the anchors of the attached bodies within a certain range of distance.
     */
    class DistanceJoint2D : public Joint2D
    {
    protected:
        float _minLength;
        float _maxLength;
        float _restLength;

    public:
        [[nodiscard]] inline float GetMinLength() const noexcept
        {
            return _minLength;
        }

        [[nodiscard]] inline float GetMaxLength() const noexcept
        {
            return _minLength;
        }

        [[nodiscard]] inline float GetRestLength() const noexcept
        {
            return _minLength;
        }

        virtual void SetMinLength(float minLength) = 0;

        virtual void SetMaxLength(float maxLength) = 0;

        virtual void SetRestLength(float restLength) = 0;
    };
}

#endif // !NOVELRT_PHYSICS_PHYSICS2D_DISTANCEJOINT2D_H