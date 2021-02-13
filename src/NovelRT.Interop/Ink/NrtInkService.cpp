// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ink/NrtInkService.h>
#include <NovelRT.Interop/NrtInteropErrorHandlingInternal.h>
#include <NovelRT.Interop/NrtInteropUtils.h>
#include <NovelRT.h>
#include <list>

using namespace NovelRT;
std::list<std::shared_ptr<DotNet::RuntimeService>> _dotnetServiceCollection;
std::list<std::shared_ptr<Ink::Story>> _storyCollection;

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_InkService_initialise(NrtInkService service)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        Ink::InkService* inkService = reinterpret_cast<Ink::InkService*>(service);
        inkService->initialise();
        return NRT_SUCCESS;
    }

    NrtResult Nrt_InkService_tearDown(NrtInkService service)
    {
        if (service == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        Ink::InkService* inkService = reinterpret_cast<Ink::InkService*>(service);
        inkService->tearDown();
        return NRT_SUCCESS;
    }

    NrtResult Nrt_InkService_createStory(NrtInkService service, const char* jsonString, NrtStory* outputStory)
    {
        if (service == nullptr || outputStory == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        Ink::InkService* inkService = reinterpret_cast<Ink::InkService*>(service);
        std::shared_ptr<Ink::Story> cStory = inkService->createStory(jsonString);
        _storyCollection.push_back(cStory);
        *outputStory = reinterpret_cast<NrtStory>(cStory.get());
        return NRT_SUCCESS;
    }

    NrtResult Nrt_InkService_getRuntimeService(NrtInkService service, NrtRuntimeService* outputRuntimeService)
    {
        if (service == nullptr || outputRuntimeService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        Ink::InkService* inkService = reinterpret_cast<Ink::InkService*>(service);
        _dotnetServiceCollection.push_back(inkService->getRuntimeService());
        *outputRuntimeService = reinterpret_cast<NrtRuntimeService>(_dotnetServiceCollection.back().get());
        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
