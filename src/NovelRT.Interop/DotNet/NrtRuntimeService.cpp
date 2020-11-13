// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "../NrtInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/NrtInteropUtils.h"
#include "NovelRT.Interop/DotNet/NrtRuntimeService.h"
#include "NovelRT.h"
#include <list>

using namespace NovelRT;
std::list<std::shared_ptr<Ink::InkService>> _inkServiceCollection;

#ifdef __cplusplus
extern "C" {
#endif

NrtRuntimeService Nrt_RuntimeService_create() {
    NovelRT::DotNet::RuntimeService* service = new NovelRT::DotNet::RuntimeService();
    return reinterpret_cast<NrtRuntimeService&>(service);
}

NrtResult Nrt_RuntimeService_destroy(NrtRuntimeService service) {
    if (service == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    NovelRT::DotNet::RuntimeService* cService = reinterpret_cast<NovelRT::DotNet::RuntimeService*>(service);
    cService->~RuntimeService();
    return NRT_SUCCESS;
}

NrtResult Nrt_RuntimeService_initialise(NrtRuntimeService service) {
    if (service == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    NovelRT::DotNet::RuntimeService* cService = reinterpret_cast<NovelRT::DotNet::RuntimeService*>(service);
    cService->initialise();
    return NRT_SUCCESS;
}

NrtResult Nrt_RuntimeService_tearDown(NrtRuntimeService service) {
    if (service == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    NovelRT::DotNet::RuntimeService* cService = reinterpret_cast<NovelRT::DotNet::RuntimeService*>(service);
    cService->tearDown();
    return NRT_SUCCESS;
}

NrtResult Nrt_RuntimeService_freeObject(NrtRuntimeService service, intptr_t obj) {
  if (service == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    NovelRT::DotNet::RuntimeService* cService = reinterpret_cast<NovelRT::DotNet::RuntimeService*>(service);
    cService->freeObject(obj);
    return NRT_SUCCESS;
}

NrtResult Nrt_RuntimeService_freeString(NrtRuntimeService service, const char* str) {
  if (service == nullptr || str == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    NovelRT::DotNet::RuntimeService* cService = reinterpret_cast<NovelRT::DotNet::RuntimeService*>(service);
    cService->freeString(str);
    return NRT_SUCCESS;
}

NrtResult Nrt_RuntimeService_getInkService(NrtRuntimeService service, NrtInkService* outputInkService) {
  if (service == nullptr || outputInkService == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    NovelRT::DotNet::RuntimeService* cService = reinterpret_cast<NovelRT::DotNet::RuntimeService*>(service);
    auto inkServicePtr = cService->getInkService();
    _inkServiceCollection.push_back(inkServicePtr);
    *outputInkService = reinterpret_cast<NrtInkService>(inkServicePtr.get());
    return NRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif
