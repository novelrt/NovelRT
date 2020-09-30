
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.Interop/Graphics/NovelRTCamera.h"
#include "NovelRT.h"
#include <list>
#include "NovelRT.Interop/NovelRTInteropUtils.h"

using namespace NovelRT::Graphics;
using namespace NovelRT::Maths;

#ifdef __cplusplus
extern "C" {
#endif

int32_t NovelRT_ImageRect_getTransform(NovelRTImageRect rect, NovelRTTransform* outputTransform, const char** errorMessage) {
    if (rect == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }

        return NOVELRT_FAILURE;
    }

    ImageRect* imageRectPtr = reinterpret_cast<ImageRect*>(rect);
    Transform cppTransform = imageRectPtr->transform();
    *outputTransform = *reinterpret_cast<NovelRTTransform*>(cppTransform);

    return NOVELRT_SUCCESS;
}

//int32_t NovelRT_ImageRect_setTransform(NovelRTImageRect rect, NovelRTTransform inputTransform, const char** errorMessage) {}
//int32_t NovelRT_ImageRect_getLayer(NovelRTImageRect rect, int32_t* outputLayer, const char** errorMessage) {}
//int32_t NovelRT_ImageRect_setLayer(NovelRTImageRect rect, int32_t inputLayer, const char** errorMessage) {}
//int32_t NovelRT_ImageRect_getActive(NovelRTImageRect rect, int32_t* outputBool, const char** errorMessage) {}
//int32_t NovelRT_ImageRect_setActive(NovelRTImageRect rect, int32_t inputBool, const char** errorMessage) {}
//int32_t NovelRT_ImageRect_executeObjectBehaviour(NovelRTImageRect rect, const char** errorMessage) {}
//int32_t NovelRT_ImageRect_getTexture(NovelRTImageRect rect, NovelRTTexture* outputTexture, const char** errorMessage) {}
//int32_t NovelRT_ImageRect_setTexture(NovelRTImageRect rect, NovelRTTexture inputTexture, const char** errorMessage) {}
//int32_t NovelRT_ImageRect_getColourTint(NovelRTImageRect rect, NovelRTRGBAConfig* outputColourTint, const char** errorMessage) {}
//int32_t NovelRT_ImageRect_setColourTint(NovelRTImageRect rect, NovelRTRGBAConfig inputColourTint, const char** errorMessage) {}

#ifdef __cplusplus
}
#endif