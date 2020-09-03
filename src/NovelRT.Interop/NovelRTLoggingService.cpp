// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.Interop/NovelRTLoggingService.h"
#include "NovelRT.Interop/NovelRTLogLevel.h"
#include "NovelRT.h"

NovelRTLoggingService NovelRT_LoggingService_create() {
    NovelRT::LoggingService* service = new NovelRT::LoggingService();
    return reinterpret_cast<NovelRTLoggingService&>(service);
}

NovelRTLoggingService NovelRT_LoggingService_createCustomTitle(const char* core) {
    NovelRT::LoggingService* service = new NovelRT::LoggingService(core);
    return reinterpret_cast<NovelRTLoggingService&>(service);
}

NovelRTLoggingService NovelRT_LoggingService_createCustomTitleAndLevel(const char* core, NovelRTLogLevel level) {
    NovelRT::LoggingService* service = new NovelRT::LoggingService(core, static_cast<NovelRT::LogLevel>(level));
    return reinterpret_cast<NovelRTLoggingService&>(service);
}

NovelRTResult NovelRT_LoggingService_log(NovelRTLoggingService service, const char* message, NovelRTLogLevel level, const char** errorMessage) {
    if (service == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    NovelRT::LoggingService* cService = reinterpret_cast<NovelRT::LoggingService*>(service);
    cService->log(message, static_cast<NovelRT::LogLevel>(level));

    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_LoggingService_logInfoLine(NovelRTLoggingService service, const char* message, const char** errorMessage) {
    if (service == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    NovelRT::LoggingService* cService = reinterpret_cast<NovelRT::LoggingService*>(service);
    cService->logInfoLine(message);

    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_LoggingService_logErrorLine(NovelRTLoggingService service, const char* message, const char** errorMessage) {
    if (service == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    NovelRT::LoggingService* cService = reinterpret_cast<NovelRT::LoggingService*>(service);
    cService->logErrorLine(message);

    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_LoggingService_logWarningLine(NovelRTLoggingService service, const char* message, const char** errorMessage) {
    if (service == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    NovelRT::LoggingService* cService = reinterpret_cast<NovelRT::LoggingService*>(service);
    cService->logWarningLine(message);

    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_LoggingService_logDebugLine(NovelRTLoggingService service, const char* message, const char** errorMessage) {
    if (service == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    NovelRT::LoggingService* cService = reinterpret_cast<NovelRT::LoggingService*>(service);
    cService->logDebugLine(message);

    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_LoggingService_logInternal(NovelRTLoggingService service, const char* message, NovelRTLogLevel level, const char** errorMessage) {
    if (service == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    NovelRT::LoggingService* cService = reinterpret_cast<NovelRT::LoggingService*>(service);
    cService->logInternal(message, static_cast<NovelRT::LogLevel>(level));

    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_LoggingService_setLogLevel(NovelRTLoggingService service, NovelRTLogLevel level, const char** errorMessage) {
    if (service == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    NovelRT::LoggingService* cService = reinterpret_cast<NovelRT::LoggingService*>(service);
    cService->setLogLevel(static_cast<NovelRT::LogLevel>(level));

    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_LoggingService_throwIfNullPtr(NovelRTLoggingService service, void* object, const char* exceptionMessage, const char** errorMessage) {
    if (service == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    NovelRT::LoggingService* cService = reinterpret_cast<NovelRT::LoggingService*>(service);
    cService->throwIfNullPtr(object, exceptionMessage);
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_LoggingService_throwIfNotZero(NovelRTLoggingService service, int32_t error, const char* exceptionMessage, const char** errorMessage) {
    if (service == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    NovelRT::LoggingService* cService = reinterpret_cast<NovelRT::LoggingService*>(service);
    cService->throwIfNotZero(error, exceptionMessage);

    return NOVELRT_SUCCESS;
}
