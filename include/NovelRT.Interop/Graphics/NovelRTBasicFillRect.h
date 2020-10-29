// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_BASICFILLRECT_H
#define NOVELRT_INTEROP_GRAPHICS_BASICFILLRECT_H

#include "../NovelRTTransform.h"
#include "NovelRTRGBAConfig.h"
#include "NovelRTGraphicsTypedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

//base type
int32_t NovelRT_BasicFillRect_getTransform(NovelRTBasicFillRect rect, NovelRTTransform* outputTransform);
int32_t NovelRT_BasicFillRect_setTransform(NovelRTBasicFillRect rect, NovelRTTransform inputTransform);
int32_t NovelRT_BasicFillRect_getLayer(NovelRTBasicFillRect rect, int32_t* outputLayer);
int32_t NovelRT_BasicFillRect_setLayer(NovelRTBasicFillRect rect, int32_t inputLayer);
int32_t NovelRT_BasicFillRect_getActive(NovelRTBasicFillRect rect, int32_t* outputBool);
int32_t NovelRT_BasicFillRect_setActive(NovelRTBasicFillRect rect, int32_t inputBool);
int32_t NovelRT_BasicFillRect_executeObjectBehaviour(NovelRTBasicFillRect rect);

//actual type
int32_t NovelRT_BasicFillRect_getColourConfig(NovelRTBasicFillRect rect, NovelRTRGBAConfig* outputColourConfig);
int32_t NovelRT_BasicFillRect_setColourConfig(NovelRTBasicFillRect rect, NovelRTRGBAConfig inputColourConfig);

int32_t NovelRT_BasicFillRect_getAsRenderObjectPtr(NovelRTBasicFillRect rect, NovelRTRenderObject* outputRenderObject);

#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_GRAPHICS_BASICFILLRECT_H