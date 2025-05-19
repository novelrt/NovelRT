// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_LOGGINGSERVICE_H
#define NOVELRT_INTEROP_LOGGINGSERVICE_H

#include "NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtLoggingServiceHandle Nrt_LoggingService_create();
    NrtLoggingServiceHandle Nrt_LoggingService_createCustomTitle(const char* core);
    NrtLoggingServiceHandle Nrt_LoggingService_createCustomTitleAndLevel(const char* core, NrtLogLevel level);
    NrtResult Nrt_LoggingService_log(NrtLoggingServiceHandle service, const char* message, NrtLogLevel level);
    NrtResult Nrt_LoggingService_logInfoLine(NrtLoggingServiceHandle service, const char* message);
    NrtResult Nrt_LoggingService_logErrorLine(NrtLoggingServiceHandle service, const char* message);
    NrtResult Nrt_LoggingService_logWarningLine(NrtLoggingServiceHandle service, const char* message);
    NrtResult Nrt_LoggingService_logDebugLine(NrtLoggingServiceHandle service, const char* message);
    NrtResult Nrt_LoggingService_logInternal(NrtLoggingServiceHandle service, const char* message, NrtLogLevel level);
    NrtResult Nrt_LoggingService_setLogLevel(NrtLoggingServiceHandle service, NrtLogLevel level);
    NrtResult Nrt_LoggingService_throwIfNullPtr(NrtLoggingServiceHandle service,
                                                void* object,
                                                const char* exceptionMessage);
    NrtResult Nrt_LoggingService_throwIfNotZero(NrtLoggingServiceHandle service,
                                                int32_t error,
                                                const char* exceptionMessage);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_LOGGINGSERVICE_H
