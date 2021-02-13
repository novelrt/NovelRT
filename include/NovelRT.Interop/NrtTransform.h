// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_TRANSFORM_H
#define NOVELRT_INTEROP_TRANSFORM_H

#include "Maths/NrtGeoBounds.h"
#include "Maths/NrtGeoVector2F.h"
#include "NrtInteropUtils.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct
    {
        NrtGeoVector2F position;
        NrtGeoVector2F scale;
        float rotation;
    } NrtTransform;

    NrtGeoBounds Nrt_Transform_getAABB(const NrtTransform transform); // TODO: why are these const lol?
    NrtGeoBounds Nrt_Transform_getBounds(const NrtTransform transform);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_TRANSFORM_H
