// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ECS_NRTCATALOGUE_H
#define NOVELRT_INTEROP_ECS_NRTCATALOGUE_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtCatalogueHandle Nrt_Catalogue_Create(size_t poolId, NrtComponentCacheHandle componentCache, NrtEntityCacheHandle entityCache);

    NrtResult Nrt_Catalogue_GetComponentViewById(NrtCatalogueHandle catalogue,
                                                 NrtComponentTypeId componentId,
                                                 NrtUnsafeComponentViewHandle* outputResult);

    NrtUnsafeComponentViewHandle Nrt_Catalogue_GetComponentViewByIdUnsafe(NrtCatalogueHandle catalogue,
                                                                    NrtComponentTypeId componentId);

    NrtEntityId Nrt_catalogue_CreateEntity(NrtCatalogueHandle catalogue);

    NrtResult Nrt_Catalogue_DeleteEntity(NrtCatalogueHandle catalogue, NrtEntityId entity);

    NrtResult Nrt_Catalogue_Destroy(NrtCatalogueHandle catalogue);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_NRTCATALOGUE_H
