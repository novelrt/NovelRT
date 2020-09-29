
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "../NovelRTTransform.h"
#include "NovelRTRGBAConfig.h"
#include "NovelRTGraphicsTypedefs.h"

#ifndef NOVELRT_INTEROP_GRAPHICS_IMAGERECT_H
#define NOVELRT_INTEROP_GRAPHICS_IMAGERECT_H

#ifdef __cplusplus
extern "C" {
#endif

//base type
int32_t NovelRT_ImageRect_getTransform(NovelRTImageRect rect, NovelRTTransform* outputTransform, const char** errorMessage);
int32_t NovelRT_ImageRect_setTransform(NovelRTImageRect rect, NovelRTTransform inputTransform, const char** errorMessage);
int32_t NovelRT_ImageRect_getLayer(NovelRTImageRect rect, int32_t* outputLayer, const char** errorMessage);
int32_t NovelRT_ImageRect_setLayer(NovelRTImageRect rect, int32_t inputLayer, const char** errorMessage);
int32_t NovelRT_ImageRect_getActive(NovelRTImageRect rect, int32_t* outputBool, const char** errorMessage);
int32_t NovelRT_ImageRect_setActive(NovelRTImageRect rect, int32_t inputBool, const char** errorMessage);
int32_t NovelRT_ImageRect_executeObjectBehaviour(NovelRTImageRect rect, const char** errorMessage);

//actual type


#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_GRAPHICS_IMAGERECT_H