// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ECS_ENTITYIDVECTOR_H
#define NOVELRT_INTEROP_ECS_ENTITYIDVECTOR_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtEntityIdVectorHandle Nrt_EntityIdVector_Create();

    NrtResult Nrt_EntityIdVector_Insert(NrtEntityIdVectorHandle vector, NrtEntityId entity);

    NrtResult Nrt_EntityIdVector_Remove(NrtEntityIdVectorHandle vector, NrtEntityId entity);

    NrtResult Nrt_EntityIdVector_Destroy(NrtEntityIdVectorHandle vector);

#ifdef __cplusplus
};
#endif

#endif // NOVELRT_INTEROP_ECS_ENTITYIDVECTOR_H
