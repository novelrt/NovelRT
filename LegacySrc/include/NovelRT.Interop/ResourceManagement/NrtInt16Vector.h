// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_RESOURCEMANAGEMENT_INT16VECTOR_H
#define NOVELRT_INTEROP_RESOURCEMANAGEMENT_INT16VECTOR_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtInt16VectorHandle Nrt_Int16Vector_Create();

    NrtResult Nrt_Int16Vector_Destroy(NrtInt16VectorHandle vector);

    NrtResult Nrt_Int16Vector_Insert(NrtInt16VectorHandle vector, int16_t value);

    NrtResult Nrt_Int16Vector_Remove(NrtInt16VectorHandle vector, int16_t value);

#ifdef __cplusplus
};
#endif

#endif // NOVELRT_INTEROP_RESOURCEMANAGEMENT_INT16VECTOR_H
