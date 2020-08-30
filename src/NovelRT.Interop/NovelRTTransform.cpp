// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/Maths/NovelRTGeoVector2F.h"
#include "NovelRT.Interop/Maths/NovelRTGeoBounds.h"
#include "NovelRT.Interop/NovelRTTransform.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include <NovelRT.h>

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

NovelRTGeoBounds NovelRT_Transform_getAABB(const NovelRTTransform transform) {
    const Transform& cTransform = reinterpret_cast<const Transform&>(transform);
    auto aabb = cTransform.getAABB();
    return *reinterpret_cast<NovelRTGeoBounds*>(&aabb);
}

NovelRTGeoBounds NovelRT_Transform_getBounds(const NovelRTTransform transform) {
    const Transform& cTransform = reinterpret_cast<const Transform&>(transform);
    auto bounds = cTransform.getBounds();
    return *reinterpret_cast<NovelRTGeoBounds*>(&bounds);
}

#ifdef __cplusplus
}
#endif

