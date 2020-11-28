// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.Interop/NrtInteropErrorHandlingInternal.h>
#include <NovelRT.Interop/NrtInteropUtils.h>
#include <NovelRT.Interop/NrtLoggingService.h>
#include <NovelRT.Interop/NrtLogLevel.h>
#include <NovelRT.h>

#ifdef __cplusplus
extern "C" {
#endif

NrtLoggingService Nrt_LoggingService_create() {
  NovelRT::LoggingService* service = new NovelRT::LoggingService();
  return reinterpret_cast<NrtLoggingService&>(service);
}

NrtLoggingService Nrt_LoggingService_createCustomTitle(const char* core) {
  NovelRT::LoggingService* service = new NovelRT::LoggingService(core);
  return reinterpret_cast<NrtLoggingService&>(service);
}

NrtLoggingService Nrt_LoggingService_createCustomTitleAndLevel(const char* core, NrtLogLevel level) {
  NovelRT::LoggingService* service = new NovelRT::LoggingService(core, static_cast<NovelRT::LogLevel>(level));
  return reinterpret_cast<NrtLoggingService&>(service);
}

NrtResult Nrt_LoggingService_log(NrtLoggingService service, const char* message, NrtLogLevel level) {
  if (service == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  NovelRT::LoggingService* cService = reinterpret_cast<NovelRT::LoggingService*>(service);
  cService->log(message, static_cast<NovelRT::LogLevel>(level));

  return NRT_SUCCESS;
}

NrtResult Nrt_LoggingService_logInfoLine(NrtLoggingService service, const char* message) {
  if (service == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  NovelRT::LoggingService* cService = reinterpret_cast<NovelRT::LoggingService*>(service);
  cService->logInfoLine(message);

  return NRT_SUCCESS;
}

NrtResult Nrt_LoggingService_logErrorLine(NrtLoggingService service, const char* message) {
  if (service == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  NovelRT::LoggingService* cService = reinterpret_cast<NovelRT::LoggingService*>(service);
  cService->logErrorLine(message);

  return NRT_SUCCESS;
}

NrtResult Nrt_LoggingService_logWarningLine(NrtLoggingService service, const char* message) {
  if (service == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  NovelRT::LoggingService* cService = reinterpret_cast<NovelRT::LoggingService*>(service);
  cService->logWarningLine(message);

  return NRT_SUCCESS;
}

NrtResult Nrt_LoggingService_logDebugLine(NrtLoggingService service, const char* message) {
  if (service == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  NovelRT::LoggingService* cService = reinterpret_cast<NovelRT::LoggingService*>(service);
  cService->logDebugLine(message);

  return NRT_SUCCESS;
}

NrtResult Nrt_LoggingService_logInternal(NrtLoggingService service, const char* message, NrtLogLevel level) {
  if (service == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  NovelRT::LoggingService* cService = reinterpret_cast<NovelRT::LoggingService*>(service);
  cService->logInternal(message, static_cast<NovelRT::LogLevel>(level));

  return NRT_SUCCESS;
}

NrtResult Nrt_LoggingService_setLogLevel(NrtLoggingService service, NrtLogLevel level) {
  if (service == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  NovelRT::LoggingService* cService = reinterpret_cast<NovelRT::LoggingService*>(service);
  cService->setLogLevel(static_cast<NovelRT::LogLevel>(level));

  return NRT_SUCCESS;
}

NrtResult Nrt_LoggingService_throwIfNullPtr(NrtLoggingService service, void* object, const char* exceptionMessage) {
  if (service == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  NovelRT::LoggingService* cService = reinterpret_cast<NovelRT::LoggingService*>(service);
  cService->throwIfNullPtr(object, exceptionMessage);
  return NRT_SUCCESS;
}

NrtResult Nrt_LoggingService_throwIfNotZero(NrtLoggingService service, int32_t error, const char* exceptionMessage) {
  if (service == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  NovelRT::LoggingService* cService = reinterpret_cast<NovelRT::LoggingService*>(service);
  cService->throwIfNotZero(error, exceptionMessage);

  return NRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif
