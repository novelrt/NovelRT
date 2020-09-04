// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/Windowing/NovelRTWindowingService.h"
#include "NovelRT.Interop/NovelRTTransform.h"
#include "NovelRT.Interop/Maths/NovelRTGeoVector2F.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.Interop/Input/NovelRTKeyCode.h"
#include "NovelRT.Interop/Input/NovelRTKeyStateFrameChangeLog.h"
#include "NovelRT.Interop/Input/NovelRTBasicInteractionRect.h"
#ifndef NOVELRT_INTEROP_INPUT_INTERACTIONSERVICE_H
#define NOVELRT_INTEROP_INPUT_INTERACTIONSERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct InteractionServiceHandle* NovelRTInteractionService;

NovelRTInteractionService NovelRT_InteractionService_create(const NovelRTWindowingService windowingService);
int32_t NovelRT_InteractionService_consumePlayerInput(const NovelRTInteractionService service, const char** errorMessage);
int32_t NovelRT_InteractionService_createBasicInteractionRect(const NovelRTInteractionService service, const NovelRTTransform transform, int layer, NovelRTBasicInteractionRect* outputRect, const char** errorMessage);
int32_t NovelRT_InteractionService_executeClickedInteractable(const NovelRTInteractionService service, const char** errorMessage);
int32_t NovelRT_InteractionService_setScreenSize(const NovelRTInteractionService service, NovelRTGeoVector2F value, const char** errorMessage);
int32_t NovelRT_InteractionService_getKeyState(const NovelRTInteractionService service, NovelRTKeyCode value, NovelRTKeyStateFrameChangeLog* output, const char** errorMessage);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_INPUT_INTERACTIONSERVICE_H