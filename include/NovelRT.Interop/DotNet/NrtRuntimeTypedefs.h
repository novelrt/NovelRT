// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_DOTNET_RUNTIMETYPEDEFS_H
#define NOVELRT_INTEROP_DOTNET_RUNTIMETYPEDEFS_H

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct RuntimeServiceHandle* NrtRuntimeService;
  typedef struct InkServiceHandle* NrtInkService;
  typedef struct InkStoryHandle* NrtStory;

#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_DOTNET_RUNTIMETYPEDEFS_H
