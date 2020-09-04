// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/NovelRTInteropUtils.h"

#ifndef NOVELRT_INTEROP_DOTNET_RUNTIMESERVICE_H
#define NOVELRT_INTEROP_DOTNET_RUNTIMESERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct RuntimeServiceHandle* NovelRTRuntimeService;
  typedef struct RuntimeFunctionHandle* NovelRTRuntimeFunction;

  NovelRTRuntimeService NovelRT_RuntimeService_create();
  int32_t NovelRT_RuntimeService_destroy(NovelRTRuntimeService service, const char** errorMessage);
//   int32_t NovelRT_RuntimeService_getFunction(NovelRTRuntimeService service, NovelRTRuntimeFunction* outputFunction, const char_t* assemblyName, const char_t* typeName, const char_t* methodName, const char_t* delegateTypeName, const char** errorMessage);
  int32_t NovelRT_RuntimeService_initialise(NovelRTRuntimeService service, const char** errorMessage);
  int32_t NovelRT_RuntimeService_tearDown(NovelRTRuntimeService service, const char** errorMessage);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_DOTNET_RUNTIMESERVICE_H