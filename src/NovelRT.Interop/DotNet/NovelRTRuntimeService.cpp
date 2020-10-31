// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "../NovelRTInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.Interop/DotNet/NovelRTRuntimeService.h"
#include "NovelRT.h"

#ifdef __cplusplus
extern "C" {
#endif

NovelRTRuntimeService NovelRT_RuntimeService_create() {
    NovelRT::DotNet::RuntimeService* service = new NovelRT::DotNet::RuntimeService();
    return reinterpret_cast<NovelRTRuntimeService&>(service);
}

int32_t NovelRT_RuntimeService_destroy(NovelRTRuntimeService service) {
    if (service == nullptr) {
        NovelRT_setErrMsgIsNullptrInternal();
        return NOVELRT_FAILURE;
    }

    NovelRT::DotNet::RuntimeService* cService = reinterpret_cast<NovelRT::DotNet::RuntimeService*>(service);
    cService->~RuntimeService();
    return NOVELRT_SUCCESS;
}

// int32_t NovelRT_RuntimeService_getFunction(NovelRTRuntimeService service, NovelRTRuntimeFunction* outputFunction, const char_t* assemblyName, const char_t* typeName, const char_t* methodName, const char_t* delegateTypeName) {
//     if (service == nullptr || outputFunction == nullptr) {
//         if (errorMessage != nullptr) {
//             *errorMessage = NovelRT_getErrMsgIsNullptr();
//         }
//         return NOVELRT_FAILURE;
//     }

//     NovelRT::DotNet::RuntimeService* cService = reinterpret_cast<NovelRT::DotNet::RuntimeService*>(service);
//     auto func = cService->getFunction(assemblyName, typeName, methodName, delegateTypeName);
//     return NOVELRT_SUCCESS;
// }

int32_t NovelRT_RuntimeService_initialise(NovelRTRuntimeService service) {
    if (service == nullptr) {
        NovelRT_setErrMsgIsNullptrInternal();
        return NOVELRT_FAILURE;
    }

    NovelRT::DotNet::RuntimeService* cService = reinterpret_cast<NovelRT::DotNet::RuntimeService*>(service);
    cService->initialise();
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_RuntimeService_tearDown(NovelRTRuntimeService service) {
    if (service == nullptr) {
        NovelRT_setErrMsgIsNullptrInternal();
        return NOVELRT_FAILURE;
    }

    NovelRT::DotNet::RuntimeService* cService = reinterpret_cast<NovelRT::DotNet::RuntimeService*>(service);
    cService->tearDown();
    return NOVELRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif
