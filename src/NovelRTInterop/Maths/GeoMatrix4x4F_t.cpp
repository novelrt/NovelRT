// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.h"
#include "NovelRTInterop/Maths/GeoMatrix4x4F_t.h"

#ifndef NOVELRT_MATHS_GEOMATRIX4X4F_T_H
#define NOVELRT_MATHS_GEOMATRIX4X4F_T_H

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

  GeoMatrix4x4F_t GeoMatrix4x4F_create(GeoVector4F_t& x, GeoVector4F_t& y, GeoVector4F_t& z, GeoVector4F_t& w) {
    return GeoMatrix4x4F_t{ x, y, z, w };
  }

  GeoVector4F_t GeoMatrix4x4F_getX(GeoMatrix4x4F_t& gm) {
    return gm.x;
  }

  void GeoMatrix4x4F_setX(GeoMatrix4x4F_t& gm, const GeoVector4F_t& value) {
    gm.x = value;
  }

  GeoVector4F_t GeoMatrix4x4F_getY(GeoMatrix4x4F_t& gm) {
    return gm.y;
  }

  void GeoMatrix4x4F_setY(GeoMatrix4x4F_t& gm, const GeoVector4F_t& value) {
    gm.y = value;
  }

  GeoVector4F_t GeoMatrix4x4F_getZ(GeoMatrix4x4F_t& gm) {
    return gm.z;
  }

  void GeoMatrix4x4F_setZ(GeoMatrix4x4F_t& gm, const GeoVector4F_t& value) {
    gm.z = value;
  }

  GeoVector4F_t GeoMatrix4x4F_getW(GeoMatrix4x4F_t& gm) {
    return gm.w;
  }

  void GeoMatrix4x4F_setW(GeoMatrix4x4F_t& gm, const GeoVector4F_t& value) {
    gm.w = value;
  }

  GeoMatrix4x4F_t GeoMatrix4x4F_getDefaultIdentity(GeoMatrix4x4F_t& gm) {
    Maths::GeoMatrix4x4<float> cMatrix = *reinterpret_cast<Maths::GeoMatrix4x4<float>*>(&gm);
    Maths::GeoMatrix4x4<float>* identity = new Maths::GeoMatrix4x4<float>();
    *identity = cMatrix.getDefaultIdentity();
    return reinterpret_cast<GeoMatrix4x4F_t&>(*identity);
  }

  bool GeoMatrix4x4F_equal(const GeoMatrix4x4F_t& first, const GeoMatrix4x4F_t& other) {
    return *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(&first) == *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(&other);
  }

  bool GeoMatrix4x4F_notEqual(const GeoMatrix4x4F_t& first, const GeoMatrix4x4F_t& other) {
    return *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(&first) != *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(&other);
  }

  GeoMatrix4x4F_t GeoMatrix4x4F_addMatrix(GeoMatrix4x4F_t& first, const GeoMatrix4x4F_t& other) {
    Maths::GeoMatrix4x4<float> cFirst = *reinterpret_cast<Maths::GeoMatrix4x4<float>*>(&first);
    Maths::GeoMatrix4x4<float> cOther = *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(&other);
    Maths::GeoMatrix4x4<float>* result = new Maths::GeoMatrix4x4<float>();
    *result = cFirst + cOther;
    return reinterpret_cast<GeoMatrix4x4F_t&>(*result);
  }

  GeoMatrix4x4F_t GeoMatrix4x4F_subtractMatrix(GeoMatrix4x4F_t& first, const GeoMatrix4x4F_t& other) {
    Maths::GeoMatrix4x4<float> cFirst = *reinterpret_cast<Maths::GeoMatrix4x4<float>*>(&first);
    Maths::GeoMatrix4x4<float> cOther = *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(&other);
    Maths::GeoMatrix4x4<float>* result = new Maths::GeoMatrix4x4<float>();
    *result = cFirst - cOther;
    return reinterpret_cast<GeoMatrix4x4F_t&>(*result);
  }

  GeoMatrix4x4F_t GeoMatrix4x4F_multiplyMatrix(GeoMatrix4x4F_t& first, const GeoMatrix4x4F_t& other) {
    Maths::GeoMatrix4x4<float> cFirst = *reinterpret_cast<Maths::GeoMatrix4x4<float>*>(&first);
    Maths::GeoMatrix4x4<float> cOther = *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(&other);
    Maths::GeoMatrix4x4<float>* result = new Maths::GeoMatrix4x4<float>();
    *result = cFirst * cOther;
    return reinterpret_cast<GeoMatrix4x4F_t&>(*result);
  }

  GeoMatrix4x4F_t GeoMatrix4x4F_addIntoMatrix(GeoMatrix4x4F_t& first, const GeoMatrix4x4F_t& other) {
    Maths::GeoMatrix4x4<float> cFirst = *reinterpret_cast<Maths::GeoMatrix4x4<float>*>(&first);
    Maths::GeoMatrix4x4<float> cOther = *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(&other);
    cFirst += cOther;
    first = reinterpret_cast<GeoMatrix4x4F_t&>(cFirst); 
    return first;
  }

  GeoMatrix4x4F_t GeoMatrix4x4F_subtractFromMatrix(GeoMatrix4x4F_t& first, const GeoMatrix4x4F_t& other) {
    Maths::GeoMatrix4x4<float> cFirst = *reinterpret_cast<Maths::GeoMatrix4x4<float>*>(&first);
    Maths::GeoMatrix4x4<float> cOther = *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(&other);
    cFirst -= cOther;
    first = reinterpret_cast<GeoMatrix4x4F_t&>(cFirst);
    return first;
  }

  GeoMatrix4x4F_t GeoMatrix4x4F_multiplyIntoMatrix(GeoMatrix4x4F_t& first, const GeoMatrix4x4F_t& other) {
    Maths::GeoMatrix4x4<float> cFirst = *reinterpret_cast<Maths::GeoMatrix4x4<float>*>(&first);
    Maths::GeoMatrix4x4<float> cOther = *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(&other);
    cFirst *= cOther;
    first = reinterpret_cast<GeoMatrix4x4F_t&>(cFirst);
    return first;
  }

  GeoMatrix4x4F_t GeoMatrix4x4F_addFloat(GeoMatrix4x4F_t& matrix, float value) {
    Maths::GeoMatrix4x4<float> cMatrix = *reinterpret_cast<Maths::GeoMatrix4x4<float>*>(&matrix);
    Maths::GeoMatrix4x4<float>* result = new Maths::GeoMatrix4x4<float>();
    *result = cMatrix + value;
    return reinterpret_cast<GeoMatrix4x4F_t&>(*result);
  }

  GeoMatrix4x4F_t GeoMatrix4x4F_subtractFloat(GeoMatrix4x4F_t& matrix, float value) {
    Maths::GeoMatrix4x4<float> cMatrix = *reinterpret_cast<Maths::GeoMatrix4x4<float>*>(&matrix);
    Maths::GeoMatrix4x4<float>* result = new Maths::GeoMatrix4x4<float>();
    *result = cMatrix - value;
    return reinterpret_cast<GeoMatrix4x4F_t&>(*result);
  }

  GeoMatrix4x4F_t GeoMatrix4x4F_multiplyFloat(GeoMatrix4x4F_t& matrix, float value) {
    Maths::GeoMatrix4x4<float> cMatrix = *reinterpret_cast<Maths::GeoMatrix4x4<float>*>(&matrix);
    Maths::GeoMatrix4x4<float>* result = new Maths::GeoMatrix4x4<float>();
    *result = cMatrix * value;
    return reinterpret_cast<GeoMatrix4x4F_t&>(*result);
  }

  GeoMatrix4x4F_t GeoMatrix4x4F_addFloatIntoMatrix(GeoMatrix4x4F_t& matrix, float value) {
    Maths::GeoMatrix4x4<float> cMatrix = *reinterpret_cast<Maths::GeoMatrix4x4<float>*>(&matrix);
    cMatrix += value;
    matrix = reinterpret_cast<GeoMatrix4x4F_t&>(cMatrix);
    return matrix;
  }

  GeoMatrix4x4F_t GeoMatrix4x4F_subFloatFromMatrix(GeoMatrix4x4F_t& matrix, float value) {
    Maths::GeoMatrix4x4<float> cMatrix = *reinterpret_cast<Maths::GeoMatrix4x4<float>*>(&matrix);
    cMatrix -= value;
    matrix = reinterpret_cast<GeoMatrix4x4F_t&>(cMatrix);
    return matrix;
  }

  GeoMatrix4x4F_t GeoMatrix4x4F_multiplyFloatIntoMatrix(GeoMatrix4x4F_t& matrix, float value) {
    Maths::GeoMatrix4x4<float> cMatrix = *reinterpret_cast<Maths::GeoMatrix4x4<float>*>(&matrix);
    cMatrix *= value;
    matrix = reinterpret_cast<GeoMatrix4x4F_t&>(cMatrix);
    return matrix;
  }

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_MATHS_GEOMATRIX4X4F_T_H
