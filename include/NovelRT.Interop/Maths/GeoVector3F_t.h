// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_MATHS_GEOVECTOR3F_H
#define NOVELRT_INTEROP_MATHS_GEOVECTOR3F_H

#ifdef __cplusplus
extern "C" {
#endif

  struct GeoVector3F_t
  {
    float x;
    float y;
    float z;
  };

  GeoVector3F_t GeoVector3F_create(float x, float y, float z);
  GeoVector3F_t GeoVector3F_createFromGeoVector3F(const GeoVector3F_t& vector);
  GeoVector3F_t GeoVector3F_uniform(float value);
  GeoVector3F_t GeoVector3F_zero();
  GeoVector3F_t GeoVector3F_one();
  float GeoVector3F_getX(GeoVector3F_t& gv);
  void GeoVector3F_setX(GeoVector3F_t& gv, float value);
  float GeoVector3F_getY(GeoVector3F_t& gv);
  void GeoVector3F_setY(GeoVector3F_t& gv, float value);
  float GeoVector3F_getZ(GeoVector3F_t& gv);
  void GeoVector3F_setZ(GeoVector3F_t& gv, float value);
  void GeoVector3F_rotateToAngleAroundPoint(GeoVector3F_t& vector, float angleRotationValue, const GeoVector3F_t& point) noexcept; 
  bool GeoVector3F_epsilonEquals(const GeoVector3F_t& vector, const GeoVector3F_t& other, const GeoVector3F_t& epsilonValue) noexcept;
  GeoVector3F_t GeoVector3F_getNormalised(const GeoVector3F_t& vector);
  float GeoVector3F_getLength(const GeoVector3F_t& vector);
  float GeoVector3F_getMagnitude(const GeoVector3F_t& vector);
  bool GeoVector3F_equal(const GeoVector3F_t& first, const GeoVector3F_t& other);
  bool GeoVector3F_notEqual(const GeoVector3F_t& first, const GeoVector3F_t& other);
  bool GeoVector3F_lessThan(const GeoVector3F_t& first, const GeoVector3F_t& other);
  bool GeoVector3F_lessThanOrEqualTo(const GeoVector3F_t& first, const GeoVector3F_t& other);
  bool GeoVector3F_greaterThan(const GeoVector3F_t& first, const GeoVector3F_t& other);
  bool GeoVector3F_greaterThanOrEqualTo(const GeoVector3F_t& first, const GeoVector3F_t& other);
  GeoVector3F_t GeoVector3F_addVector(const GeoVector3F_t& first, const GeoVector3F_t& other);
  GeoVector3F_t GeoVector3F_subtractVector(const GeoVector3F_t& first, const GeoVector3F_t& other);
  GeoVector3F_t GeoVector3F_multiplyVector(const GeoVector3F_t& first, const GeoVector3F_t& other);
  GeoVector3F_t GeoVector3F_divideVector(const GeoVector3F_t& first, const GeoVector3F_t& other);
  GeoVector3F_t GeoVector3F_addFloat(const GeoVector3F_t& vector, float value);
  GeoVector3F_t GeoVector3F_subtractFloat(const GeoVector3F_t& vector, float value);
  GeoVector3F_t GeoVector3F_multiplyFloat(const GeoVector3F_t& vector, float value);
  GeoVector3F_t GeoVector3F_divideFloat(const GeoVector3F_t& vector, float value);
  void GeoVector3F_addIntoVector(GeoVector3F_t& first, const GeoVector3F_t& other);
  void GeoVector3F_subtractFromVector(GeoVector3F_t& first, const GeoVector3F_t& other);
  void GeoVector3F_multiplyIntoVector(GeoVector3F_t& first, const GeoVector3F_t& other);
  void GeoVector3F_divideIntoVector(GeoVector3F_t& first, const GeoVector3F_t& other);
  void GeoVector3F_addFloatIntoVector(GeoVector3F_t& vector, float value);
  void GeoVector3F_subFloatFromVector(GeoVector3F_t& vector, float value);
  void GeoVector3F_multiplyFloatIntoVector(GeoVector3F_t& vector, float value);
  void GeoVector3F_divideFloatIntoVector(GeoVector3F_t& vector, float value);
  GeoVector3F_t GeoVector3F_multiplyFloatInverse(float lhs, const GeoVector3F_t& rhs);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_MATHS_GEOVECTOR3F_H
