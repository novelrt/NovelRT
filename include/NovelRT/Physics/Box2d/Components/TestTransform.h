#ifndef NOVELRT_PHYSICS_BOX2D_TESTTRANSFORM_H
#define NOVELRT_PHYSICS_BOX2D_TESTTRANSFORM_H

#include <NovelRT.h>

namespace NovelRT::Physics::Box2d
{
    struct TestTransform{
        NovelRT::Maths::GeoVector2F position;
        float rotation;

        static const TestTransform DeletedTransform;

        TestTransform& operator+=(const TestTransform& rhs){
            position = rhs.position;
            rotation = rhs.rotation;
            return *this;
        }
    };

    const TestTransform TestTransform::DeletedTransform = TestTransform{
        NovelRT::Maths::GeoVector2F(NAN,NAN),
        NAN
    };
}

#endif //NOVELRT_PHYSICS_BOX2D_TESTTRANSFORM_H