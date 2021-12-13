// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_DEFAULTCOMPONENTTYPES_H
#define NOVELRT_DEFAULTCOMPONENTTYPES_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs
{
    struct TransformComponent
    {
        Maths::GeoVector3F positionAndLayer;
        float rotationInEulerAngles;

        inline TransformComponent& operator+=(const TransformComponent& other)
        {
            positionAndLayer += other.positionAndLayer;
            rotationInEulerAngles += other.rotationInEulerAngles;

            if (rotationInEulerAngles > 360)
            {
                rotationInEulerAngles = 0;
            }
            else if (rotationInEulerAngles < 0)
            {
                rotationInEulerAngles = 0;
            }

            return *this;
        }
    };


}
#endif // NOVELRT_DEFAULTCOMPONENTTYPES_H
