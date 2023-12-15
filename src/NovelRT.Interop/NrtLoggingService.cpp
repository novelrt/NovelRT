// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/NrtLoggingService.h>
#include <NovelRT/NovelRT.h>

#ifdef __cplusplus
extern "C"
{
#endif

    NrtLoggingServiceHandle Nrt_LoggingService_Create()
    {
        NovelRT::LoggingService* service = new NovelRT::LoggingService();
        return reinterpret_cast<NrtLoggingServiceHandle&>(service);
    }

    NrtLoggingServiceHandle Nrt_LoggingService_createCustomTitle(const char* core)
    {
        NovelRT::LoggingService* service = new NovelRT::LoggingService(core);
        return reinterpret_cast<NrtLoggingServiceHandle&>(service);
    }

    NrtLoggingServiceHandle Nrt_LoggingService_CreateCustomTitleAndLevel(const char* core, NrtLogLevel level)
    {
        NovelRT::LoggingService* service = new NovelRT::LoggingService(core, static_cast<NovelRT::LogLevel>(level));
        return reinterpret_cast<NrtLoggingServiceHandle&>(service);
    }

    NrtResult Nrt_LoggingService_Log(NrtLoggingServiceHandle service, const char* message, NrtLogLevel level)
    {
        if (service == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        NovelRT::LoggingService* cService = reinterpret_cast<NovelRT::LoggingService*>(service);
        cService->log(message, static_cast<NovelRT::LogLevel>(level));

        return NRT_SUCCESS;
    }

    NrtResult Nrt_LoggingService_LogInfoLine(NrtLoggingServiceHandle service, const char* message)
    {
        if (service == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        NovelRT::LoggingService* cService = reinterpret_cast<NovelRT::LoggingService*>(service);
        cService->logInfoLine(message);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_LoggingService_LogErrorLine(NrtLoggingServiceHandle service, const char* message)
    {
        if (service == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (message == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        NovelRT::LoggingService* cService = reinterpret_cast<NovelRT::LoggingService*>(service);
        cService->logErrorLine(message);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_LoggingService_LogWarningLine(NrtLoggingServiceHandle service, const char* message)
    {
        if (service == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (message == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        NovelRT::LoggingService* cService = reinterpret_cast<NovelRT::LoggingService*>(service);
        cService->logWarningLine(message);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_LoggingService_LogDebugLine(NrtLoggingServiceHandle service, const char* message)
    {
        if (service == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (message == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        NovelRT::LoggingService* cService = reinterpret_cast<NovelRT::LoggingService*>(service);
        cService->logDebugLine(message);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_LoggingService_LogInternal(NrtLoggingServiceHandle service, const char* message, NrtLogLevel level)
    {
        if (service == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (message == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        NovelRT::LoggingService* cService = reinterpret_cast<NovelRT::LoggingService*>(service);
        cService->logInternal(message, static_cast<NovelRT::LogLevel>(level));

        return NRT_SUCCESS;
    }

    NrtResult Nrt_LoggingService_SetLogLevel(NrtLoggingServiceHandle service, NrtLogLevel level)
    {
        if (service == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        NovelRT::LoggingService* cService = reinterpret_cast<NovelRT::LoggingService*>(service);
        cService->setLogLevel(static_cast<NovelRT::LogLevel>(level));

        return NRT_SUCCESS;
    }

    NrtResult Nrt_LoggingService_ThrowIfNullPtr(NrtLoggingServiceHandle service,
                                                void* object,
                                                const char* exceptionMessage)
    {
        if (service == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (exceptionMessage == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        NovelRT::LoggingService* cService = reinterpret_cast<NovelRT::LoggingService*>(service);
        cService->throwIfNullPtr(object, exceptionMessage);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_LoggingService_ThrowIfNotZero(NrtLoggingServiceHandle service,
                                                int32_t error,
                                                const char* exceptionMessage)
    {
        if (service == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (exceptionMessage == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        NovelRT::LoggingService* cService = reinterpret_cast<NovelRT::LoggingService*>(service);
        cService->throwIfNotZero(error, exceptionMessage);

        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
