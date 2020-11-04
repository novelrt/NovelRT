// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/Maths/NrtGeoVector2F.h"
#include "NovelRT.Interop/Maths/NrtGeoBounds.h"
#include "NovelRT.Interop/NrtTransform.h"
#include "NovelRT.Interop/NrtInteropUtils.h"
#include <NovelRT.h>

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

NrtGeoBounds Nrt_Transform_getAABB(const NrtTransform transform) {
    const Transform& cTransform = *reinterpret_cast<const Transform*>(&transform);
    auto aabb = cTransform.getAABB();
    return *reinterpret_cast<NrtGeoBounds*>(&aabb);
}

NrtGeoBounds Nrt_Transform_getBounds(const NrtTransform transform) {
    const Transform& cTransform = *reinterpret_cast<const Transform*>(&transform);
    auto bounds = cTransform.getBounds();
    return *reinterpret_cast<NrtGeoBounds*>(&bounds);
}

#ifdef __cplusplus
}
#endif

