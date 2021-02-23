// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtInteropErrorHandlingInternal.h>
#include <NovelRT.Interop/NrtNovelRunner.h>
#include <NovelRT.h>
#include <list>
#include <stdint.h>

using namespace NovelRT;

std::list<std::shared_ptr<Audio::AudioService>> _audioCollection;
std::list<std::shared_ptr<Input::InteractionService>> _interactionCollection;
std::list<std::shared_ptr<Windowing::WindowingService>> _windowingCollection;
std::list<std::shared_ptr<DotNet::RuntimeService>> _runtimeCollection;
std::list<std::shared_ptr<Graphics::RenderingService>> _rendererCollection;
std::list<std::shared_ptr<DebugService>> _debugServiceCollection;

#ifdef __cplusplus
extern "C"
{
#endif

    NrtNovelRunner Nrt_NovelRunner_create(int32_t displayNumber)
    {
        NovelRunner* runner = new NovelRunner(displayNumber);
        return reinterpret_cast<NrtNovelRunner>(runner);
    }

    NrtNovelRunner Nrt_NovelRunner_createCustom(int32_t displayNumber,
                                                const char* windowTitle,
                                                NrtWindowMode windowMode,
                                                uint32_t targetFrameRate)
    {
        NovelRunner* runner = new NovelRunner(
            displayNumber, windowTitle, static_cast<WindowMode>(windowMode), targetFrameRate);
        return reinterpret_cast<NrtNovelRunner>(runner);
    }

    NrtResult Nrt_NovelRunner_runNovel(NrtNovelRunner runner)
    {
        if (runner == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        NovelRunner* cRunner = reinterpret_cast<NovelRunner*>(runner);
        cRunner->runNovel();
        return NRT_SUCCESS;
    }

    NrtResult Nrt_NovelRunner_destroy(NrtNovelRunner runner)
    {
        if (runner == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        NovelRunner* cRunner = reinterpret_cast<NovelRunner*>(runner);

        cRunner->~NovelRunner();
        return NRT_SUCCESS;
    }

    NrtResult Nrt_NovelRunner_getAudioService(NrtNovelRunner runner, NrtAudioService* outputService)
    {
        if (runner == nullptr || outputService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        NovelRunner* cRunner = reinterpret_cast<NovelRunner*>(runner);
        _audioCollection.push_back(cRunner->getAudioService());

        auto ptr = _audioCollection.back().get();
        if (ptr == nullptr)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        *outputService = reinterpret_cast<NrtAudioService>(ptr);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_NovelRunner_getInteractionService(NrtNovelRunner runner, NrtInteractionService* outputService)
    {
        if (runner == nullptr || outputService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        NovelRunner* cRunner = reinterpret_cast<NovelRunner*>(runner);
        _interactionCollection.push_back(cRunner->getInteractionService());

        auto ptr = _interactionCollection.back().get();
        if (ptr == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }
        *outputService = reinterpret_cast<NrtInteractionService>(ptr);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_NovelRunner_getWindowingService(NrtNovelRunner runner, NrtWindowingService* outputService)
    {
        if (runner == nullptr || outputService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        NovelRunner* cRunner = reinterpret_cast<NovelRunner*>(runner);
        _windowingCollection.push_back(cRunner->getWindowingService());

        auto ptr = _windowingCollection.back().get();
        if (ptr == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }
        *outputService = reinterpret_cast<NrtWindowingService>(ptr);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_NovelRunner_getRuntimeService(NrtNovelRunner runner, NrtRuntimeService* outputService)
    {
        if (runner == nullptr || outputService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        NovelRunner* cRunner = reinterpret_cast<NovelRunner*>(runner);
        _runtimeCollection.push_back(cRunner->getDotNetRuntimeService());

        auto ptr = _runtimeCollection.back().get();
        if (ptr == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }
        *outputService = reinterpret_cast<NrtRuntimeService>(ptr);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_NovelRunner_getRenderer(NrtNovelRunner runner, NrtRenderingService* outputService)
    {
        if (runner == nullptr || outputService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        NovelRunner* cRunner = reinterpret_cast<NovelRunner*>(runner);
        _rendererCollection.push_back(cRunner->getRenderer());

        auto ptr = _rendererCollection.back().get();
        if (ptr == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }
        *outputService = reinterpret_cast<NrtRenderingService>(ptr);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_NovelRunner_getDebugService(NrtNovelRunner runner, NrtDebugService* outputService)
    {
        if (runner == nullptr || outputService == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        NovelRunner* cRunner = reinterpret_cast<NovelRunner*>(runner);
        _debugServiceCollection.push_back(cRunner->getDebugService());

        auto ptr = _debugServiceCollection.back().get();
        if (ptr == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }
        *outputService = reinterpret_cast<NrtDebugService>(ptr);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_NovelRunner_addUpdate(NrtNovelRunner runner, void (*func)(NrtTimestamp))
    {
        if (runner == nullptr || func == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        NovelRunner* cRunner = reinterpret_cast<NovelRunner*>(runner);

        cRunner->Update += [func](Timing::Timestamp delta) { func(reinterpret_cast<NrtTimestamp&>(delta)); };

        return NRT_SUCCESS;
    }

    NrtResult Nrt_NovelRunner_addSceneConstructionRequested(NrtNovelRunner runner, void (*func)())
    {
        if (runner == nullptr || func == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        NovelRunner* cRunner = reinterpret_cast<NovelRunner*>(runner);

        cRunner->SceneConstructionRequested += [func]() { func(); };
        return NRT_SUCCESS;
    }

    NrtResult Nrt_NovelRunner_getUpdateEvent(NrtNovelRunner runner, NrtUtilitiesEventWithTimestamp* outputEvent)
    {
        if (runner == nullptr || outputEvent == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        NovelRunner* cRunner = reinterpret_cast<NovelRunner*>(runner);
        *outputEvent = reinterpret_cast<NrtUtilitiesEventWithTimestamp&>(cRunner->Update);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_NovelRunner_getSceneConstructionEvent(NrtNovelRunner runner, NrtUtilitiesEvent* outputEvent)
    {
        if (runner == nullptr || outputEvent == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        NovelRunner* cRunner = reinterpret_cast<NovelRunner*>(runner);
        *outputEvent = reinterpret_cast<NrtUtilitiesEvent&>(cRunner->SceneConstructionRequested);
        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
