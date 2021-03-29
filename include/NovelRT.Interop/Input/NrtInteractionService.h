// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_INPUT_INTERACTIONSERVICE_H
#define NOVELRT_INTEROP_INPUT_INTERACTIONSERVICE_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtInteractionServiceHandle Nrt_InteractionService_create(const NrtWindowingServiceHandle windowingService);
    NrtResult Nrt_InteractionService_consumePlayerInput(const NrtInteractionServiceHandle service);
    NrtResult Nrt_InteractionService_createBasicInteractionRect(const NrtInteractionServiceHandle service,
                                                                const NrtTransform transform,
                                                                int32_t layer,
                                                                NrtBasicInteractionRectHandle* outputRect);
    NrtResult Nrt_InteractionService_executeClickedInteractable(const NrtInteractionServiceHandle service);
    NrtResult Nrt_InteractionService_setScreenSize(const NrtInteractionServiceHandle service, NrtGeoVector2F value);
    NrtResult Nrt_InteractionService_getKeyState(const NrtInteractionServiceHandle service,
                                                 NrtKeyCode value,
                                                 NrtKeyStateFrameChangeLogHandle* output);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_INPUT_INTERACTIONSERVICE_H
