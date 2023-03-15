// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PHYSICS_PHYSICS2D_SLIDINGJOINT2D_H
#define NOVELRT_PHYSICS_PHYSICS2D_SLIDINGJOINT2D_H

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    /**
     * @brief
     * A joint whose movement is restricted to a single axis, often called a prismatic joint.
     *
     * @details
     * A sliding joint can move along a single axis, rather than rotating around it. It can be useful for situations, like sliding doors.
     */
    class SlidingJoint2D : public Joint2D
    {
    protected:
        float _motorSpeed;
        float _maximumMotorForce;
        float _lowerTranslationLimit;
        float _upperTranslationLimit;
        float _breakTorque;
        bool _useTranslationLimits;
        bool _useMotor;

    public:
        [[nodiscard]] inline float GetMotorSpeed() const noexcept
        {
            return _motorSpeed;
        }

        [[nodiscard]] inline float GetMaximumMotorForce() const noexcept
        {
            return _maximumMotorForce;
        }

        [[nodiscard]] inline float GetLowerTranslationLimit() const noexcept
        {
            return _lowerTranslationLimit;
        }

        [[nodiscard]] inline float GetUpperTranslationLimit() const noexcept
        {
            return _upperTranslationLimit;
        }

        [[nodiscard]] inline float GetBreakTorque() const noexcept
        {
            return _breakTorque;
        }

        [[nodiscard]] inline bool GetAreTranslationLimitsUsed() const noexcept
        {
            return _useTranslationLimits;
        }

        [[nodiscard]] inline bool GetIsMotorUsed() const noexcept
        {
            return _useMotor;
        }

        virtual void SetMotorSpeed(float motorSpeed) = 0;

        virtual void SetMaximumMotorForce(float maximumMotorForce) = 0;

        virtual void SetLowerTranslationLimit(float lowerTranslationLimit) = 0;

        virtual void SetUpperTranslationLimit(float upperTranslationLimit) = 0;

        virtual void SetBreakTorque(float breakTorque) = 0;

        virtual void SetAreTranslationLimitsUsed(bool useTranslationLimits) = 0;

        virtual void SetIsMotorUsed(bool useMotor) = 0;
    };
}

#endif // !NOVELRT_PHYSICS_PHYSICS2D_SLIDINGJOINT2D_H