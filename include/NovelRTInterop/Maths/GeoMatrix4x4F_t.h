// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRTInterop/Maths/GeoVector4F_t.h"

#ifndef NOVELRT_INTEROP_MATHS_GEOMATRIX4X4F_T_H
#define NOVELRT_INTEROP_MATHS_GEOMATRIX4X4F_T_H

#ifdef __cplusplus
extern "C" {
#endif

  typedef void GeoMatrix4x4F_t;

  GeoMatrix4x4F_t* GeoMatrix4x4F_create(GeoVector4F_t* x, GeoVector4F_t* y, GeoVector4F_t* z, GeoVector4F_t* w);
  GeoVector4F_t* GeoMatrix4x4F_getX(GeoMatrix4x4F_t* gm);
  void GeoMatrix4x4F_setX(GeoMatrix4x4F_t* gm, const GeoVector4F_t* value);
  GeoVector4F_t* GeoMatrix4x4F_getY(GeoMatrix4x4F_t* gm);
  void GeoMatrix4x4F_setY(GeoMatrix4x4F_t* gm, const GeoVector4F_t* value);
  GeoVector4F_t* GeoMatrix4x4F_getZ(GeoMatrix4x4F_t* gm);
  void GeoMatrix4x4F_setZ(GeoMatrix4x4F_t* gm, const GeoVector4F_t* value);
  GeoVector4F_t* GeoMatrix4x4F_getW(GeoMatrix4x4F_t* gm);
  void GeoMatrix4x4F_setW(GeoMatrix4x4F_t* gm, const GeoVector4F_t* value);
  GeoMatrix4x4F_t* GeoMatrix4x4F_getDefaultIdentity(GeoMatrix4x4F_t* gm);
  bool GeoMatrix4x4F_equal(const GeoMatrix4x4F_t* first, const GeoMatrix4x4F_t* other);
  bool GeoMatrix4x4F_notEqual(const GeoMatrix4x4F_t* first, const GeoMatrix4x4F_t* other);
  GeoMatrix4x4F_t* GeoMatrix4x4F_addMatrix(GeoMatrix4x4F_t* first, const GeoMatrix4x4F_t* other);
  GeoMatrix4x4F_t* GeoMatrix4x4F_subtractMatrix(GeoMatrix4x4F_t* first, const GeoMatrix4x4F_t* other);
  GeoMatrix4x4F_t* GeoMatrix4x4F_multiplyMatrix(GeoMatrix4x4F_t* first, const GeoMatrix4x4F_t* other);
  GeoMatrix4x4F_t* GeoMatrix4x4F_addIntoMatrix(GeoMatrix4x4F_t* first, const GeoMatrix4x4F_t* other);
  GeoMatrix4x4F_t* GeoMatrix4x4F_subtractFromMatrix(GeoMatrix4x4F_t* first, const GeoMatrix4x4F_t* other);
  GeoMatrix4x4F_t* GeoMatrix4x4F_multiplyIntoMatrix(GeoMatrix4x4F_t* first, const GeoMatrix4x4F_t* other);
  GeoMatrix4x4F_t* GeoMatrix4x4F_addFloat(GeoMatrix4x4F_t* matrix, float value);
  GeoMatrix4x4F_t* GeoMatrix4x4F_subtractFloat(GeoMatrix4x4F_t* matrix, float value);
  GeoMatrix4x4F_t* GeoMatrix4x4F_multiplyFloat(GeoMatrix4x4F_t* matrix, float value);
  GeoMatrix4x4F_t* GeoMatrix4x4F_addFloatIntoMatrix(GeoMatrix4x4F_t* matrix, float value);
  GeoMatrix4x4F_t* GeoMatrix4x4F_subFloatFromMatrix(GeoMatrix4x4F_t* matrix, float value);
  GeoMatrix4x4F_t* GeoMatrix4x4F_multiplyFloatIntoMatrix(GeoMatrix4x4F_t* matrix, float value);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_MATHS_GEOMATRIX4X4F_T_H
