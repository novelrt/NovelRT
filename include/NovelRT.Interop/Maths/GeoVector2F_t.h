// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_MATHS_GEOVECTOR2F_H
#define NOVELRT_INTEROP_MATHS_GEOVECTOR2F_H

#ifdef __cplusplus
extern "C" {
#endif
  struct GeoVector2F_t
  {
    float x;
    float y;
  };

  GeoVector2F_t GeoVector2F_create(float x, float y);
  GeoVector2F_t GeoVector2F_uniform(float value);
  GeoVector2F_t GeoVector2F_zero();
  GeoVector2F_t GeoVector2F_one();
  float GeoVector2F_getX(GeoVector2F_t& gv);
  void GeoVector2F_setX(GeoVector2F_t& gv, float value);
  float GeoVector2F_getY(GeoVector2F_t& gv);
  void GeoVector2F_setY(GeoVector2F_t& gv, float value);
  void GeoVector2F_rotateToAngleAroundPoint(GeoVector2F_t& vector, float angleRotationValue, const GeoVector2F_t& point) noexcept;
  bool GeoVector2F_epsilonEquals(const GeoVector2F_t& vector, const GeoVector2F_t& other, const GeoVector2F_t& epsilonValue) noexcept;
  GeoVector2F_t GeoVector2F_getNormalised(const GeoVector2F_t& gv);
  float GeoVector2F_getLength(const GeoVector2F_t& gv);
  float GeoVector2F_getMagnitude(const GeoVector2F_t& gv);
  bool GeoVector2F_equal(const GeoVector2F_t& first, const GeoVector2F_t& other);
  bool GeoVector2F_notEqual(const GeoVector2F_t& first, const GeoVector2F_t& other);
  bool GeoVector2F_lessThan(const GeoVector2F_t& first, const GeoVector2F_t& other);
  bool GeoVector2F_lessThanOrEqualTo(const GeoVector2F_t& first, const GeoVector2F_t& other);
  bool GeoVector2F_greaterThan(const GeoVector2F_t& first, const GeoVector2F_t& other);
  bool GeoVector2F_greaterThanOrEqualTo(const GeoVector2F_t& first, const GeoVector2F_t& other);
  GeoVector2F_t GeoVector2F_addVector(const GeoVector2F_t& first, const GeoVector2F_t& other);
  GeoVector2F_t GeoVector2F_subtractVector(const GeoVector2F_t& first, const GeoVector2F_t& other);
  GeoVector2F_t GeoVector2F_multiplyVector(const GeoVector2F_t& first, const GeoVector2F_t& other);
  GeoVector2F_t GeoVector2F_divideVector(const GeoVector2F_t& first, const GeoVector2F_t& other);
  GeoVector2F_t GeoVector2F_addFloat(const GeoVector2F_t& vector, float value);
  GeoVector2F_t GeoVector2F_subtractFloat(const GeoVector2F_t& vector, float value);
  GeoVector2F_t GeoVector2F_multiplyFloat(const GeoVector2F_t& vector, float value);
  GeoVector2F_t GeoVector2F_divideFloat(const GeoVector2F_t& vector, float value);
  void GeoVector2F_addIntoVector(GeoVector2F_t& first, const GeoVector2F_t& other);
  void GeoVector2F_subtractFromVector(GeoVector2F_t& first, const GeoVector2F_t& other);
  void GeoVector2F_multiplyIntoVector(GeoVector2F_t& first, const GeoVector2F_t& other);
  void GeoVector2F_divideIntoVector(GeoVector2F_t& first, const GeoVector2F_t& other);
  void GeoVector2F_addFloatIntoVector(GeoVector2F_t& vector, float value);
  void GeoVector2F_subFloatFromVector(GeoVector2F_t& vector, float value);
  void GeoVector2F_multiplyFloatIntoVector(GeoVector2F_t& vector, float value);
  void GeoVector2F_divideFloatIntoVector(GeoVector2F_t& vector, float value);
  GeoVector2F_t GeoVector2F_multiplyFloatInverse(float lhs, const GeoVector2F_t& rhs);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_MATHS_GEOVECTOR2F_H
