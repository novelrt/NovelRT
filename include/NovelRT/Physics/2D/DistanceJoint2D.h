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

    };
}

#endif // !NOVELRT_PHYSICS_PHYSICS2D_DISTANCEJOINT2D_H