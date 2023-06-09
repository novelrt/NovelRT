// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/NrtLoggingService.h>
#include <NovelRT/NovelRT.h>

#ifdef __cplusplus
extern "C"
{
#endif

    NrtLoggingServiceHandle Nrt_LoggingService_create()
    {
        NovelRT::Core::LoggingService* service = new NovelRT::Core::LoggingService();
        return reinterpret_cast<NrtLoggingServiceHandle&>(service);
    }

    NrtLoggingServiceHandle Nrt_LoggingService_createCustomTitle(const char* core)
    {
        NovelRT::Core::LoggingService* service = new NovelRT::Core::LoggingService(core);
        return reinterpret_cast<NrtLoggingServiceHandle&>(service);
    }

    NrtLoggingServiceHandle Nrt_LoggingService_createCustomTitleAndLevel(const char* core, NrtLogLevel level)
    {
        NovelRT::Core::LoggingService* service =
            new NovelRT::Core::LoggingService(core, static_cast<NovelRT::Core::LogLevel>(level));
        return reinterpret_cast<NrtLoggingServiceHandle&>(service);
    }

    NrtResult Nrt_LoggingService_log(NrtLoggingServiceHandle service, const char* message, NrtLogLevel level)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        NovelRT::Core::LoggingService* cService = reinterpret_cast<NovelRT::Core::LoggingService*>(service);
        cService->log(message, static_cast<NovelRT::Core::LogLevel>(level));

        return NRT_SUCCESS;
    }

    NrtResult Nrt_LoggingService_logInfoLine(NrtLoggingServiceHandle service, const char* message)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        NovelRT::Core::LoggingService* cService = reinterpret_cast<NovelRT::Core::LoggingService*>(service);
        cService->logInfoLine(message);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_LoggingService_logErrorLine(NrtLoggingServiceHandle service, const char* message)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (message == nullptr)
        {
            Nrt_setErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        NovelRT::Core::LoggingService* cService = reinterpret_cast<NovelRT::Core::LoggingService*>(service);
        cService->logErrorLine(message);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_LoggingService_logWarningLine(NrtLoggingServiceHandle service, const char* message)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (message == nullptr)
        {
            Nrt_setErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        NovelRT::Core::LoggingService* cService = reinterpret_cast<NovelRT::Core::LoggingService*>(service);
        cService->logWarningLine(message);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_LoggingService_logDebugLine(NrtLoggingServiceHandle service, const char* message)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (message == nullptr)
        {
            Nrt_setErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        NovelRT::Core::LoggingService* cService = reinterpret_cast<NovelRT::Core::LoggingService*>(service);
        cService->logDebugLine(message);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_LoggingService_logInternal(NrtLoggingServiceHandle service, const char* message, NrtLogLevel level)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (message == nullptr)
        {
            Nrt_setErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        NovelRT::Core::LoggingService* cService = reinterpret_cast<NovelRT::Core::LoggingService*>(service);
        cService->logInternal(message, static_cast<NovelRT::Core::LogLevel>(level));

        return NRT_SUCCESS;
    }

    NrtResult Nrt_LoggingService_setLogLevel(NrtLoggingServiceHandle service, NrtLogLevel level)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        NovelRT::Core::LoggingService* cService = reinterpret_cast<NovelRT::Core::LoggingService*>(service);
        cService->setLogLevel(static_cast<NovelRT::Core::LogLevel>(level));

        return NRT_SUCCESS;
    }

    NrtResult Nrt_LoggingService_throwIfNullPtr(NrtLoggingServiceHandle service,
                                                void* object,
                                                const char* exceptionMessage)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (exceptionMessage == nullptr)
        {
            Nrt_setErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        NovelRT::Core::LoggingService* cService = reinterpret_cast<NovelRT::Core::LoggingService*>(service);
        cService->throwIfNullPtr(object, exceptionMessage);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_LoggingService_throwIfNotZero(NrtLoggingServiceHandle service,
                                                int32_t error,
                                                const char* exceptionMessage)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (exceptionMessage == nullptr)
        {
            Nrt_setErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        NovelRT::Core::LoggingService* cService = reinterpret_cast<NovelRT::Core::LoggingService*>(service);
        cService->throwIfNotZero(error, exceptionMessage);

        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
