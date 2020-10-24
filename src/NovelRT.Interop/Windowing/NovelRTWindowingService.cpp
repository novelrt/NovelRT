#include "NovelRT.Interop/Windowing/NovelRTWindowingService.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include <NovelRT.h>
#include <stdint.h>
#include <list>

std::list<std::shared_ptr<NovelRT::Windowing::WindowingService>> _windowingServiceCollection;

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

NovelRTWindowingService NovelRT_WindowingService_create() {
    _windowingServiceCollection.push_back(std::make_shared<Windowing::WindowingService>(Windowing::WindowingService()));
    return reinterpret_cast<NovelRTWindowingService>(_windowingServiceCollection.back().get());
}

int32_t NovelRT_WindowingService_initialiseWindow(NovelRTWindowingService service, int displayNumber, const char* windowTitle, int32_t transparencyEnabled, const char** errorMessage) {
    auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);
    if (servicePtr == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }
    servicePtr->initialiseWindow(displayNumber, windowTitle, static_cast<bool>(transparencyEnabled));
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_WindowingService_tearDown(NovelRTWindowingService service, const char** errorMessage) {
    auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);
    if (servicePtr == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }
    servicePtr->tearDown();
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_WindowingService_getWindowTitle(NovelRTWindowingService service, const char** windowTitle, const char** errorMessage) {
    auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);
    if (servicePtr == nullptr || windowTitle == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }
    *windowTitle = servicePtr->getWindowTitle().c_str();
    return NOVELRT_SUCCESS;
    
}

int32_t NovelRT_WindowingService_setWindowTitle(NovelRTWindowingService service, const char* value, const char** errorMessage) {
    auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);
    if (servicePtr == nullptr || value == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }
    servicePtr->setWindowTitle(value);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_WindowingService_setWindowSize(NovelRTWindowingService service, NovelRTGeoVector2F value, const char** errorMessage) {
    auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);
    if (servicePtr == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }
    servicePtr->setWindowSize(*reinterpret_cast<const Maths::GeoVector2F*>(&value));
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_WindowingService_getWindowSize(NovelRTWindowingService service, NovelRTGeoVector2F* output, const char** errorMessage) {
    auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);
    if (servicePtr == nullptr || output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }
    auto vector = servicePtr->getWindowSize();
    *output = reinterpret_cast<NovelRTGeoVector2F&>(vector);
    return NOVELRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif
