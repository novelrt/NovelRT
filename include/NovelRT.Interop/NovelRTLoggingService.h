// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.Interop/NovelRTLogLevel.h"

#ifndef NOVELRT_INTEROP_LOGGINGSERVICE_H
#define NOVELRT_INTEROP_LOGGINGSERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct LoggingServiceHandle* NovelRTLoggingService;

  NovelRTLoggingService NovelRT_LoggingService_create();
  NovelRTLoggingService NovelRT_LoggingService_createCustomTitle(const char* core);
  NovelRTLoggingService NovelRT_LoggingService_createCustomTitleAndLevel(const char* core, NovelRTLogLevel level);
  int32_t NovelRT_LoggingService_log(NovelRTLoggingService service, const char* message, NovelRTLogLevel level, const char** errorMessage);
  int32_t NovelRT_LoggingService_logInfoLine(NovelRTLoggingService service, const char* message, const char** errorMessage);
  int32_t NovelRT_LoggingService_logErrorLine(NovelRTLoggingService service, const char* message, const char** errorMessage);
  int32_t NovelRT_LoggingService_logWarningLine(NovelRTLoggingService service, const char* message, const char** errorMessage);
  int32_t NovelRT_LoggingService_logDebugLine(NovelRTLoggingService service, const char* message, const char** errorMessage);
  int32_t NovelRT_LoggingService_logInternal(NovelRTLoggingService service, const char* message, NovelRTLogLevel level, const char** errorMessage);
  int32_t NovelRT_LoggingService_setLogLevel(NovelRTLoggingService service, NovelRTLogLevel level, const char** errorMessage);
  int32_t NovelRT_LoggingService_throwIfNullPtr(NovelRTLoggingService service, void* object, const char* exceptionMessage, const char** errorMessage);
  int32_t NovelRT_LoggingService_throwIfNotZero(NovelRTLoggingService service, int32_t error, const char* exceptionMessage, const char** errorMessage);


#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_LOGGINGSERVICE_H
