// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/Input/NrtInputSystem.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT/Ecs/Ecs.h>

using namespace NovelRT;
using namespace PluginManagement;
using namespace Ecs::Input;

#ifdef __cplusplus
extern "C"
{
#endif

    NrtInputSystemHandle Nrt_InputSystem_Create(
        NrtIWindowingPluginProviderPtrHandle windowingProvider,
        NrtIInputPluginProviderPtrHandle inputProvider)
    {
        auto cppWindowing = reinterpret_cast<IWindowingPluginProvider*>(windowingProvider)->shared_from_this();
        auto cppInput = reinterpret_cast<IInputPluginProvider*>(inputProvider)->shared_from_this();

        auto cppSystem = new InputSystem(cppWindowing, cppInput);
        return reinterpret_cast<NrtInputSystemHandle>(cppSystem);
    }

    NrtResult Nrt_InputSystem_Destroy(NrtInputSystemHandle system)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto cppSystem = reinterpret_cast<InputSystem*>(system);
        delete cppSystem;
        return NRT_SUCCESS;
    }

    NrtResult Nrt_InputSystem_Update(NrtInputSystemHandle system, NrtTimestamp delta, NrtCatalogueHandle catalogue)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (catalogue == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto cppSystem = reinterpret_cast<InputSystem*>(system);
        auto cppTimestamp = *reinterpret_cast<Timing::Timestamp*>(&delta);
        auto cppCatalogue = reinterpret_cast<Ecs::Catalogue*>(catalogue);

        cppSystem->Update(cppTimestamp, *cppCatalogue);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_InputSystem_AddMapping(NrtInputSystemHandle system, const char* name, const char* id)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (name == nullptr, id == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto cppSystem = reinterpret_cast<InputSystem*>(system);

        cppSystem->AddMapping(std::string(name), std::string(id));
        return NRT_SUCCESS;
    }

    NrtResult Nrt_InputSystem_AddDefaultKBMMapping(NrtInputSystemHandle system)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto cppSystem = reinterpret_cast<InputSystem*>(system);

        cppSystem->AddDefaultKBMMapping();
        return NRT_SUCCESS;
    }

    NrtResult Nrt_InputSystem_GetMappingId(
        NrtInputSystemHandle system,
        const char* mappingName,
        NrtAtom *outputResult)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }
        if (mappingName == nullptr, outputResult == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto cppSystem = reinterpret_cast<InputSystem*>(system);
        auto cppAtom = cppSystem->GetMappingId(std::string(mappingName));
        *outputResult = reinterpret_cast<NrtAtom>(&cppAtom);
        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
