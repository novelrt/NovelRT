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
        Maths::GeoMatrix4x4F value = Maths::GeoMatrix4x4F::getDefaultIdentity();

        inline TransformComponent& operator+=(const TransformComponent& other)
        {
            value = other.value * value;
            return *this;
        }
    };


}
#endif // NOVELRT_DEFAULTCOMPONENTTYPES_H
