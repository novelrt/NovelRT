// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PHYSICS_PHYSICSPROVIDER_H
#define NOVELRT_PHYSICS_PHYSICSPROVIDER_H

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics
{
    class PhysicsProvider : public std::enable_shared_from_this<PhysicsProvider>
    {
    private:
        PhysicsProvider() = default;
    public:
        /**
         * @brief
         * Determines if the physics provider supports 2D physics simulations.
         *
         * @retval true if the physics provider supports 2D physics simulations.
         * @retval false if the physics provider does not support 2D physics simulations.
         */
        [[nodiscard]] virtual bool Supports2D() const noexcept
        {
            return false;
        }

        /**
         * @brief
         * Determines if the physics provider supports 3D physics simulations.
         *
         * @retval true if the physics provider supports 3D physics simulations.
         * @retval false if the physics provider does not support 3D physics simulations.
         */
        [[nodiscard]] virtual bool Supports3D() const noexcept
        {
            return false;
        }
    };
}
#endif // !NOVELRT_PHYSICS_PHYSICSPROVIDER_H