// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "../NrtInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/Utilities/NrtMisc.h"
#include "NovelRT.Interop/NrtInteropUtils.h"
#include <NovelRT.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

const char* Nrt_getExecutablePath() {
  const char* path = NovelRT::Utilities::Misc::getExecutablePath().string().c_str();
  return path;
}

// NrtResult Nrt_getExecutableDirPath(const char** path) {
//   if (path == nullptr) {
//     Nrt_setErrMsgIsNullptrInternal();
//     return NRT_FAILURE_NULLPTR_PROVIDED;
//   }

//   std::string cppPath = NovelRT::Utilities::Misc::getExecutableDirPath().string();
//   char* heapPath = new char[cppPath.length() + 1];
//   strcpy_s(heapPath, cppPath.length()+1,  cppPath.c_str());
//   *path = heapPath;
//   return NRT_SUCCESS;
// }

const char* Nrt_getExecutableDirPath() {
  std::string cppPath = NovelRT::Utilities::Misc::getExecutableDirPath().string();
  char* path = new char[cppPath.length() + 1];
  if(strlen(path) < (cppPath.length() + 1)) {
    Nrt_setErrMsgCustomInternal("Could not properly allocate memory for path!");
    return NULL;
  }

  strcpy_s(path, cppPath.length()+1, cppPath.c_str());
  return path;
}

const char* Nrt_appendFilePath(int numberOfArgs, ...) {
  if (numberOfArgs <= 1) {
    Nrt_setErrMsgCustomInternal("Cannot append file path when nothing is being appended!");
    return NULL;
  }

  char* dirMarker = "/";
#if defined(_WIN32) || defined(WIN32)
  dirMarker = "\\";
#endif

  std::string finalString = "";
  va_list args;
  va_start(args, numberOfArgs);

  for(int i = 0; i < numberOfArgs; i++) {
    finalString.append(va_arg(args, const char*));
    if (i < numberOfArgs-1) {
      finalString.append(dirMarker);
    }
  }
  va_end(args);

  char* finalPath = new char[finalString.length() + 1];
  if(strlen(finalPath) < (finalString.length() + 1)) {
    Nrt_setErrMsgCustomInternal("Could not properly allocate memory for path!");
    return NULL;
  }

  strcpy_s(finalPath, finalString.length() + 1, finalString.c_str());
  return finalPath;
}

const char* Nrt_appendText(int numberOfArgs, ...) {
  if (numberOfArgs <= 1) {
    Nrt_setErrMsgCustomInternal("Cannot append text when nothing is being appended!");
    return NULL;
  }

  std::string finalString = "";
  va_list args;
  va_start(args, numberOfArgs);

  for(int i = 0; i < numberOfArgs; i++) {
    finalString.append(va_arg(args, const char*));
  }
  va_end(args);

  char* finalText = new char[finalString.length() + 1];
  if(strlen(finalText) < (finalString.length() + 1)) {
    Nrt_setErrMsgCustomInternal("Could not properly allocate memory for test!");
    return NULL;
  }

  strcpy_s(finalText, finalString.length() + 1, finalString.c_str());
  return finalText;
}

#ifdef __cplusplus
}
#endif
