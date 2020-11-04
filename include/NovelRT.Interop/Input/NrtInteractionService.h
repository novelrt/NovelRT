// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_INPUT_INTERACTIONSERVICE_H
#define NOVELRT_INTEROP_INPUT_INTERACTIONSERVICE_H

#include "../Windowing/NrtWindowingService.h"
#include "../NrtTransform.h"
#include "../Maths/NrtGeoVector2F.h"
#include "../NrtInteropUtils.h"
#include "NrtKeyCode.h"
#include "NrtKeyStateFrameChangeLog.h"
#include "NrtBasicInteractionRect.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct InteractionServiceHandle* NrtInteractionService;

NrtInteractionService Nrt_InteractionService_create(const NrtWindowingService windowingService);
NrtResult Nrt_InteractionService_consumePlayerInput(const NrtInteractionService service);
NrtResult Nrt_InteractionService_createBasicInteractionRect(const NrtInteractionService service, const NrtTransform transform, int layer, NrtBasicInteractionRect* outputRect);
NrtResult Nrt_InteractionService_executeClickedInteractable(const NrtInteractionService service);
NrtResult Nrt_InteractionService_setScreenSize(const NrtInteractionService service, NrtGeoVector2F value);
NrtResult Nrt_InteractionService_getKeyState(const NrtInteractionService service, NrtKeyCode value, NrtKeyStateFrameChangeLog* output);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_INPUT_INTERACTIONSERVICE_H