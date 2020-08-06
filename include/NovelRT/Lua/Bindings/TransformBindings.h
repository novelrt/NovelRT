// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_TRANSFORM_BINDINGS_H
#define NOVELRT_TRANSFORM_BINDINGS_H

#endif //NOVELRT_TRANSFORM_BINDINGS_H

#include "NovelRT.h"

class TransformBindings {
public:
    static float getRotation(NovelRT::Transform* t) {
        return t->rotation();
    }

    static void setRotation(NovelRT::Transform* t, float rotation) {
        t->rotation() = rotation;
    }
private:
    TransformBindings() {}
};