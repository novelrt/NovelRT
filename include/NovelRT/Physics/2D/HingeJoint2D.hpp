// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PHYSICS_PHYSICS2D_HINGEJOINT2D_H
#define NOVELRT_PHYSICS_PHYSICS2D_HINGEJOINT2D_H

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    class HingeJoint2D : public Joint2D
    {
    protected:
        float _lowerAngleLimit;
        float _upperAngleLimit;
        float _motorSpeed;
        float _maxMotorTorque;
        bool _isMotorUsed;

    public:
        [[nodiscard]] inline float GetLowerAngleLimit() const noexcept
        {
            return _lowerAngleLimit;
        }

        [[nodiscard]] inline float GetUpperAngleLimit() const noexcept
        {
            return _upperAngleLimit;
        }

        [[nodiscard]] inline float GetMotorSpeed() const noexcept
        {
            return _motorSpeed;
        }

        [[nodiscard]] inline float GetMaxMotorTorque() const noexcept
        {
            return _maxMotorTorque;
        }

        [[nodiscard]] inline bool GetIsMotorUsed() const noexcept
        {
            return _isMotorUsed;
        }

        virtual void SetLowerAngleLimit(float lowerAngleLimit) = 0;

        virtual void SetUpperAngleLimit(float upperAngleLimit) = 0;

        virtual void SetMotorSpeed(float motorSpeed) = 0;

        virtual void SetMaxMotorTorque(float maxMotorTorque) = 0;

        virtual void SetIsMotorUsed(bool isMotorUsed) = 0;
    };
}

#endif // !NOVELRT_PHYSICS_PHYSICS2D_HINGEJOINT2D_H