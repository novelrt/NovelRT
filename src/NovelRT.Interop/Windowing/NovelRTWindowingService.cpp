#include "NovelRT.Interop/Windowing/NovelRTWindowingService.h"
#include <NovelRT.h>
#include <stdint.h>

std::list<std::shared_ptr<Windowing::WindowingService>> _serviceCollection;

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

NovelRTWindowingService WindowingService_create() noexcept {
    _serviceCollection.push_back(std::make_shared<Windowing::WindowingService>(Windowing::WindowingService()));
    return reinterpret_cast<NovelRTWindowingService>(_serviceCollection.back().get());
}

void WindowingService_initialiseWindow(NovelRTWindowingService service, int displayNumber, const char* windowTitle, bool transparencyEnabled) {
    auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);
    servicePtr->initialiseWindow(displayNumber, windowTitle, transparencyEnabled);
}

void WindowingService_tearDown(NovelRTWindowingService service) {
    auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);
    servicePtr->tearDown();
}

const char* WindowingService_getWindowTitle(NovelRTWindowingService service) {
    auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);
    return servicePtr->getWindowTitle().c_str();
}

void WindowingService_setWindowTitle(NovelRTWindowingService service, const char* value) {
    auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);
    servicePtr->setWindowTitle(value);
}

void WindowingService_setWindowSize(NovelRTWindowingService service, const GeoVector2F_t value) {
    auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);
    servicePtr->setWindowSize(*reinterpret_cast<const Maths::GeoVector2<float>*>(&value));
}

GeoVector2F_t WindowingService_getWindowSize(NovelRTWindowingService service) {
    auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);
    auto vector = new Maths::GeoVector2<float>();
    *vector = servicePtr->getWindowSize();
    return reinterpret_cast<GeoVector2F_t&>(vector);
}

#ifdef __cplusplus
}
#endif
