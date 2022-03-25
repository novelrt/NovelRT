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

    NrtInputSystemHandle Nrt_InputSystem_create(
        NrtIWindowingPluginProviderPtrHandle windowingProvider,
        NrtIInputPluginProviderPtrHandle inputProvider)
    {
        auto CppWindowing = reinterpret_cast<IWindowingPluginProvider*>(windowingProvider)->shared_from_this();
        auto CppInput = reinterpret_cast<IInputPluginProvider*>(inputProvider)->shared_from_this();

        auto CppSystem = new InputSystem(CppWindowing, CppInput);
        return reinterpret_cast<NrtInputSystemHandle>(CppSystem);
    }

    NrtResult Nrt_InputSystem_destroy(NrtInputSystemHandle system)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto CppSystem = reinterpret_cast<InputSystem*>(system);
        delete CppSystem;
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

        auto CppSystem = reinterpret_cast<InputSystem*>(system);
        auto CppTimestamp = *reinterpret_cast<Timing::Timestamp*>(&delta);
        auto CppCatalogue = reinterpret_cast<Ecs::Catalogue*>(catalogue);

        CppSystem->Update(CppTimestamp, *CppCatalogue);
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

        auto CppSystem = reinterpret_cast<InputSystem*>(system);

        CppSystem->AddMapping(std::string(name), std::string(id));
        return NRT_SUCCESS;
    }

    NrtResult Nrt_InputSystem_AddDefaultKBMMapping(NrtInputSystemHandle system)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto CppSystem = reinterpret_cast<InputSystem*>(system);

        CppSystem->AddDefaultKBMMapping();
        return NRT_SUCCESS;
    }

    NrtResult Nrt_InputSystem_GetMappingId(
        NrtInputSystemHandle system,
        const char* mappingName,
        NrtAtom *output)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }
        if (mappingName == nullptr, output == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto CppSystem = reinterpret_cast<InputSystem*>(system);
        auto CppAtom = CppSystem->GetMappingId(std::string(mappingName));
        *output = reinterpret_cast<NrtAtom>(&CppAtom);
        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
