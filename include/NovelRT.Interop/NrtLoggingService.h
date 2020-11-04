// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_LOGGINGSERVICE_H
#define NOVELRT_INTEROP_LOGGINGSERVICE_H

#include "NrtInteropUtils.h"
#include "NrtLogLevel.h"

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct LoggingServiceHandle* NrtLoggingService;

  NrtLoggingService Nrt_LoggingService_create();
  NrtLoggingService Nrt_LoggingService_createCustomTitle(const char* core);
  NrtLoggingService Nrt_LoggingService_createCustomTitleAndLevel(const char* core, NrtLogLevel level);
  int32_t Nrt_LoggingService_log(NrtLoggingService service, const char* message, NrtLogLevel level);
  int32_t Nrt_LoggingService_logInfoLine(NrtLoggingService service, const char* message);
  int32_t Nrt_LoggingService_logErrorLine(NrtLoggingService service, const char* message);
  int32_t Nrt_LoggingService_logWarningLine(NrtLoggingService service, const char* message);
  int32_t Nrt_LoggingService_logDebugLine(NrtLoggingService service, const char* message);
  int32_t Nrt_LoggingService_logInternal(NrtLoggingService service, const char* message, NrtLogLevel level);
  int32_t Nrt_LoggingService_setLogLevel(NrtLoggingService service, NrtLogLevel level);
  int32_t Nrt_LoggingService_throwIfNullPtr(NrtLoggingService service, void* object, const char* exceptionMessage);
  int32_t Nrt_LoggingService_throwIfNotZero(NrtLoggingService service, int32_t error, const char* exceptionMessage);


#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_LOGGINGSERVICE_H
