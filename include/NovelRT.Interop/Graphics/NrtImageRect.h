// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_IMAGERECT_H
#define NOVELRT_INTEROP_GRAPHICS_IMAGERECT_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtTransform Nrt_ImageRect_getTransform(NrtImageRectHandle rect);
    NrtResult Nrt_ImageRect_setTransform(NrtImageRectHandle rect, NrtTransform inputTransform);
    int32_t Nrt_ImageRect_getLayer(NrtImageRectHandle rect);
    NrtResult Nrt_ImageRect_setLayer(NrtImageRectHandle rect, int32_t inputLayer);
    NrtBool Nrt_ImageRect_getActive(NrtImageRectHandle rect);
    NrtResult Nrt_ImageRect_setActive(NrtImageRectHandle rect, NrtBool inputBool);
    NrtResult Nrt_ImageRect_executeObjectBehaviour(NrtImageRectHandle rect);
    NrtResult Nrt_ImageRect_getTexture(NrtImageRectHandle rect, NrtTextureHandle* outputTexture);
    NrtResult Nrt_ImageRect_setTexture(NrtImageRectHandle rect, NrtTextureHandle inputTexture);
    NrtResult Nrt_ImageRect_getColourTint(NrtImageRectHandle rect, NrtRGBAConfigHandle* outputColourTint);
    NrtResult Nrt_ImageRect_setColourTint(NrtImageRectHandle rect, NrtRGBAConfigHandle inputColourTint);

    NrtResult Nrt_ImageRect_getAsRenderObjectPtr(NrtImageRectHandle rect, NrtRenderObjectHandle* outputRenderObject);
    NrtResult Nrt_ImageRect_destroy(NrtImageRectHandle rect);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_GRAPHICS_IMAGERECT_H
