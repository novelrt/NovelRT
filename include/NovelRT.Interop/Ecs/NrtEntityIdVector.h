// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_NRTENTITYIDVECTOR_H
#define NOVELRT_NRTENTITYIDVECTOR_H

#include "NrtEcsUtils.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtEntityIdVector Nrt_EntityIdVector_Create();

    NrtResult Nrt_EntityIdVector_Insert(NrtEntityIdVector vector, NrtEntityId entity);

    NrtResult Nrt_EntityIdVector_Remove(NrtEntityIdVector vector, NrtEntityId entity);

    NrtResult Nrt_EntityIdVector_Delete(NrtEntityIdVector vector);

#ifdef __cplusplus
};
#endif

#endif // NOVELRT_NRTENTITYIDVECTOR_H
