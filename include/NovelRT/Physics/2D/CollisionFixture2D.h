#ifndef NOVELRT_PHYSICS_PHYSICS2D_COLLISIONFIXTURE2D_H
#define NOVELRT_PHYSICS_PHYSICS2D_COLLISIONFIXTURE2D_H

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    class CollisionFixture2D
    {
    private:
        bool _isShared;

    public:
        virtual NovelRT::Maths::GeoVector2F GetOffset() = 0;

        virtual float GetFriction() = 0;

        virtual float GetRestitution() = 0;

        virtual float GetRestitutionThreshold() = 0;

        virtual float GetDensity() = 0;

        virtual bool IsSensor() = 0;

        inline bool IsShared() const noexcept
        {
            return _isShared;
        }

        virtual void SetOffset(NovelRT::Maths::GeoVector2F offset) = 0;

        virtual void SetFriction(float friction) = 0;

        virtual void SetRestitution(float restitution) = 0;

        virtual void SetRestitutionThreshold(float restitutionThreshold) = 0;

        virtual void SetDensity(float density) = 0;

        virtual void SetIsSensor(bool isSensor) = 0;
    };
    
} // namespace NovelRT::Physics::Physics2D

#endif // NOVELRT_PHYSICS_PHYSICS2D_COLLISIONFIXTURE2D_H