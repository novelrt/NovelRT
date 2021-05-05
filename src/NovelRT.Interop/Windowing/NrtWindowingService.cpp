// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/Windowing/NrtWindowingService.h>
#include <NovelRT.h>

#include <list>

std::list<std::shared_ptr<NovelRT::Windowing::WindowingService>> _windowingServiceCollection;

#ifdef __cplusplus
using namespace NovelRT;
extern "C"
{
#endif

    NrtWindowingServiceHandle Nrt_WindowingService_create()
    {
        _windowingServiceCollection.push_back(
            std::make_shared<Windowing::WindowingService>(Windowing::WindowingService()));
        return reinterpret_cast<NrtWindowingServiceHandle>(_windowingServiceCollection.back().get());
    }

    NrtResult Nrt_WindowingService_initialiseWindow(NrtWindowingServiceHandle service,
                                                    int32_t displayNumber,
                                                    const char* windowTitle,
                                                    NrtWindowMode windowMode,
                                                    int32_t transparencyEnabled)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);

        if (windowTitle == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        servicePtr->initialiseWindow(displayNumber, windowTitle, static_cast<Windowing::WindowMode>(windowMode),
                                     static_cast<bool>(transparencyEnabled));
        return NRT_SUCCESS;
    }

    NrtResult Nrt_WindowingService_tearDown(NrtWindowingServiceHandle service)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);

        servicePtr->tearDown();
        return NRT_SUCCESS;
    }

    const char* Nrt_WindowingService_getWindowTitle(NrtWindowingServiceHandle service)
    {
        auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);
        std::string* title = new std::string(servicePtr->getWindowTitle());
        return title->c_str();
    }

    NrtResult Nrt_WindowingService_setWindowTitle(NrtWindowingServiceHandle service, const char* value)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);

        if (value == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        servicePtr->setWindowTitle(value);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_WindowingService_setWindowSize(NrtWindowingServiceHandle service, NrtGeoVector2F value)
    {
        if (servicePtr == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }
        
        auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);

        servicePtr->setWindowSize(*reinterpret_cast<const Maths::GeoVector2F*>(&value));
        return NRT_SUCCESS;
    }

    NrtGeoVector2F Nrt_WindowingService_getWindowSize(NrtWindowingServiceHandle service)
    {
        auto servicePtr = reinterpret_cast<Windowing::WindowingService*>(service);
        auto vector = servicePtr->getWindowSize();
        return reinterpret_cast<NrtGeoVector2F&>(vector);
    }

#ifdef __cplusplus
}
#endif
