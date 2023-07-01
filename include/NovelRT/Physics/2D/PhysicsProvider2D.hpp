// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#pragma once

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    class PhysicsProvider2D : public PhysicsProvider
    {
    public:
        [[nodiscard]] bool Supports2D() const noexcept final
        {
            return true;
        }

        /**
         * @brief
         * Creates an instance of a 2 dimensional physics world.
         *
         * @details
         *
         *
         * @return std::unique_ptr<PhysicsWorld2D> The instance of a 2 dimensional physics world.
         */
        [[nodiscard]] virtual std::unique_ptr<PhysicsWorld2D> CreateWorld() = 0;
    };
}