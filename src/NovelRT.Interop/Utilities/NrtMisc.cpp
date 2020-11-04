// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "../NrtInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/Utilities/NrtMisc.h"
#include "NovelRT.Interop/NrtInteropUtils.h"
#include <NovelRT.h>

#ifdef __cplusplus
extern "C" {
#endif

const char* Nrt_getExecutablePath() {
  const char* path = NovelRT::Utilities::Misc::getExecutablePath().string().c_str();
  return path;
}

int32_t Nrt_getExecutableDirPath(const char** path) {
  if (path == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  std::string cppPath = NovelRT::Utilities::Misc::getExecutableDirPath().string();
  char* heapPath = new char[cppPath.length() + 1];
  strcpy_s(heapPath, cppPath.length()+1,  cppPath.c_str()); //TODO: This will fail on Linux
  *path = heapPath;
  return NRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif