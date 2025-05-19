// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_RESOURCEMANAGEMENT_UINT8VECTOR_H
#define NOVELRT_INTEROP_RESOURCEMANAGEMENT_UINT8VECTOR_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtUint8VectorHandle Nrt_Uint8Vector_Create();

    NrtResult Nrt_Uint8Vector_Destroy(NrtUint8VectorHandle vector);

    NrtResult Nrt_Uint8Vector_Insert(NrtUint8VectorHandle vector, uint8_t value);

    NrtResult Nrt_Uint8Vector_Remove(NrtUint8VectorHandle vector, uint8_t value);

#ifdef __cplusplus
};
#endif

#endif // NOVELRT_INTEROP_RESOURCEMANAGEMENT_UINT8VECTOR_H
