#ifndef NOVELRT_PHYSICS_PHYSICS2D_POLYGONCOLLISIONFIXTURE2D_H
#define NOVELRT_PHYSICS_PHYSICS2D_POLYGONCOLLISIONFIXTURE2D_H

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    class PolygonCollisionFixture2D : public CollisionFixture2D
    {
        [[nodiscard]] virtual NovelRT::Utilities::Misc::Span<const NovelRT::Maths::GeoVector2F> GetVertices() = 0;

        virtual void SetVertices(NovelRT::Utilities::Misc::Span<const NovelRT::Maths::GeoVector2F> vertices) = 0;
    };

} // namespace NovelRT::Physics::Physics2D

#endif // NOVELRT_PHYSICS_PHYSICS2D_POLYGONCOLLISIONFIXTURE2D_H