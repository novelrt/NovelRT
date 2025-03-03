#pragma once

#ifndef NOVELRT_PHYSICS_HPP
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    class CollisionFixture2D
    {
    public:
        [[nodiscard]] virtual NovelRT::Maths::GeoVector2F GetOffset() = 0;

        [[nodiscard]] virtual float GetFriction() = 0;

        [[nodiscard]] virtual float GetRestitution() = 0;

        [[nodiscard]] virtual float GetRestitutionThreshold() = 0;

        [[nodiscard]] virtual float GetDensity() = 0;

        [[nodiscard]] virtual bool IsSensor() = 0;

        virtual void SetOffset(NovelRT::Maths::GeoVector2F offset) = 0;

        virtual void SetFriction(float friction) = 0;

        virtual void SetRestitution(float restitution) = 0;

        virtual void SetRestitutionThreshold(float restitutionThreshold) = 0;

        virtual void SetDensity(float density) = 0;

        virtual void SetIsSensor(bool isSensor) = 0;
    };

} // namespace NovelRT::Physics::Physics2D