// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/DotNet/NrtRuntimeService.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.h>

#include <list>

using namespace NovelRT;
std::list<std::shared_ptr<Ink::InkService>> _inkServiceCollection;

#ifdef __cplusplus
extern "C"
{
#endif

    NrtRuntimeServiceHandle Nrt_RuntimeService_create()
    {
        NovelRT::DotNet::RuntimeService* service = new NovelRT::DotNet::RuntimeService();
        return reinterpret_cast<NrtRuntimeServiceHandle&>(service);
    }

    NrtResult Nrt_RuntimeService_destroy(NrtRuntimeServiceHandle service)
    {
        if (service == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
        }

        NovelRT::DotNet::RuntimeService* cService = reinterpret_cast<NovelRT::DotNet::RuntimeService*>(service);
        cService->~RuntimeService();
        return NRT_SUCCESS;
    }

    NrtResult Nrt_RuntimeService_initialise(NrtRuntimeServiceHandle service)
    {
        if (service == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
        }

        NovelRT::DotNet::RuntimeService* cService = reinterpret_cast<NovelRT::DotNet::RuntimeService*>(service);

        try
        {
            cService->initialise();
        }
        catch (const Exceptions::InitialisationFailureException)
        {
            return Nrt_getInitialisationFailureErrorInternal();
        }
        catch (const Exceptions::FunctionNotFoundException)
        {
            return Nrt_getFunctionNotFoundErrorInternal();
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RuntimeService_tearDown(NrtRuntimeServiceHandle service)
    {
        if (service == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
        }

        NovelRT::DotNet::RuntimeService* cService = reinterpret_cast<NovelRT::DotNet::RuntimeService*>(service);
        cService->tearDown();
        return NRT_SUCCESS;
    }

    NrtResult Nrt_RuntimeService_freeObject(NrtRuntimeServiceHandle service, intptr_t obj)
    {
        if (service == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
        }

        NovelRT::DotNet::RuntimeService* cService = reinterpret_cast<NovelRT::DotNet::RuntimeService*>(service);

        try
        {
            cService->freeObject(obj);
        }
        catch (const Exceptions::InitialisationFailureException)
        {
            return Nrt_getInitialisationFailureErrorInternal();
        }
        catch (const Exceptions::FunctionNotFoundException)
        {
            return Nrt_getFunctionNotFoundErrorInternal();
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RuntimeService_freeString(NrtRuntimeServiceHandle service, const char* str)
    {
        if (service == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
        }

        if (str == nullptr)
        {
            return Nrt_getNullArgumentErrorInternal();
        }

        NovelRT::DotNet::RuntimeService* cService = reinterpret_cast<NovelRT::DotNet::RuntimeService*>(service);

        try
        {
            cService->freeString(str);
        }
        catch (const Exceptions::InitialisationFailureException)
        {
            return Nrt_getInitialisationFailureErrorInternal();
        }
        catch (const Exceptions::FunctionNotFoundException)
        {
            return Nrt_getFunctionNotFoundErrorInternal();
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_RuntimeService_getInkService(NrtRuntimeServiceHandle service, NrtInkServiceHandle* outputInkService)
    {
        if (service == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
        }

        if (outputInkService == nullptr)
        {
            return Nrt_getNullArgumentErrorInternal();
        }

        NovelRT::DotNet::RuntimeService* cService = reinterpret_cast<NovelRT::DotNet::RuntimeService*>(service);

        std::shared_ptr<Ink::InkService> inkServicePtr;
        try
        {
            inkServicePtr = cService->getInkService();
        }
        catch (const Exceptions::InitialisationFailureException)
        {
            return Nrt_getInitialisationFailureErrorInternal();
        }
        catch (const Exceptions::FunctionNotFoundException)
        {
            return Nrt_getFunctionNotFoundErrorInternal();
        }

        _inkServiceCollection.push_back(inkServicePtr);
        *outputInkService = reinterpret_cast<NrtInkServiceHandle>(inkServicePtr.get());
        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
