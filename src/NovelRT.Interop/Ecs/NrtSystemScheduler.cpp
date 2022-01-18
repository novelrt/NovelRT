// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/NrtSystemScheduler.h>
#include <NovelRT/Ecs/Ecs.h>
#include <NovelRT.Interop/NrtErrorHandling.h>

using namespace NovelRT::Ecs;
using namespace NovelRT::Exceptions;

extern "C"
{
    NrtSystemSchedulerHandle Nrt_SystemScheduler_CreateWithDefaultThreadCount()
    {
        return reinterpret_cast<NrtSystemSchedulerHandle>(new SystemScheduler());
    }

    NrtSystemSchedulerHandle Nrt_SystemScheduler_Create(uint32_t maximumThreadCount)
    {
        return reinterpret_cast<NrtSystemSchedulerHandle>(new SystemScheduler(maximumThreadCount));
    }

    NrtBool Nrt_SystemScheduler_GetThreadsAreSpinning(NrtSystemSchedulerHandle systemScheduler)
    {
        auto schedulerPtr = reinterpret_cast<SystemScheduler*>(systemScheduler);

        if (schedulerPtr->GetThreadsAreSpinning())
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    void Nrt_SystemScheduler_RegisterSystem(NrtSystemSchedulerHandle systemScheduler,
                                            NrtSystemUpdateFnPtr systemUpdatePtr,
                                            void* context)
    {
        auto schedulerPtr = reinterpret_cast<SystemScheduler*>(systemScheduler);
        schedulerPtr->RegisterSystem([=](auto timestamp, auto catalogue) {
            systemUpdatePtr(timestamp.ticks, reinterpret_cast<NrtCatalogueHandle>(&catalogue), context);
        });
    }

    uint32_t Nrt_SystemScheduler_GetWorkerThreadCount(NrtSystemSchedulerHandle systemScheduler)
    {
        return reinterpret_cast<SystemScheduler*>(systemScheduler)->GetWorkerThreadCount();
    }

    NrtEntityCacheHandle Nrt_SystemScheduler_GetEntityCache(NrtSystemSchedulerHandle systemScheduler)
    {
        return reinterpret_cast<NrtEntityCacheHandle>(
            &reinterpret_cast<SystemScheduler*>(systemScheduler)->GetEntityCache());
    }

    NrtComponentCacheHandle Nrt_SystemScheduler_GetComponentCache(NrtSystemSchedulerHandle systemScheduler)
    {
        return reinterpret_cast<NrtComponentCacheHandle>(
            &reinterpret_cast<SystemScheduler*>(systemScheduler)->GetComponentCache());
    }

    void Nrt_SystemScheduler_SpinThreads(NrtSystemSchedulerHandle systemScheduler)
    {
        reinterpret_cast<SystemScheduler*>(systemScheduler)->SpinThreads();
    }

    NrtResult Nrt_SystemScheduler_ExecuteIteration(NrtSystemSchedulerHandle systemScheduler, NrtTimestamp delta)
    {
        if (systemScheduler == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
        }

        try
        {
            reinterpret_cast<SystemScheduler*>(systemScheduler)->ExecuteIteration(NovelRT::Timing::Timestamp(delta));
            return NRT_SUCCESS;
        }
        catch (const std::bad_alloc&)
        {
            return Nrt_getOutOfMemoryErrorInternal();
        }
        catch (const std::out_of_range&)
        {
            return Nrt_getArgumentOutOfRangeErrorInternal();
        }
        catch (const CharacterNotFoundException&)
        {
            return Nrt_getCharacterNotFoundErrorInternal();
        }
        catch (const CompilationErrorException&)
        {
            return NRT_FAILURE_COMPILATION_ERROR;
        }
        catch (const DuplicateKeyException&)
        {
            return NRT_FAILURE_DUPLICATE_KEY_PROVIDED;
        }
        catch (const FileNotFoundException&)
        {
            return NRT_FAILURE_FILE_NOT_FOUND;
        }
        catch (const FunctionNotFoundException&)
        {
            return Nrt_getFunctionNotFoundErrorInternal();
        }
        catch (const InitialisationFailureException&)
        {
            return Nrt_getInitialisationFailureErrorInternal();
        }
        catch (const InvalidOperationException&)
        {
            return Nrt_getInvalidOperationErrorInternal();
        }
        catch (const KeyNotFoundException&)
        {
            return NRT_FAILURE_KEY_NOT_FOUND;
        }
        catch (const NotInitialisedException&)
        {
            return Nrt_getNotInitialisedErrorInternal();
        }
        catch (const NotSupportedException&)
        {
            return Nrt_getNotSupportedErrorInternal();
        }
        catch (const NullPointerException&)
        {
            return Nrt_getNullArgumentErrorInternal();
        }
        catch (const OutOfMemoryException&)
        {
            return Nrt_getOutOfMemoryErrorInternal();
        }
        catch (const RuntimeNotFoundException&)
        {
            return NRT_FAILURE_RUNTIME_NOT_FOUND;
        }
        catch (...)
        {
            return NRT_FAILURE_UNKNOWN;
        }
    }

    NrtResult Nrt_SystemScheduler_ShutDown(NrtSystemSchedulerHandle systemScheduler)
    {
        if (systemScheduler == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
        }

        auto schedulerPtr = reinterpret_cast<SystemScheduler*>(systemScheduler);
        schedulerPtr->ShutDown();

        return NRT_SUCCESS;
    }

    NrtResult Nrt_SystemScheduler_Destroy(NrtSystemSchedulerHandle systemScheduler)
    {
        if (systemScheduler == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
        }

        delete reinterpret_cast<SystemScheduler*>(systemScheduler);

        return NRT_SUCCESS;
    }
}
