// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/NrtSystemScheduler.h>
#include <NovelRT/Ecs/Ecs.h>

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

    void Nrt_SystemScheduler_RegisterSystem(NrtSystemSchedulerHandle scheduler, NrtSystemUpdateFnPtr systemUpdatePtr)
    {
        auto schedulerPtr = reinterpret_cast<SystemScheduler*>(scheduler);
        schedulerPtr->RegisterSystem([=](auto timestamp, auto catalogue) {
            systemUpdatePtr(timestamp.ticks, reinterpret_cast<NrtCatalogueHandle>(&catalogue));
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
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        try
        {
            reinterpret_cast<SystemScheduler*>(systemScheduler)->ExecuteIteration(NovelRT::Timing::Timestamp(delta));
            return NRT_SUCCESS;
        }
        catch (const std::bad_alloc&)
        {
            return NRT_FAILURE_OUT_OF_MEMORY;
        }
        catch (const std::out_of_range&)
        {
            return NRT_FAILURE_ARGUMENT_OUT_OF_RANGE;
        }
        catch (const CharacterNotFoundException&)
        {
            return NRT_FAILURE_CHARACTER_NOT_FOUND;
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
            return NRT_FAILURE_FUNCTION_NOT_FOUND;
        }
        catch (const InitialisationFailureException&)
        {
            return NRT_FAILURE_INITIALISATION_FAILURE;
        }
        catch (const InvalidOperationException&)
        {
            return NRT_FAILURE_INVALID_OPERATION;
        }
        catch (const KeyNotFoundException&)
        {
            return NRT_FAILURE_KEY_NOT_FOUND;
        }
        catch (const NotInitialisedException&)
        {
            return NRT_FAILURE_NOT_INITIALISED;
        }
        catch (const NotSupportedException&)
        {
            return NRT_FAILURE_NOT_SUPPORTED;
        }
        catch (const NullPointerException&)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }
        catch (const OutOfMemoryException&)
        {
            return NRT_FAILURE_OUT_OF_MEMORY;
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

    NrtResult Nrt_SystemScheduler_Destroy(NrtSystemSchedulerHandle systemScheduler)
    {
        if (systemScheduler == nullptr)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        delete reinterpret_cast<SystemScheduler*>(systemScheduler);

        return NRT_SUCCESS;
    }
}
