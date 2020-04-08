// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.h"
#include "GeoVector4F_t.h"

#ifndef NOVELRT_MATHS_GEOMATRIX4X4F_T_H
#define NOVELRT_MATHS_GEOMATRIX4X4F_T_H

#ifdef __cplusplus
extern "C" {
#endif

  struct GeoMatrix4x4F {
    GeoVector4F_t x;
    GeoVector4F_t y;
    GeoVector4F_t z;
    GeoVector4F_t w;
  };

  typedef struct GeoMatrix4x4F GeoMatrix4x4F_t;

  inline GeoMatrix4x4F_t GeoMatrix4x4F_create(GeoVector4F_t x, GeoVector4F_t y, GeoVector4F_t z, GeoVector4F_t w) {
    return { x, y, z, w };
  }

  inline GeoVector4F_t GeoMatrix4x4F_getX(GeoMatrix4x4F_t& gm) {
    return gm.x;
  }

  inline void GeoMatrix4x4F_setX(GeoMatrix4x4F_t& gm, const GeoVector4F_t& value) {
    gm.x = value;
  }

  inline GeoVector4F_t GeoMatrix4x4F_getY(GeoMatrix4x4F_t& gm) {
    return gm.y;
  }

  inline void GeoMatrix4x4F_setY(GeoMatrix4x4F_t& gm, const GeoVector4F_t& value) {
    gm.y = value;
  }

  inline GeoVector4F_t GeoMatrix4x4F_getZ(GeoMatrix4x4F_t& gm) {
    return gm.z;
  }

  inline void GeoMatrix4x4F_setZ(GeoMatrix4x4F_t& gm, const GeoVector4F_t& value) {
    gm.z = value;
  }

  inline GeoVector4F_t GeoMatrix4x4F_getW(GeoMatrix4x4F_t& gm) {
    return gm.w;
  }

  inline void GeoMatrix4x4F_setW(GeoMatrix4x4F_t& gm, const GeoVector4F_t& value) {
    gm.w = value;
  }

  inline GeoMatrix4x4F_t GeoMatrix4x4F_getDefaultIdentity(GeoMatrix4x4F_t& gm) {
    NovelRT::Maths::GeoMatrix4x4<float> matrix = NovelRT::Maths::GeoMatrix4x4(NovelRT::Maths::GeoVector4<float>(gm.x.x, gm.x.y, gm.x.z, gm.x.w),
      NovelRT::Maths::GeoVector4<float>(gm.y.x, gm.y.y, gm.y.z, gm.y.w), NovelRT::Maths::GeoVector4<float>(gm.z.x, gm.z.y, gm.z.z, gm.z.w),
      NovelRT::Maths::GeoVector4<float>(gm.w.x, gm.w.y, gm.w.z, gm.w.w));
    NovelRT::Maths::GeoMatrix4x4<float> result = matrix.getDefaultIdentity();

    GeoVector4F_t v1 = { result.getX().getX(), result.getX().getY(), result.getX().getZ(), result.getX().getW() };
    GeoVector4F_t v2 = { result.getY().getX(), result.getY().getY(), result.getY().getZ(), result.getY().getW() };
    GeoVector4F_t v3 = { result.getZ().getX(), result.getZ().getY(), result.getZ().getZ(), result.getZ().getW() };
    GeoVector4F_t v4 = { result.getW().getX(), result.getW().getY(), result.getW().getZ(), result.getW().getW() };
    return { v1, v2, v3, v4 };
  }

  inline bool GeoMatrix4x4F_equal(const GeoMatrix4x4F_t& first, const GeoMatrix4x4F_t& other) {
    NovelRT::Maths::GeoVector4<float> first_vX = NovelRT::Maths::GeoVector4<float>(first.x.x, first.x.y, first.x.z, first.x.w);
    NovelRT::Maths::GeoVector4<float> first_vY = NovelRT::Maths::GeoVector4<float>(first.y.x, first.y.y, first.y.z, first.y.w);
    NovelRT::Maths::GeoVector4<float> first_vZ = NovelRT::Maths::GeoVector4<float>(first.z.x, first.z.y, first.z.z, first.z.w);
    NovelRT::Maths::GeoVector4<float> first_vW = NovelRT::Maths::GeoVector4<float>(first.w.x, first.w.y, first.w.z, first.w.w);

    NovelRT::Maths::GeoVector4<float> other_vX = NovelRT::Maths::GeoVector4<float>(other.x.x, other.x.y, other.x.z, other.x.w);
    NovelRT::Maths::GeoVector4<float> other_vY = NovelRT::Maths::GeoVector4<float>(other.y.x, other.y.y, other.y.z, other.y.w);
    NovelRT::Maths::GeoVector4<float> other_vZ = NovelRT::Maths::GeoVector4<float>(other.z.x, other.z.y, other.z.z, other.z.w);
    NovelRT::Maths::GeoVector4<float> other_vW = NovelRT::Maths::GeoVector4<float>(other.w.x, other.w.y, other.w.z, other.w.w);

    return NovelRT::Maths::GeoMatrix4x4<float>(first_vX, first_vY, first_vZ, first_vW) == NovelRT::Maths::GeoMatrix4x4<float>(other_vX, other_vY, other_vZ, other_vW);
  }

  inline bool GeoMatrix4x4F_notEqual(const GeoMatrix4x4F_t& first, const GeoMatrix4x4F_t& other) {
    NovelRT::Maths::GeoVector4<float> first_vX = NovelRT::Maths::GeoVector4<float>(first.x.x, first.x.y, first.x.z, first.x.w);
    NovelRT::Maths::GeoVector4<float> first_vY = NovelRT::Maths::GeoVector4<float>(first.y.x, first.y.y, first.y.z, first.y.w);
    NovelRT::Maths::GeoVector4<float> first_vZ = NovelRT::Maths::GeoVector4<float>(first.z.x, first.z.y, first.z.z, first.z.w);
    NovelRT::Maths::GeoVector4<float> first_vW = NovelRT::Maths::GeoVector4<float>(first.w.x, first.w.y, first.w.z, first.w.w);

    NovelRT::Maths::GeoVector4<float> other_vX = NovelRT::Maths::GeoVector4<float>(other.x.x, other.x.y, other.x.z, other.x.w);
    NovelRT::Maths::GeoVector4<float> other_vY = NovelRT::Maths::GeoVector4<float>(other.y.x, other.y.y, other.y.z, other.y.w);
    NovelRT::Maths::GeoVector4<float> other_vZ = NovelRT::Maths::GeoVector4<float>(other.z.x, other.z.y, other.z.z, other.z.w);
    NovelRT::Maths::GeoVector4<float> other_vW = NovelRT::Maths::GeoVector4<float>(other.w.x, other.w.y, other.w.z, other.w.w);

    return NovelRT::Maths::GeoMatrix4x4<float>(first_vX, first_vY, first_vZ, first_vW) != NovelRT::Maths::GeoMatrix4x4<float>(other_vX, other_vY, other_vZ, other_vW);
  }

  inline GeoMatrix4x4F_t GeoMatrix4x4F_addMatrix(GeoMatrix4x4F_t& first, const GeoMatrix4x4F_t& other) {
    NovelRT::Maths::GeoVector4<float> first_vX = NovelRT::Maths::GeoVector4<float>(first.x.x, first.x.y, first.x.z, first.x.w);
    NovelRT::Maths::GeoVector4<float> first_vY = NovelRT::Maths::GeoVector4<float>(first.y.x, first.y.y, first.y.z, first.y.w);
    NovelRT::Maths::GeoVector4<float> first_vZ = NovelRT::Maths::GeoVector4<float>(first.z.x, first.z.y, first.z.z, first.z.w);
    NovelRT::Maths::GeoVector4<float> first_vW = NovelRT::Maths::GeoVector4<float>(first.w.x, first.w.y, first.w.z, first.w.w);

    NovelRT::Maths::GeoVector4<float> other_vX = NovelRT::Maths::GeoVector4<float>(other.x.x, other.x.y, other.x.z, other.x.w);
    NovelRT::Maths::GeoVector4<float> other_vY = NovelRT::Maths::GeoVector4<float>(other.y.x, other.y.y, other.y.z, other.y.w);
    NovelRT::Maths::GeoVector4<float> other_vZ = NovelRT::Maths::GeoVector4<float>(other.z.x, other.z.y, other.z.z, other.z.w);
    NovelRT::Maths::GeoVector4<float> other_vW = NovelRT::Maths::GeoVector4<float>(other.w.x, other.w.y, other.w.z, other.w.w);

    NovelRT::Maths::GeoMatrix4x4<float> result = NovelRT::Maths::GeoMatrix4x4<float>(first_vX, first_vY, first_vZ, first_vW)
      + NovelRT::Maths::GeoMatrix4x4<float>(other_vX, other_vY, other_vZ, other_vW);

    GeoVector4F_t vX = { result.getX().getX(), result.getX().getY(), result.getX().getZ(), result.getX().getW() };
    GeoVector4F_t vY = { result.getY().getX(), result.getY().getY(), result.getY().getZ(), result.getY().getW() };
    GeoVector4F_t vZ = { result.getZ().getX(), result.getZ().getY(), result.getZ().getZ(), result.getZ().getW() };
    GeoVector4F_t vW = { result.getW().getX(), result.getW().getY(), result.getW().getZ(), result.getW().getW() };

    return { vX, vY, vZ, vW };
  }

  inline GeoMatrix4x4F_t GeoMatrix4x4F_subtractMatrix(GeoMatrix4x4F_t& first, const GeoMatrix4x4F_t& other) {
    NovelRT::Maths::GeoVector4<float> first_vX = NovelRT::Maths::GeoVector4<float>(first.x.x, first.x.y, first.x.z, first.x.w);
    NovelRT::Maths::GeoVector4<float> first_vY = NovelRT::Maths::GeoVector4<float>(first.y.x, first.y.y, first.y.z, first.y.w);
    NovelRT::Maths::GeoVector4<float> first_vZ = NovelRT::Maths::GeoVector4<float>(first.z.x, first.z.y, first.z.z, first.z.w);
    NovelRT::Maths::GeoVector4<float> first_vW = NovelRT::Maths::GeoVector4<float>(first.w.x, first.w.y, first.w.z, first.w.w);

    NovelRT::Maths::GeoVector4<float> other_vX = NovelRT::Maths::GeoVector4<float>(other.x.x, other.x.y, other.x.z, other.x.w);
    NovelRT::Maths::GeoVector4<float> other_vY = NovelRT::Maths::GeoVector4<float>(other.y.x, other.y.y, other.y.z, other.y.w);
    NovelRT::Maths::GeoVector4<float> other_vZ = NovelRT::Maths::GeoVector4<float>(other.z.x, other.z.y, other.z.z, other.z.w);
    NovelRT::Maths::GeoVector4<float> other_vW = NovelRT::Maths::GeoVector4<float>(other.w.x, other.w.y, other.w.z, other.w.w);

    NovelRT::Maths::GeoMatrix4x4<float> result = NovelRT::Maths::GeoMatrix4x4<float>(first_vX, first_vY, first_vZ, first_vW)
      - NovelRT::Maths::GeoMatrix4x4<float>(other_vX, other_vY, other_vZ, other_vW);

    GeoVector4F_t vX = { result.getX().getX(), result.getX().getY(), result.getX().getZ(), result.getX().getW() };
    GeoVector4F_t vY = { result.getY().getX(), result.getY().getY(), result.getY().getZ(), result.getY().getW() };
    GeoVector4F_t vZ = { result.getZ().getX(), result.getZ().getY(), result.getZ().getZ(), result.getZ().getW() };
    GeoVector4F_t vW = { result.getW().getX(), result.getW().getY(), result.getW().getZ(), result.getW().getW() };

    return { vX, vY, vZ, vW };
  }

  inline GeoMatrix4x4F_t GeoMatrix4x4F_multiplyMatrix(GeoMatrix4x4F_t& first, const GeoMatrix4x4F_t& other) {
    NovelRT::Maths::GeoVector4<float> first_vX = NovelRT::Maths::GeoVector4<float>(first.x.x, first.x.y, first.x.z, first.x.w);
    NovelRT::Maths::GeoVector4<float> first_vY = NovelRT::Maths::GeoVector4<float>(first.y.x, first.y.y, first.y.z, first.y.w);
    NovelRT::Maths::GeoVector4<float> first_vZ = NovelRT::Maths::GeoVector4<float>(first.z.x, first.z.y, first.z.z, first.z.w);
    NovelRT::Maths::GeoVector4<float> first_vW = NovelRT::Maths::GeoVector4<float>(first.w.x, first.w.y, first.w.z, first.w.w);

    NovelRT::Maths::GeoVector4<float> other_vX = NovelRT::Maths::GeoVector4<float>(other.x.x, other.x.y, other.x.z, other.x.w);
    NovelRT::Maths::GeoVector4<float> other_vY = NovelRT::Maths::GeoVector4<float>(other.y.x, other.y.y, other.y.z, other.y.w);
    NovelRT::Maths::GeoVector4<float> other_vZ = NovelRT::Maths::GeoVector4<float>(other.z.x, other.z.y, other.z.z, other.z.w);
    NovelRT::Maths::GeoVector4<float> other_vW = NovelRT::Maths::GeoVector4<float>(other.w.x, other.w.y, other.w.z, other.w.w);

    NovelRT::Maths::GeoMatrix4x4<float> result = NovelRT::Maths::GeoMatrix4x4<float>(first_vX, first_vY, first_vZ, first_vW)
      * NovelRT::Maths::GeoMatrix4x4<float>(other_vX, other_vY, other_vZ, other_vW);

    GeoVector4F_t vX = { result.getX().getX(), result.getX().getY(), result.getX().getZ(), result.getX().getW() };
    GeoVector4F_t vY = { result.getY().getX(), result.getY().getY(), result.getY().getZ(), result.getY().getW() };
    GeoVector4F_t vZ = { result.getZ().getX(), result.getZ().getY(), result.getZ().getZ(), result.getZ().getW() };
    GeoVector4F_t vW = { result.getW().getX(), result.getW().getY(), result.getW().getZ(), result.getW().getW() };

    return { vX, vY, vZ, vW };
  }

  inline GeoMatrix4x4F_t GeoMatrix4x4F_addIntoMatrix(GeoMatrix4x4F_t& first, const GeoMatrix4x4F_t& other) {
    NovelRT::Maths::GeoVector4<float> first_vX = NovelRT::Maths::GeoVector4<float>(first.x.x, first.x.y, first.x.z, first.x.w);
    NovelRT::Maths::GeoVector4<float> first_vY = NovelRT::Maths::GeoVector4<float>(first.y.x, first.y.y, first.y.z, first.y.w);
    NovelRT::Maths::GeoVector4<float> first_vZ = NovelRT::Maths::GeoVector4<float>(first.z.x, first.z.y, first.z.z, first.z.w);
    NovelRT::Maths::GeoVector4<float> first_vW = NovelRT::Maths::GeoVector4<float>(first.w.x, first.w.y, first.w.z, first.w.w);

    NovelRT::Maths::GeoVector4<float> other_vX = NovelRT::Maths::GeoVector4<float>(other.x.x, other.x.y, other.x.z, other.x.w);
    NovelRT::Maths::GeoVector4<float> other_vY = NovelRT::Maths::GeoVector4<float>(other.y.x, other.y.y, other.y.z, other.y.w);
    NovelRT::Maths::GeoVector4<float> other_vZ = NovelRT::Maths::GeoVector4<float>(other.z.x, other.z.y, other.z.z, other.z.w);
    NovelRT::Maths::GeoVector4<float> other_vW = NovelRT::Maths::GeoVector4<float>(other.w.x, other.w.y, other.w.z, other.w.w);

    NovelRT::Maths::GeoMatrix4x4<float> matrix = NovelRT::Maths::GeoMatrix4x4<float>(first_vX, first_vY, first_vZ, first_vW);
    matrix += NovelRT::Maths::GeoMatrix4x4<float>(other_vX, other_vY, other_vZ, other_vW);

    GeoVector4F_t vX = { matrix.getX().getX(), matrix.getX().getY(), matrix.getX().getZ(), matrix.getX().getW() };
    GeoVector4F_t vY = { matrix.getY().getX(), matrix.getY().getY(), matrix.getY().getZ(), matrix.getY().getW() };
    GeoVector4F_t vZ = { matrix.getZ().getX(), matrix.getZ().getY(), matrix.getZ().getZ(), matrix.getZ().getW() };
    GeoVector4F_t vW = { matrix.getW().getX(), matrix.getW().getY(), matrix.getW().getZ(), matrix.getW().getW() };

    first = { vX, vY, vZ, vW };

    return first;
  }

  inline GeoMatrix4x4F_t GeoMatrix4x4F_subtractFromMatrix(GeoMatrix4x4F_t& first, const GeoMatrix4x4F_t& other) {
    NovelRT::Maths::GeoVector4<float> first_vX = NovelRT::Maths::GeoVector4<float>(first.x.x, first.x.y, first.x.z, first.x.w);
    NovelRT::Maths::GeoVector4<float> first_vY = NovelRT::Maths::GeoVector4<float>(first.y.x, first.y.y, first.y.z, first.y.w);
    NovelRT::Maths::GeoVector4<float> first_vZ = NovelRT::Maths::GeoVector4<float>(first.z.x, first.z.y, first.z.z, first.z.w);
    NovelRT::Maths::GeoVector4<float> first_vW = NovelRT::Maths::GeoVector4<float>(first.w.x, first.w.y, first.w.z, first.w.w);

    NovelRT::Maths::GeoVector4<float> other_vX = NovelRT::Maths::GeoVector4<float>(other.x.x, other.x.y, other.x.z, other.x.w);
    NovelRT::Maths::GeoVector4<float> other_vY = NovelRT::Maths::GeoVector4<float>(other.y.x, other.y.y, other.y.z, other.y.w);
    NovelRT::Maths::GeoVector4<float> other_vZ = NovelRT::Maths::GeoVector4<float>(other.z.x, other.z.y, other.z.z, other.z.w);
    NovelRT::Maths::GeoVector4<float> other_vW = NovelRT::Maths::GeoVector4<float>(other.w.x, other.w.y, other.w.z, other.w.w);

    NovelRT::Maths::GeoMatrix4x4<float> matrix = NovelRT::Maths::GeoMatrix4x4<float>(first_vX, first_vY, first_vZ, first_vW);
    matrix -= NovelRT::Maths::GeoMatrix4x4<float>(other_vX, other_vY, other_vZ, other_vW);

    GeoVector4F_t vX = { matrix.getX().getX(), matrix.getX().getY(), matrix.getX().getZ(), matrix.getX().getW() };
    GeoVector4F_t vY = { matrix.getY().getX(), matrix.getY().getY(), matrix.getY().getZ(), matrix.getY().getW() };
    GeoVector4F_t vZ = { matrix.getZ().getX(), matrix.getZ().getY(), matrix.getZ().getZ(), matrix.getZ().getW() };
    GeoVector4F_t vW = { matrix.getW().getX(), matrix.getW().getY(), matrix.getW().getZ(), matrix.getW().getW() };

    first = { vX, vY, vZ, vW };

    return first;
  }

  inline GeoMatrix4x4F_t GeoMatrix4x4F_multiplyIntoMatrix(GeoMatrix4x4F_t& first, const GeoMatrix4x4F_t& other) {
    NovelRT::Maths::GeoVector4<float> first_vX = NovelRT::Maths::GeoVector4<float>(first.x.x, first.x.y, first.x.z, first.x.w);
    NovelRT::Maths::GeoVector4<float> first_vY = NovelRT::Maths::GeoVector4<float>(first.y.x, first.y.y, first.y.z, first.y.w);
    NovelRT::Maths::GeoVector4<float> first_vZ = NovelRT::Maths::GeoVector4<float>(first.z.x, first.z.y, first.z.z, first.z.w);
    NovelRT::Maths::GeoVector4<float> first_vW = NovelRT::Maths::GeoVector4<float>(first.w.x, first.w.y, first.w.z, first.w.w);

    NovelRT::Maths::GeoVector4<float> other_vX = NovelRT::Maths::GeoVector4<float>(other.x.x, other.x.y, other.x.z, other.x.w);
    NovelRT::Maths::GeoVector4<float> other_vY = NovelRT::Maths::GeoVector4<float>(other.y.x, other.y.y, other.y.z, other.y.w);
    NovelRT::Maths::GeoVector4<float> other_vZ = NovelRT::Maths::GeoVector4<float>(other.z.x, other.z.y, other.z.z, other.z.w);
    NovelRT::Maths::GeoVector4<float> other_vW = NovelRT::Maths::GeoVector4<float>(other.w.x, other.w.y, other.w.z, other.w.w);

    NovelRT::Maths::GeoMatrix4x4<float> matrix = NovelRT::Maths::GeoMatrix4x4<float>(first_vX, first_vY, first_vZ, first_vW);
    matrix *= NovelRT::Maths::GeoMatrix4x4<float>(other_vX, other_vY, other_vZ, other_vW);

    GeoVector4F_t vX = { matrix.getX().getX(), matrix.getX().getY(), matrix.getX().getZ(), matrix.getX().getW() };
    GeoVector4F_t vY = { matrix.getY().getX(), matrix.getY().getY(), matrix.getY().getZ(), matrix.getY().getW() };
    GeoVector4F_t vZ = { matrix.getZ().getX(), matrix.getZ().getY(), matrix.getZ().getZ(), matrix.getZ().getW() };
    GeoVector4F_t vW = { matrix.getW().getX(), matrix.getW().getY(), matrix.getW().getZ(), matrix.getW().getW() };

    first = { vX, vY, vZ, vW };

    return first;
  }

  inline GeoMatrix4x4F_t GeoMatrix4x4F_addFloat(GeoMatrix4x4F_t& matrix, float value) {
    NovelRT::Maths::GeoVector4<float> matrix_vX = NovelRT::Maths::GeoVector4<float>(matrix.x.x, matrix.x.y, matrix.x.z, matrix.x.w);
    NovelRT::Maths::GeoVector4<float> matrix_vY = NovelRT::Maths::GeoVector4<float>(matrix.y.x, matrix.y.y, matrix.y.z, matrix.y.w);
    NovelRT::Maths::GeoVector4<float> matrix_vZ = NovelRT::Maths::GeoVector4<float>(matrix.z.x, matrix.z.y, matrix.z.z, matrix.z.w);
    NovelRT::Maths::GeoVector4<float> matrix_vW = NovelRT::Maths::GeoVector4<float>(matrix.w.x, matrix.w.y, matrix.w.z, matrix.w.w);

    NovelRT::Maths::GeoMatrix4x4<float> result = NovelRT::Maths::GeoMatrix4x4<float>(matrix_vX, matrix_vY, matrix_vZ, matrix_vW) + value;

    GeoVector4F_t vX = { result.getX().getX(), result.getX().getY(), result.getX().getZ(), result.getX().getW() };
    GeoVector4F_t vY = { result.getY().getX(), result.getY().getY(), result.getY().getZ(), result.getY().getW() };
    GeoVector4F_t vZ = { result.getZ().getX(), result.getZ().getY(), result.getZ().getZ(), result.getZ().getW() };
    GeoVector4F_t vW = { result.getW().getX(), result.getW().getY(), result.getW().getZ(), result.getW().getW() };

    return { vX, vY, vZ, vW };
  }

  inline GeoMatrix4x4F_t GeoMatrix4x4F_subtractFloat(GeoMatrix4x4F_t& matrix, float value) {
    NovelRT::Maths::GeoVector4<float> matrix_vX = NovelRT::Maths::GeoVector4<float>(matrix.x.x, matrix.x.y, matrix.x.z, matrix.x.w);
    NovelRT::Maths::GeoVector4<float> matrix_vY = NovelRT::Maths::GeoVector4<float>(matrix.y.x, matrix.y.y, matrix.y.z, matrix.y.w);
    NovelRT::Maths::GeoVector4<float> matrix_vZ = NovelRT::Maths::GeoVector4<float>(matrix.z.x, matrix.z.y, matrix.z.z, matrix.z.w);
    NovelRT::Maths::GeoVector4<float> matrix_vW = NovelRT::Maths::GeoVector4<float>(matrix.w.x, matrix.w.y, matrix.w.z, matrix.w.w);

    NovelRT::Maths::GeoMatrix4x4<float> result = NovelRT::Maths::GeoMatrix4x4<float>(matrix_vX, matrix_vY, matrix_vZ, matrix_vW) - value;

    GeoVector4F_t vX = { result.getX().getX(), result.getX().getY(), result.getX().getZ(), result.getX().getW() };
    GeoVector4F_t vY = { result.getY().getX(), result.getY().getY(), result.getY().getZ(), result.getY().getW() };
    GeoVector4F_t vZ = { result.getZ().getX(), result.getZ().getY(), result.getZ().getZ(), result.getZ().getW() };
    GeoVector4F_t vW = { result.getW().getX(), result.getW().getY(), result.getW().getZ(), result.getW().getW() };

    return { vX, vY, vZ, vW };
  }

  inline GeoMatrix4x4F_t GeoMatrix4x4F_multiplyFloat(GeoMatrix4x4F_t& matrix, float value) {
    NovelRT::Maths::GeoVector4<float> matrix_vX = NovelRT::Maths::GeoVector4<float>(matrix.x.x, matrix.x.y, matrix.x.z, matrix.x.w);
    NovelRT::Maths::GeoVector4<float> matrix_vY = NovelRT::Maths::GeoVector4<float>(matrix.y.x, matrix.y.y, matrix.y.z, matrix.y.w);
    NovelRT::Maths::GeoVector4<float> matrix_vZ = NovelRT::Maths::GeoVector4<float>(matrix.z.x, matrix.z.y, matrix.z.z, matrix.z.w);
    NovelRT::Maths::GeoVector4<float> matrix_vW = NovelRT::Maths::GeoVector4<float>(matrix.w.x, matrix.w.y, matrix.w.z, matrix.w.w);

    NovelRT::Maths::GeoMatrix4x4<float> result = NovelRT::Maths::GeoMatrix4x4<float>(matrix_vX, matrix_vY, matrix_vZ, matrix_vW) * value;

    GeoVector4F_t vX = { result.getX().getX(), result.getX().getY(), result.getX().getZ(), result.getX().getW() };
    GeoVector4F_t vY = { result.getY().getX(), result.getY().getY(), result.getY().getZ(), result.getY().getW() };
    GeoVector4F_t vZ = { result.getZ().getX(), result.getZ().getY(), result.getZ().getZ(), result.getZ().getW() };
    GeoVector4F_t vW = { result.getW().getX(), result.getW().getY(), result.getW().getZ(), result.getW().getW() };

    return { vX, vY, vZ, vW };
  }

  inline GeoMatrix4x4F_t GeoMatrix4x4F_addFloatIntoVector(GeoMatrix4x4F_t& matrix, float value) {
    NovelRT::Maths::GeoVector4<float> matrix_vX = NovelRT::Maths::GeoVector4<float>(matrix.x.x, matrix.x.y, matrix.x.z, matrix.x.w);
    NovelRT::Maths::GeoVector4<float> matrix_vY = NovelRT::Maths::GeoVector4<float>(matrix.y.x, matrix.y.y, matrix.y.z, matrix.y.w);
    NovelRT::Maths::GeoVector4<float> matrix_vZ = NovelRT::Maths::GeoVector4<float>(matrix.z.x, matrix.z.y, matrix.z.z, matrix.z.w);
    NovelRT::Maths::GeoVector4<float> matrix_vW = NovelRT::Maths::GeoVector4<float>(matrix.w.x, matrix.w.y, matrix.w.z, matrix.w.w);

    NovelRT::Maths::GeoMatrix4x4<float> result = NovelRT::Maths::GeoMatrix4x4<float>(matrix_vX, matrix_vY, matrix_vZ, matrix_vW);
    result += value;

    GeoVector4F_t vX = { result.getX().getX(), result.getX().getY(), result.getX().getZ(), result.getX().getW() };
    GeoVector4F_t vY = { result.getY().getX(), result.getY().getY(), result.getY().getZ(), result.getY().getW() };
    GeoVector4F_t vZ = { result.getZ().getX(), result.getZ().getY(), result.getZ().getZ(), result.getZ().getW() };
    GeoVector4F_t vW = { result.getW().getX(), result.getW().getY(), result.getW().getZ(), result.getW().getW() };

    matrix = { vX, vY, vZ, vW };

    return matrix;
  }

  inline GeoMatrix4x4F_t GeoMatrix4x4F_subFloatFromVector(GeoMatrix4x4F_t& matrix, float value) {
    NovelRT::Maths::GeoVector4<float> matrix_vX = NovelRT::Maths::GeoVector4<float>(matrix.x.x, matrix.x.y, matrix.x.z, matrix.x.w);
    NovelRT::Maths::GeoVector4<float> matrix_vY = NovelRT::Maths::GeoVector4<float>(matrix.y.x, matrix.y.y, matrix.y.z, matrix.y.w);
    NovelRT::Maths::GeoVector4<float> matrix_vZ = NovelRT::Maths::GeoVector4<float>(matrix.z.x, matrix.z.y, matrix.z.z, matrix.z.w);
    NovelRT::Maths::GeoVector4<float> matrix_vW = NovelRT::Maths::GeoVector4<float>(matrix.w.x, matrix.w.y, matrix.w.z, matrix.w.w);

    NovelRT::Maths::GeoMatrix4x4<float> result = NovelRT::Maths::GeoMatrix4x4<float>(matrix_vX, matrix_vY, matrix_vZ, matrix_vW);
    result -= value;

    GeoVector4F_t vX = { result.getX().getX(), result.getX().getY(), result.getX().getZ(), result.getX().getW() };
    GeoVector4F_t vY = { result.getY().getX(), result.getY().getY(), result.getY().getZ(), result.getY().getW() };
    GeoVector4F_t vZ = { result.getZ().getX(), result.getZ().getY(), result.getZ().getZ(), result.getZ().getW() };
    GeoVector4F_t vW = { result.getW().getX(), result.getW().getY(), result.getW().getZ(), result.getW().getW() };

    matrix = { vX, vY, vZ, vW };

    return matrix;
  }

  inline GeoMatrix4x4F_t GeoMatrix4x4F_multiplyFloatIntoVector(GeoMatrix4x4F_t& matrix, float value) {
    NovelRT::Maths::GeoVector4<float> matrix_vX = NovelRT::Maths::GeoVector4<float>(matrix.x.x, matrix.x.y, matrix.x.z, matrix.x.w);
    NovelRT::Maths::GeoVector4<float> matrix_vY = NovelRT::Maths::GeoVector4<float>(matrix.y.x, matrix.y.y, matrix.y.z, matrix.y.w);
    NovelRT::Maths::GeoVector4<float> matrix_vZ = NovelRT::Maths::GeoVector4<float>(matrix.z.x, matrix.z.y, matrix.z.z, matrix.z.w);
    NovelRT::Maths::GeoVector4<float> matrix_vW = NovelRT::Maths::GeoVector4<float>(matrix.w.x, matrix.w.y, matrix.w.z, matrix.w.w);

    NovelRT::Maths::GeoMatrix4x4<float> result = NovelRT::Maths::GeoMatrix4x4<float>(matrix_vX, matrix_vY, matrix_vZ, matrix_vW);
    result *= value;

    GeoVector4F_t vX = { result.getX().getX(), result.getX().getY(), result.getX().getZ(), result.getX().getW() };
    GeoVector4F_t vY = { result.getY().getX(), result.getY().getY(), result.getY().getZ(), result.getY().getW() };
    GeoVector4F_t vZ = { result.getZ().getX(), result.getZ().getY(), result.getZ().getZ(), result.getZ().getW() };
    GeoVector4F_t vW = { result.getW().getX(), result.getW().getY(), result.getW().getZ(), result.getW().getW() };

    matrix = { vX, vY, vZ, vW };

    return matrix;
  }

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_MATHS_GEOMATRIX4X4F_T_H
