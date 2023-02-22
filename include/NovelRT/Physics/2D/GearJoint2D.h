// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PHYSICS_PHYSICS2D_GEARJOINT2D_H
#define NOVELRT_PHYSICS_PHYSICS2D_GEARJOINT2D_H

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    class GearJoint2D : public Joint2D
    {
    protected:
        Joint2D* _primaryJoint;
        Joint2D* _secondaryJoint;
        float _ratio;

    public:
        [[nodiscard]] inline Joint2D* GetPrimaryJoint()
        {
            return _primaryJoint;
        }

        [[nodiscard]] inline Joint2D* GetSecondaryJoint()
        {
            return _secondaryJoint;
        }

        [[nodiscard]] inline float GetRatio()
        {
            return _ratio;
        }

        virtual void SetPrimaryJoint(Joint2D* primaryJoint) = 0;

        virtual void SetSecondaryJoint(Joint2D* secondaryJoint) = 0;

        virtual void SetRatio(float ratio) = 0;
    };
}

#endif // !NOVELRT_PHYSICS_PHYSICS2D_GEARJOINT2D_H