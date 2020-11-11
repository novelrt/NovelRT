// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "../NrtInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/Windowing/NrtWindowingService.h"
#include "NovelRT.Interop/Input/NrtInteractionService.h"
#include "NovelRT.h"
#include <list>

std::list<std::shared_ptr<NovelRT::Windowing::WindowingService>> _windowCollection;
std::list<std::shared_ptr<NovelRT::Input::InteractionService>> _interactionServiceCollection;
std::list<std::unique_ptr<NovelRT::Input::BasicInteractionRect>> _rectCollection;

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif


NrtInteractionService Nrt_InteractionService_create(const NrtWindowingService windowingService) {
  _windowCollection.push_back(std::shared_ptr<Windowing::WindowingService>(reinterpret_cast<Windowing::WindowingService*>(windowingService)));
  _interactionServiceCollection.push_back(std::make_shared<Input::InteractionService>(Input::InteractionService(_windowCollection.back())));
  return reinterpret_cast<NrtInteractionService>(_interactionServiceCollection.back().get());
}

NrtResult Nrt_InteractionService_consumePlayerInput(NrtInteractionService service) {
  auto servicePtr = reinterpret_cast<Input::InteractionService*>(service);

  if (servicePtr == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  servicePtr->consumePlayerInput();  
  return NRT_SUCCESS;
}

NrtResult Nrt_InteractionService_executeClickedInteractable(const NrtInteractionService service) {
  auto servicePtr = reinterpret_cast<Input::InteractionService*>(service);

  if (servicePtr == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  servicePtr->executeClickedInteractable();
  return NRT_SUCCESS;
}

NrtResult Nrt_InteractionService_setScreenSize(const NrtInteractionService service, NrtGeoVector2F value) {
  auto servicePtr = reinterpret_cast<Input::InteractionService*>(service);

  if (servicePtr == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  auto vector = reinterpret_cast<Maths::GeoVector2F&>(value);
  servicePtr->setScreenSize(vector);
  return NRT_SUCCESS;
}

NrtResult Nrt_InteractionService_getKeyState(const NrtInteractionService service, NrtKeyCode value, NrtKeyStateFrameChangeLog* output) {
  auto servicePtr = reinterpret_cast<Input::InteractionService*>(service);

  if (servicePtr == nullptr || output == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  auto changelog = servicePtr->getKeyState(reinterpret_cast<Input::KeyCode&>(value));
  *output = reinterpret_cast<NrtKeyStateFrameChangeLog&>(changelog);
  return NRT_SUCCESS;
}

NrtResult Nrt_InteractionService_createBasicInteractionRect(const NrtInteractionService service, const NrtTransform transform, int layer, NrtBasicInteractionRect* outputRect) {
  auto servicePtr = reinterpret_cast<Input::InteractionService*>(service);

  if (servicePtr == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  _rectCollection.push_back(std::unique_ptr<Input::BasicInteractionRect>(servicePtr->createBasicInteractionRect(*reinterpret_cast<const Transform*>(&transform), layer)));
  *outputRect = reinterpret_cast<NrtBasicInteractionRect>(_rectCollection.back().get());
  return NRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif