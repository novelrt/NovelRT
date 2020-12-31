// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtInteropErrorHandlingInternal.h>
#include <NovelRT.Interop/NrtInteropUtils.h>
#include <NovelRT.Interop/Windowing/NrtWindowingService.h>
#include <NovelRT.h>
#include <list>
#include <stdint.h>

std::list<std::shared_ptr<NovelRT::Windowing::WindowingService>> _windowingServiceCollection;

#ifdef __cplusplus
using namespace NovelRT;
extern "C"
{
#endif

    NrtWindowingService Nrt_WindowingService_create()
    {
        _windowingServiceCollection.push_back(
            std::make_shared<Windowing::WindowingService>(Windowing::WindowingService()));
        return reinterpret_cast<NrtWindowingService>(_windowingServiceCollection.back().get());
    }

    NrtResult Nrt_WindowingService_initialiseWindow(NrtWindowingService service, int32_t displayNumber,
                                                    const char* windowTitle, int32_t transparencyEnabled)
    {
        auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);
        if (servicePtr == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        servicePtr->initialiseWindow(displayNumber, windowTitle, static_cast<bool>(transparencyEnabled));
        return NRT_SUCCESS;
    }

    NrtResult Nrt_WindowingService_tearDown(NrtWindowingService service)
    {
        auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);
        if (servicePtr == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        servicePtr->tearDown();
        return NRT_SUCCESS;
    }

    const char* Nrt_WindowingService_getWindowTitle(NrtWindowingService service)
    {
        auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);
        std::string* title = new std::string(servicePtr->getWindowTitle());
        return title->c_str();
    }

    NrtResult Nrt_WindowingService_setWindowTitle(NrtWindowingService service, const char* value)
    {
        auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);
        if (servicePtr == nullptr || value == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        servicePtr->setWindowTitle(value);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_WindowingService_setWindowSize(NrtWindowingService service, NrtGeoVector2F value)
    {
        auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);
        if (servicePtr == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        servicePtr->setWindowSize(*reinterpret_cast<const Maths::GeoVector2F*>(&value));
        return NRT_SUCCESS;
    }

    NrtGeoVector2F Nrt_WindowingService_getWindowSize(NrtWindowingService service)
    {
        auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);
        auto vector = servicePtr->getWindowSize();
        return reinterpret_cast<NrtGeoVector2F&>(vector);
    }

#ifdef __cplusplus
}
#endif
