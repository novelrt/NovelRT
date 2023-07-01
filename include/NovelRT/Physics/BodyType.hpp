// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PHYSICS_BODYTYPE_H
#define NOVELRT_PHYSICS_BODYTYPE_H

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics
{
    /**
     * @brief
     * The type associated with a rigidbody.
     */
    enum class BodyType
    {
        /**
         * @brief
         * A rigibody that is not meant to move, for example: scenery.
         */
        Static,

        /**
         * @brief
         * A rigidbody that gets moved around programmatically, for example: player characters.
         */
        Kinematic,

        /**
         * @brief
         * A rigidbody that gets fully simulated by the physics system.
         */
        Dynamic
    };
}

#endif // !NOVELRT_PHYSICS_BODYTYPE_H