// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.h"
#include "NovelRTInterop/Maths/GeoMatrix4x4F_t.h"

#ifndef NOVELRT_MATHS_GEOMATRIX4X4F_T_H
#define NOVELRT_MATHS_GEOMATRIX4X4F_T_H

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

  GeoMatrix4x4F_t* GeoMatrix4x4F_create(GeoVector4F_t* x, GeoVector4F_t* y, GeoVector4F_t* z, GeoVector4F_t* w) {
    static Maths::GeoMatrix4x4<float> matrix = Maths::GeoMatrix4x4<float>(*reinterpret_cast<Maths::GeoVector4<float>*>(x),
      *reinterpret_cast<Maths::GeoVector4<float>*>(y), *reinterpret_cast<Maths::GeoVector4<float>*>(z), *reinterpret_cast<Maths::GeoVector4<float>*>(w));
    return reinterpret_cast<GeoMatrix4x4F_t*>(&matrix);
  }

  GeoVector4F_t* GeoMatrix4x4F_getX(GeoMatrix4x4F_t* gm) {
    static Maths::GeoVector4<float> x = reinterpret_cast<Maths::GeoMatrix4x4<float>*>(gm)->getX();
    return reinterpret_cast<GeoVector4F_t*>(&x);
  }

  void GeoMatrix4x4F_setX(GeoMatrix4x4F_t* gm, const GeoVector4F_t* value) {
    static Maths::GeoMatrix4x4<float> matrix = *reinterpret_cast<Maths::GeoMatrix4x4<float>*>(gm);
    matrix.setX(*reinterpret_cast<const Maths::GeoVector4<float>*>(value));
    gm = reinterpret_cast<GeoMatrix4x4F_t*>(&matrix);
  }

  GeoVector4F_t* GeoMatrix4x4F_getY(GeoMatrix4x4F_t* gm) {
    static Maths::GeoVector4<float> y = reinterpret_cast<Maths::GeoMatrix4x4<float>*>(gm)->getY();
    return reinterpret_cast<GeoVector4F_t*>(&y);
  }

  void GeoMatrix4x4F_setY(GeoMatrix4x4F_t* gm, const GeoVector4F_t* value) {
    static Maths::GeoMatrix4x4<float> matrix = *reinterpret_cast<Maths::GeoMatrix4x4<float>*>(gm);
    matrix.setY(*reinterpret_cast<const Maths::GeoVector4<float>*>(value));
    gm = reinterpret_cast<GeoMatrix4x4F_t*>(&matrix);
  }

  GeoVector4F_t* GeoMatrix4x4F_getZ(GeoMatrix4x4F_t* gm) {
    static Maths::GeoVector4<float> z = reinterpret_cast<Maths::GeoMatrix4x4<float>*>(gm)->getZ();
    return reinterpret_cast<GeoVector4F_t*>(&z);
  }

  void GeoMatrix4x4F_setZ(GeoMatrix4x4F_t* gm, const GeoVector4F_t* value) {
    static Maths::GeoMatrix4x4<float> matrix = *reinterpret_cast<Maths::GeoMatrix4x4<float>*>(gm);
    matrix.setZ(*reinterpret_cast<const Maths::GeoVector4<float>*>(value));
    gm = reinterpret_cast<GeoMatrix4x4F_t*>(&matrix);
  }

  GeoVector4F_t* GeoMatrix4x4F_getW(GeoMatrix4x4F_t* gm) {
    static Maths::GeoVector4<float> w = reinterpret_cast<Maths::GeoMatrix4x4<float>*>(gm)->getW();
    return reinterpret_cast<GeoVector4F_t*>(&w);
  }

  void GeoMatrix4x4F_setW(GeoMatrix4x4F_t* gm, const GeoVector4F_t* value) {
    static Maths::GeoMatrix4x4<float> matrix = *reinterpret_cast<Maths::GeoMatrix4x4<float>*>(gm);
    matrix.setW(*reinterpret_cast<const Maths::GeoVector4<float>*>(value));
    gm = reinterpret_cast<GeoMatrix4x4F_t*>(&matrix);
  }

  GeoMatrix4x4F_t* GeoMatrix4x4F_getDefaultIdentity(GeoMatrix4x4F_t* gm) {
    static Maths::GeoMatrix4x4<float> identity = reinterpret_cast<Maths::GeoMatrix4x4<float>*>(gm)->getDefaultIdentity();
    return reinterpret_cast<GeoMatrix4x4F_t*>(&identity);
  }

  bool GeoMatrix4x4F_equal(const GeoMatrix4x4F_t* first, const GeoMatrix4x4F_t* other) {
    return *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(first) == *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(other);
  }

  bool GeoMatrix4x4F_notEqual(const GeoMatrix4x4F_t* first, const GeoMatrix4x4F_t* other) {
    return *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(first) != *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(other);
  }

  GeoMatrix4x4F_t* GeoMatrix4x4F_addMatrix(GeoMatrix4x4F_t* first, const GeoMatrix4x4F_t* other) {
    static NovelRT::Maths::GeoMatrix4x4<float> matrix = *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(first) + *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(other);
    return reinterpret_cast<GeoMatrix4x4F_t*>(&matrix);
  }

  GeoMatrix4x4F_t* GeoMatrix4x4F_subtractMatrix(GeoMatrix4x4F_t* first, const GeoMatrix4x4F_t* other) {
    static NovelRT::Maths::GeoMatrix4x4<float> matrix = *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(first) - *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(other);
    return reinterpret_cast<GeoMatrix4x4F_t*>(&matrix);
  }

  GeoMatrix4x4F_t* GeoMatrix4x4F_multiplyMatrix(GeoMatrix4x4F_t* first, const GeoMatrix4x4F_t* other) {
    static NovelRT::Maths::GeoMatrix4x4<float> matrix = *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(first) * (*reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(other));
    return reinterpret_cast<GeoMatrix4x4F_t*>(&matrix);
  }

  GeoMatrix4x4F_t* GeoMatrix4x4F_addIntoMatrix(GeoMatrix4x4F_t* first, const GeoMatrix4x4F_t* other) {
    static NovelRT::Maths::GeoMatrix4x4<float> matrix = *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(first);
    matrix += *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(other);
    first = reinterpret_cast<GeoMatrix4x4F_t*>(&matrix);
    return first;
  }

  GeoMatrix4x4F_t* GeoMatrix4x4F_subtractFromMatrix(GeoMatrix4x4F_t* first, const GeoMatrix4x4F_t* other) {
    static NovelRT::Maths::GeoMatrix4x4<float> matrix = *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(first);
    matrix -= *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(other);
    first = reinterpret_cast<GeoMatrix4x4F_t*>(&matrix);
    return first;
  }

  GeoMatrix4x4F_t* GeoMatrix4x4F_multiplyIntoMatrix(GeoMatrix4x4F_t* first, const GeoMatrix4x4F_t* other) {
    static NovelRT::Maths::GeoMatrix4x4<float> matrix = *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(first);
    matrix *= *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(other);
    first = reinterpret_cast<GeoMatrix4x4F_t*>(&matrix);
    return first;
  }

  GeoMatrix4x4F_t* GeoMatrix4x4F_addFloat(GeoMatrix4x4F_t* matrix, float value) {
    static NovelRT::Maths::GeoMatrix4x4<float> mat = *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(matrix) + value;
    return reinterpret_cast<GeoMatrix4x4F_t*>(&mat);
  }

  GeoMatrix4x4F_t* GeoMatrix4x4F_subtractFloat(GeoMatrix4x4F_t* matrix, float value) {
    static NovelRT::Maths::GeoMatrix4x4<float> mat = *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(matrix) - value;
    return reinterpret_cast<GeoMatrix4x4F_t*>(&mat);
  }

  GeoMatrix4x4F_t* GeoMatrix4x4F_multiplyFloat(GeoMatrix4x4F_t* matrix, float value) {
    static NovelRT::Maths::GeoMatrix4x4<float> mat = *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(matrix) * value;
    return reinterpret_cast<GeoMatrix4x4F_t*>(&mat);
  }

  GeoMatrix4x4F_t* GeoMatrix4x4F_addFloatIntoMatrix(GeoMatrix4x4F_t* matrix, float value) {
    static NovelRT::Maths::GeoMatrix4x4<float> mat = *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(matrix);
    mat += value;
    matrix = reinterpret_cast<GeoMatrix4x4F_t*>(&mat);
    return matrix;
  }

  GeoMatrix4x4F_t* GeoMatrix4x4F_subFloatFromMatrix(GeoMatrix4x4F_t* matrix, float value) {
    static NovelRT::Maths::GeoMatrix4x4<float> mat = *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(matrix);
    mat -= value;
    matrix = reinterpret_cast<GeoMatrix4x4F_t*>(&mat);
    return matrix;
  }

  GeoMatrix4x4F_t* GeoMatrix4x4F_multiplyFloatIntoMatrix(GeoMatrix4x4F_t* matrix, float value) {
    static NovelRT::Maths::GeoMatrix4x4<float> mat = *reinterpret_cast<const Maths::GeoMatrix4x4<float>*>(matrix);
    mat *= value;
    matrix = reinterpret_cast<GeoMatrix4x4F_t*>(&mat);
    return matrix;
  }

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_MATHS_GEOMATRIX4X4F_T_H
