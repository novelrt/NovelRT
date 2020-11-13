// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_DOTNET_RUNTIMESERVICE_H
#define NOVELRT_INTEROP_DOTNET_RUNTIMESERVICE_H

#include "../NrtInteropUtils.h"

#ifdef __cplusplus
extern "C" {
#endif

  #if defined(WIN32)
    typedef wchar_t char_t;
  #else
    typedef char char_t;
  #endif

  typedef struct RuntimeServiceHandle* NrtRuntimeService;
  typedef void* NrtRuntimeFunction;

  NrtRuntimeService Nrt_RuntimeService_create();
  NrtResult Nrt_RuntimeService_destroy(NrtRuntimeService service);
  //NrtResult Nrt_RuntimeService_getFunction(NrtRuntimeService service, NrtRuntimeFunction* outputFunction, const char_t* assemblyName, const char_t* typeName, const char_t* methodName, const char_t* delegateTypeName);
  NrtResult Nrt_RuntimeService_initialise(NrtRuntimeService service);
  NrtResult Nrt_RuntimeService_tearDown(NrtRuntimeService service);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_DOTNET_RUNTIMESERVICE_H