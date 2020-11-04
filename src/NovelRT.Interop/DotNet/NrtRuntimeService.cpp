// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "../NrtInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/NrtInteropUtils.h"
#include "NovelRT.Interop/DotNet/NrtRuntimeService.h"
#include "NovelRT.h"

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
        return NRT_FAILURE_UNKOWN;
    }

    NovelRT::DotNet::RuntimeService* cService = reinterpret_cast<NovelRT::DotNet::RuntimeService*>(service);
    cService->~RuntimeService();
    return NRT_SUCCESS;
}

// NrtResult Nrt_RuntimeService_getFunction(NrtRuntimeService service, NrtRuntimeFunction* outputFunction, const char_t* assemblyName, const char_t* typeName, const char_t* methodName, const char_t* delegateTypeName) {
//     if (service == nullptr || outputFunction == nullptr) {
//         if (errorMessage != nullptr) {
//             *errorMessage = Nrt_getErrMsgIsNullptr();
//         }
//         return NOVELRT_FAILURE;
//     }

//     NovelRT::DotNet::RuntimeService* cService = reinterpret_cast<NovelRT::DotNet::RuntimeService*>(service);
//     auto func = cService->getFunction(assemblyName, typeName, methodName, delegateTypeName);
//     return NOVELRT_SUCCESS;
// }

NrtResult Nrt_RuntimeService_initialise(NrtRuntimeService service) {
    if (service == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    NovelRT::DotNet::RuntimeService* cService = reinterpret_cast<NovelRT::DotNet::RuntimeService*>(service);
    cService->initialise();
    return NRT_SUCCESS;
}

NrtResult Nrt_RuntimeService_tearDown(NrtRuntimeService service) {
    if (service == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    NovelRT::DotNet::RuntimeService* cService = reinterpret_cast<NovelRT::DotNet::RuntimeService*>(service);
    cService->tearDown();
    return NRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif
