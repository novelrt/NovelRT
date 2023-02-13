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

    };
}

#endif // !NOVELRT_PHYSICS_PHYSICS2D_SLIDINGJOINT2D_H