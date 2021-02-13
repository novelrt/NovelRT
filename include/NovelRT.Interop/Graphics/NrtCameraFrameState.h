// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_CAMERAFRAMESTATE_H
#define NOVELRT_INTEROP_GRAPHICS_CAMERAFRAMESTATE_H

#include "../Maths/NrtGeoMatrix4x4F.h"
#include "NrtGraphicsTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum
    {
        NRT_UNMODIFIED = 0,
        NRT_MODIFIEDINCURRENT = 1,
        NRT_MODIFIEDINLAST = 2
    } NrtCameraFrameState;

#ifdef __cplusplus
}
#endif

#endif //! NOVELRT_INTEROP_GRAPHICS_CAMERAFRAMESTATE_H
