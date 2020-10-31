// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "../NovelRTInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/Utilities/NovelRTMisc.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include <NovelRT.h>

#ifdef __cplusplus
extern "C" {
#endif

const char* NovelRT_getExecutablePath() {
  const char* path = NovelRT::Utilities::Misc::getExecutablePath().string().c_str();
  return path;
}

int32_t NovelRT_getExecutableDirPath(const char** path) {
  if (path == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  std::string cppPath = NovelRT::Utilities::Misc::getExecutableDirPath().string();
  char* heapPath = new char[cppPath.length() + 1];
  strcpy_s(heapPath, cppPath.length()+1,  cppPath.c_str()); //TODO: This will fail on Linux
  *path = heapPath;
  return NOVELRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif