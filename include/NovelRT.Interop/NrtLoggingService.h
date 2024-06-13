// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_LOGGINGSERVICE_H
#define NOVELRT_INTEROP_LOGGINGSERVICE_H

#include "NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtLoggingServiceHandle Nrt_LoggingService_Create();
    NrtLoggingServiceHandle Nrt_LoggingService_createCustomTitle(const char* core);
    NrtLoggingServiceHandle Nrt_LoggingService_CreateCustomTitleAndLevel(const char* core, NrtLogLevel level);
    NrtResult Nrt_LoggingService_Log(NrtLoggingServiceHandle service, const char* message, NrtLogLevel level);
    NrtResult Nrt_LoggingService_LogInfoLine(NrtLoggingServiceHandle service, const char* message);
    NrtResult Nrt_LoggingService_LogErrorLine(NrtLoggingServiceHandle service, const char* message);
    NrtResult Nrt_LoggingService_LogWarningLine(NrtLoggingServiceHandle service, const char* message);
    NrtResult Nrt_LoggingService_LogDebugLine(NrtLoggingServiceHandle service, const char* message);
    NrtResult Nrt_LoggingService_LogInternal(NrtLoggingServiceHandle service, const char* message, NrtLogLevel level);
    NrtResult Nrt_LoggingService_SetLogLevel(NrtLoggingServiceHandle service, NrtLogLevel level);
    NrtResult Nrt_LoggingService_ThrowIfNullPtr(NrtLoggingServiceHandle service,
                                                void* object,
                                                const char* exceptionMessage);
    NrtResult Nrt_LoggingService_ThrowIfNotZero(NrtLoggingServiceHandle service,
                                                int32_t error,
                                                const char* exceptionMessage);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_LOGGINGSERVICE_H
