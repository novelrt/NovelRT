// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "../NrtInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/Windowing/NrtWindowingService.h"
#include "NovelRT.Interop/NrtInteropUtils.h"
#include <NovelRT.h>
#include <stdint.h>
#include <list>

std::list<std::shared_ptr<NovelRT::Windowing::WindowingService>> _windowingServiceCollection;

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

NrtWindowingService Nrt_WindowingService_create() {
  _windowingServiceCollection.push_back(std::make_shared<Windowing::WindowingService>(Windowing::WindowingService()));
  return reinterpret_cast<NrtWindowingService>(_windowingServiceCollection.back().get());
}

NrtResult Nrt_WindowingService_initialiseWindow(NrtWindowingService service, int displayNumber, const char* windowTitle, int32_t transparencyEnabled) {
  auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);
  if (servicePtr == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  servicePtr->initialiseWindow(displayNumber, windowTitle, static_cast<bool>(transparencyEnabled));
  return NRT_SUCCESS;
}

NrtResult Nrt_WindowingService_tearDown(NrtWindowingService service) {
  auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);
  if (servicePtr == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  servicePtr->tearDown();
  return NRT_SUCCESS;
}

NrtResult Nrt_WindowingService_getWindowTitle(NrtWindowingService service, const char** windowTitle) {
  auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);
  if (servicePtr == nullptr || windowTitle == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  *windowTitle = servicePtr->getWindowTitle().c_str();
  return NRT_SUCCESS;
}

NrtResult Nrt_WindowingService_setWindowTitle(NrtWindowingService service, const char* value) {
  auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);
  if (servicePtr == nullptr || value == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  servicePtr->setWindowTitle(value);
  return NRT_SUCCESS;
}

NrtResult Nrt_WindowingService_setWindowSize(NrtWindowingService service, NrtGeoVector2F value) {
  auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);
  if (servicePtr == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  servicePtr->setWindowSize(*reinterpret_cast<const Maths::GeoVector2F*>(&value));
  return NRT_SUCCESS;
}

NrtResult Nrt_WindowingService_getWindowSize(NrtWindowingService service, NrtGeoVector2F* output) {
  auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);
  if (servicePtr == nullptr || output == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  auto vector = servicePtr->getWindowSize();
  *output = reinterpret_cast<NrtGeoVector2F&>(vector);
  return NRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif
