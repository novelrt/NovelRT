// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/NrtCatalogue.h>
#include <NovelRT/Ecs/Ecs.h>
#include <NovelRT.Interop/NrtErrorHandling.h>

using namespace NovelRT::Ecs;

extern "C"
{
    NrtCatalogueHandle Nrt_Catalogue_Create(size_t poolId,
                                            NrtComponentCacheHandle componentCache,
                                            NrtEntityCacheHandle entityCache)
    {
        auto catalogue = new Catalogue(poolId, *reinterpret_cast<ComponentCache*>(componentCache),
                                       *reinterpret_cast<EntityCache*>(entityCache));
        return reinterpret_cast<NrtCatalogueHandle>(catalogue);
    }

    NrtResult Nrt_Catalogue_GetComponentViewById(NrtCatalogueHandle catalogue,
                                                 NrtComponentTypeId componentId,
                                                 NrtUnsafeComponentViewHandle* outputResult)
    {
        if (catalogue == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
        }

        if (outputResult == nullptr)
        {
            return Nrt_getNullArgumentErrorInternal();
        }

        auto returnPtr = new UnsafeComponentView(0, nullptr);
        try
        {
            auto actualCatalogue = reinterpret_cast<Catalogue*>(catalogue);
            *returnPtr = actualCatalogue->GetComponentViewById(componentId);
            *outputResult = reinterpret_cast<NrtUnsafeComponentViewHandle>(returnPtr);
        }
        catch (const std::out_of_range&)
        {
            delete returnPtr;
            return Nrt_getArgumentOutOfRangeErrorInternal();
        }

        return NRT_SUCCESS;
    }

    NrtUnsafeComponentViewHandle Nrt_Catalogue_GetComponentViewByIdUnsafe(NrtCatalogueHandle catalogue,
                                                                          NrtComponentTypeId componentId)
    {
        auto actualCatalogue = reinterpret_cast<Catalogue*>(catalogue);

        auto returnPtr = new UnsafeComponentView(0, nullptr);
        *returnPtr = actualCatalogue->GetComponentViewById(componentId);
        return reinterpret_cast<NrtUnsafeComponentViewHandle>(returnPtr);
    }

    NrtEntityId Nrt_Catalogue_CreateEntity(NrtCatalogueHandle catalogue)
    {
        return reinterpret_cast<Catalogue*>(catalogue)->CreateEntity();
    }

    NrtResult Nrt_Catalogue_DeleteEntity(NrtCatalogueHandle catalogue, NrtEntityId entity)
    {
        if (catalogue == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
        }

        reinterpret_cast<Catalogue*>(catalogue)->DeleteEntity(entity);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_Catalogue_Destroy(NrtCatalogueHandle catalogue)
    {
        if (catalogue == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
        }

        delete reinterpret_cast<Catalogue*>(catalogue);

        return NRT_SUCCESS;
    }
}
