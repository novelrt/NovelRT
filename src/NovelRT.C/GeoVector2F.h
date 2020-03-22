// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.h"


#ifndef NOVELRT_MATHS_GEOVECTOR2F_H
#define NOVELRT_MATHS_GEOVECTOR2F_H

#ifdef __cplusplus
extern "C" {
#endif

 struct GeoVector2F {
   float x;
   float y;
 };

#ifdef WIN32
#define typeof _declspec()
#endif

 typedef struct GeoVector2F GeoVector2_t;

float GeoVector2F_getX(GeoVector2_t* gv);
void GeoVector2F_setX(GeoVector2_t* gv, float value);
float GeoVector2F_getY(GeoVector2_t* gv);
void GeoVector2F_setY(GeoVector2_t* gv, float value);

inline GeoVector2_t GeoVector2F_getNormalised(GeoVector2_t& gv) {
  NovelRT::Maths::GeoVector2<float> geo = NovelRT::Maths::GeoVector2<float>(gv.x, gv.y).getNormalised();
  GeoVector2_t normal = {geo.getX(), geo.getY()};
  return normal;
}

inline float GeoVector2F_getLength(GeoVector2_t& gv) {
  NovelRT::Maths::GeoVector2<float> geo = NovelRT::Maths::GeoVector2<float>(gv.x, gv.y);
  return geo.getLength();
}

inline float GeoVector2F_getMagnitude(GeoVector2_t& gv) {
  return GeoVector2F_getLength(gv);
}

inline bool GeoVector2F_equal(GeoVector2_t& first, const GeoVector2_t& other) {
  return NovelRT::Maths::GeoVector2<float>(first.x, first.y) == NovelRT::Maths::GeoVector2<float>(other.x, other.y);
}

inline bool GeoVector2F_notEqual(GeoVector2_t& first, const GeoVector2_t& other) {
  return NovelRT::Maths::GeoVector2<float>(first.x, first.y) != NovelRT::Maths::GeoVector2<float>(other.x, other.y);
}

inline bool GeoVector2F_lessThan(GeoVector2_t& first, const GeoVector2_t& other) {
  return NovelRT::Maths::GeoVector2<float>(first.x, first.y) < NovelRT::Maths::GeoVector2<float>(other.x, other.y);
}

inline bool GeoVector2F_lessThanOrEqualTo(GeoVector2_t& first, const GeoVector2_t& other) {
  return NovelRT::Maths::GeoVector2<float>(first.x, first.y) <= NovelRT::Maths::GeoVector2<float>(other.x, other.y);
}

inline bool GeoVector2F_greaterThan(GeoVector2_t& first, const GeoVector2_t& other) {
  return NovelRT::Maths::GeoVector2<float>(first.x, first.y) > NovelRT::Maths::GeoVector2<float>(other.x, other.y);
}

inline bool GeoVector2F_greaterThanOrEqualTo(GeoVector2_t& first, const GeoVector2_t& other) {
  return NovelRT::Maths::GeoVector2<float>(first.x, first.y) >= NovelRT::Maths::GeoVector2<float>(other.x, other.y);
}

inline GeoVector2_t GeoVector2F_addVector(GeoVector2_t& first, const GeoVector2_t& other) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<float>(first.x,first.y) + NovelRT::Maths::GeoVector2<float>(other.x, other.y);
  first.x = geo.getX();
  first.y = geo.getY();
  return first;
}

inline GeoVector2_t GeoVector2F_subtractVector(GeoVector2_t& first, const GeoVector2_t& other) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<float>(first.x, first.y) - NovelRT::Maths::GeoVector2<float>(other.x, other.y);
  first.x = geo.getX();
  first.y = geo.getY();
  return first;
}

inline GeoVector2_t GeoVector2F_multiplyVector(GeoVector2_t& first, const GeoVector2_t& other) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<float>(first.x, first.y) * NovelRT::Maths::GeoVector2<float>(other.x, other.y);
  first.x = geo.getX();
  first.y = geo.getY();
  return first;
}

inline GeoVector2_t GeoVector2F_divideVector(GeoVector2_t& first, const GeoVector2_t& other) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<float>(first.x, first.y) / NovelRT::Maths::GeoVector2<float>(other.x, other.y);
  first.x = geo.getX();
  first.y = geo.getY();
  return first;
}

inline GeoVector2_t GeoVector2F_addFloat(GeoVector2_t& vector, float value) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<float>(vector.x, vector.y) + value;
  vector.x = geo.getX();
  vector.y = geo.getY();
  return vector;
}

inline GeoVector2_t GeoVector2F_subtractFloat(GeoVector2_t& vector, float value) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<float>(vector.x, vector.y) - value;
  vector.x = geo.getX();
  vector.y = geo.getY();
  return vector;
}

inline GeoVector2_t GeoVector2F_multiplyFloat(GeoVector2_t& vector, float value) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<float>(vector.x, vector.y) * value;
  vector.x = geo.getX();
  vector.y = geo.getY();
  return vector;
}

GeoVector2_t GeoVector2F_divideFloat(GeoVector2_t& vector, float value) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<float>(vector.x, vector.y) / value;
  vector.x = geo.getX();
  vector.y = geo.getY();
  return vector;
}

inline GeoVector2_t GeoVector2F_addIntoVector(GeoVector2_t& first, const GeoVector2_t& other) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<float>(first.x, first.y);
  geo += NovelRT::Maths::GeoVector2<float>(other.x, other.y);
  first.x = geo.getX();
  first.y = geo.getY();
  return first;
}

inline GeoVector2_t GeoVector2F_subtractFromVector(GeoVector2_t& first, const GeoVector2_t& other) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<float>(first.x, first.y);
  geo -= NovelRT::Maths::GeoVector2<float>(other.x, other.y);
  first.x = geo.getX();
  first.y = geo.getY();
  return first;
}

inline GeoVector2_t GeoVector2F_multiplyIntoVector(GeoVector2_t& first, const GeoVector2_t& other) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<float>(first.x, first.y);
  geo *= NovelRT::Maths::GeoVector2<float>(other.x, other.y);
  first.x = geo.getX();
  first.y = geo.getY();
  return first;
}

GeoVector2_t GeoVector2F_divideIntoVector(GeoVector2_t& first, const GeoVector2_t& other) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<float>(first.x, first.y);
  geo /= NovelRT::Maths::GeoVector2<float>(other.x, other.y);
  first.x = geo.getX();
  first.y = geo.getY();
  return first;
}

inline GeoVector2_t GeoVector2F_addFloatIntoVector(GeoVector2_t& vector, float value) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<float>(vector.x, vector.y);
  geo += value;
  vector.x = geo.getX();
  vector.y = geo.getY();
  return vector;
}

inline GeoVector2_t GeoVector2F_subFloatFromVector(GeoVector2_t& vector, float value) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<float>(vector.x, vector.y);
  geo -= value;
  vector.x = geo.getX();
  vector.y = geo.getY();
  return vector;
}

inline GeoVector2_t GeoVector2F_multiplyFloatIntoVector(GeoVector2_t& vector, float value) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<float>(vector.x, vector.y);
  geo *= value;
  vector.x = geo.getX();
  vector.y = geo.getY();
  return vector;
}

inline GeoVector2_t GeoVector2F_divideFloatIntoVector(GeoVector2_t& vector, float value) {
  NovelRT::Maths::GeoVector2 geo = NovelRT::Maths::GeoVector2<float>(vector.x, vector.y);
  geo /= value;
  vector.x = geo.getX();
  vector.y = geo.getY();
  return vector;
}

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_MATHS_GEOVECTOR2F_H
