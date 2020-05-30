// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <NovelRT.h>
#include "NovelRTInterop/Maths/GeoVector3F_t.h"

#ifndef NOVELRT_MATHS_GEOVECTOR3F_H
#define NOVELRT_MATHS_GEOVECTOR3F_H

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

GeoVector3F_t* GeoVector3F_create(float x, float y, float z) {
	static Maths::GeoVector3<float> vector = { x, y, z };
	return reinterpret_cast<GeoVector3F_t*>(&vector);
}

GeoVector3F_t* GeoVector3F_createFromGeoVector2F(const GeoVector2F_t* vector) {
	Maths::GeoVector2<float>* cVector2 = reinterpret_cast<Maths::GeoVector2<float>*>(&vector);
	static Maths::GeoVector3<float> vec = { cVector2->getX(), cVector2->getY(), 0.0f };
	return reinterpret_cast<GeoVector3F_t*>(&vec);
}

const GeoVector3F_t* GeoVector3F_uniform(float value) {
  return GeoVector3F_create(value, value, value);
}

const GeoVector3F_t* GeoVector3F_zero() {
  return GeoVector3F_uniform(0.0f);
}

const GeoVector3F_t* GeoVector3F_one() {
  return GeoVector3F_uniform(1.0f);
}

float GeoVector3F_getX(GeoVector3F_t* gv) {
	return reinterpret_cast<Maths::GeoVector3<float>*>(&gv)->getX();
}

void GeoVector3F_setX(GeoVector3F_t* gv, float value) {
	static Maths::GeoVector3<float> vec = *(reinterpret_cast<Maths::GeoVector3<float>*>(&gv));
	vec.setX(value);
	gv = reinterpret_cast<GeoVector3F_t*>(&vec);
}

float GeoVector3F_getY(GeoVector3F_t* gv) {
	return reinterpret_cast<Maths::GeoVector3<float>*>(&gv)->getY();
}

void GeoVector3F_setY(GeoVector3F_t* gv, float value) {
	static Maths::GeoVector3<float> vec = *(reinterpret_cast<Maths::GeoVector3<float>*>(&gv));
	vec.setY(value);
	gv = reinterpret_cast<GeoVector3F_t*>(&vec);
}

float GeoVector3F_getZ(GeoVector3F_t* gv) {
	return reinterpret_cast<Maths::GeoVector3<float>*>(&gv)->getY();
}

void GeoVector3F_setZ(GeoVector3F_t* gv, float value) {
	static Maths::GeoVector3<float> vec = *(reinterpret_cast<Maths::GeoVector3<float>*>(&gv));
	vec.setZ(value);
	gv = reinterpret_cast<GeoVector3F_t*>(&vec);
}

void GeoVector3F_rotateToAngleAroundPoint(float angleRotationValue, GeoVector3F_t* vector, const GeoVector3F_t* point) noexcept {
	static Maths::GeoVector3<float> cVector = *reinterpret_cast<Maths::GeoVector3<float>*>(vector);
	const Maths::GeoVector3<float> cPoint = *reinterpret_cast<const Maths::GeoVector3<float>*>(point);
	cVector.rotateToAngleAroundPoint(angleRotationValue, cPoint);
	vector = reinterpret_cast<GeoVector3F_t*>(&cVector);
}

bool GeoVector3F_epsilonEquals(GeoVector3F_t* vector, const GeoVector3F_t* other, const GeoVector3F_t* epsilonValue) noexcept {
  Maths::GeoVector3<float>v1 = *reinterpret_cast<Maths::GeoVector3<float>*>(vector);
  Maths::GeoVector3<float>v2 = *reinterpret_cast<const Maths::GeoVector3<float>*>(other);
  Maths::GeoVector3<float>v3 = *reinterpret_cast<const Maths::GeoVector3<float>*>(epsilonValue);
  return v1.epsilonEquals(v2, v3);
}

GeoVector3F_t* GeoVector3F_getNormalised(GeoVector3F_t* gv) {
	Maths::GeoVector3<float> geo = *reinterpret_cast<Maths::GeoVector3<float>*>(gv);
	static Maths::GeoVector3<float> normal = geo.getNormalised();
	return reinterpret_cast<GeoVector3F_t*>(&normal);
}

float GeoVector3F_getLength(GeoVector3F_t* gv) {
	Maths::GeoVector3<float> geo = *reinterpret_cast<Maths::GeoVector3<float>*>(gv);
  return geo.getLength();
}

float GeoVector3F_getMagnitude(GeoVector3F_t* gv) {
  return GeoVector3F_getLength(gv);
}

bool GeoVector3F_equal(const GeoVector3F_t* first, const GeoVector3F_t* other) {
	return *reinterpret_cast<const Maths::GeoVector3<float>*>(first) == *reinterpret_cast<const Maths::GeoVector3<float>*>(other);
}

bool GeoVector3F_notEqual(const GeoVector3F_t* first, const GeoVector3F_t* other) {
	return *reinterpret_cast<const Maths::GeoVector3<float>*>(first) != *reinterpret_cast<const Maths::GeoVector3<float>*>(other);
}

bool GeoVector3F_lessThan(const GeoVector3F_t* first, const GeoVector3F_t* other) {
	return *reinterpret_cast<const Maths::GeoVector3<float>*>(first) < *reinterpret_cast<const Maths::GeoVector3<float>*>(other);
}

bool GeoVector3F_lessThanOrEqualTo(const GeoVector3F_t* first, const GeoVector3F_t* other) {
	return *reinterpret_cast<const Maths::GeoVector3<float>*>(first) <= *reinterpret_cast<const Maths::GeoVector3<float>*>(other);
}

bool GeoVector3F_greaterThan(const GeoVector3F_t* first, const GeoVector3F_t* other) {
	return *reinterpret_cast<const Maths::GeoVector3<float>*>(first) > *reinterpret_cast<const Maths::GeoVector3<float>*>(other);
}

bool GeoVector3F_greaterThanOrEqualTo(const GeoVector3F_t* first, const GeoVector3F_t* other) {
	return *reinterpret_cast<const Maths::GeoVector3<float>*>(first) >= *reinterpret_cast<const Maths::GeoVector3<float>*>(other);
}

GeoVector3F_t* GeoVector3F_addVector(GeoVector3F_t* first, const GeoVector3F_t* other) {
  static NovelRT::Maths::GeoVector3<float> geo = *reinterpret_cast<const Maths::GeoVector3<float>*>(first) + *reinterpret_cast<const Maths::GeoVector3<float>*>(other);
  return reinterpret_cast<GeoVector3F_t*>(&geo);
}

GeoVector3F_t* GeoVector3F_subtractVector(GeoVector3F_t* first, const GeoVector3F_t* other) {
	static NovelRT::Maths::GeoVector3<float> geo = *reinterpret_cast<const Maths::GeoVector3<float>*>(first) - *reinterpret_cast<const Maths::GeoVector3<float>*>(other);
	return reinterpret_cast<GeoVector3F_t*>(&geo);
}

GeoVector3F_t* GeoVector3F_multiplyVector(GeoVector3F_t* first, const GeoVector3F_t* other) {
	static NovelRT::Maths::GeoVector3<float> geo = *reinterpret_cast<const Maths::GeoVector3<float>*>(first) * *reinterpret_cast<const Maths::GeoVector3<float>*>(other);
	return reinterpret_cast<GeoVector3F_t*>(&geo);
}

GeoVector3F_t* GeoVector3F_divideVector(GeoVector3F_t* first, const GeoVector3F_t* other) {
	static NovelRT::Maths::GeoVector3<float> geo = *reinterpret_cast<const Maths::GeoVector3<float>*>(first) / *reinterpret_cast<const Maths::GeoVector3<float>*>(other);
	return reinterpret_cast<GeoVector3F_t*>(&geo);
}

GeoVector3F_t* GeoVector3F_addFloat(GeoVector3F_t* vector, float value) {
	static NovelRT::Maths::GeoVector3<float> geo = *reinterpret_cast<const Maths::GeoVector3<float>*>(vector) + value;
	return reinterpret_cast<GeoVector3F_t*>(&geo);
}

GeoVector3F_t* GeoVector3F_subtractFloat(GeoVector3F_t* vector, float value) {
	static NovelRT::Maths::GeoVector3<float> geo = *reinterpret_cast<const Maths::GeoVector3<float>*>(vector) - value;
	return reinterpret_cast<GeoVector3F_t*>(&geo);
}

GeoVector3F_t* GeoVector3F_multiplyFloat(GeoVector3F_t* vector, float value) {
	static NovelRT::Maths::GeoVector3<float> geo = *reinterpret_cast<const Maths::GeoVector3<float>*>(vector) * value;
	return reinterpret_cast<GeoVector3F_t*>(&geo);
}

GeoVector3F_t* GeoVector3F_divideFloat(GeoVector3F_t* vector, float value) {
	static NovelRT::Maths::GeoVector3<float> geo = *reinterpret_cast<const Maths::GeoVector3<float>*>(vector) / value;
	return reinterpret_cast<GeoVector3F_t*>(&geo);
}

GeoVector3F_t* GeoVector3F_addIntoVector(GeoVector3F_t* first, const GeoVector3F_t* other) {
	static NovelRT::Maths::GeoVector3<float> geo = *reinterpret_cast<const Maths::GeoVector3<float>*>(first);
	geo += *reinterpret_cast<const Maths::GeoVector3<float>*>(other);
	first = reinterpret_cast<GeoVector3F_t*>(&geo);
	return first;
}

GeoVector3F_t* GeoVector3F_subtractFromVector(GeoVector3F_t* first, const GeoVector3F_t* other) {
	static NovelRT::Maths::GeoVector3<float> geo = *reinterpret_cast<const Maths::GeoVector3<float>*>(first);
	geo -= *reinterpret_cast<const Maths::GeoVector3<float>*>(other);
	first = reinterpret_cast<GeoVector3F_t*>(&geo);
	return first;
}

GeoVector3F_t* GeoVector3F_multiplyIntoVector(GeoVector3F_t* first, const GeoVector3F_t* other) {
	static NovelRT::Maths::GeoVector3<float> geo = *reinterpret_cast<const Maths::GeoVector3<float>*>(first);
	geo *= *reinterpret_cast<const Maths::GeoVector3<float>*>(other);
	first = reinterpret_cast<GeoVector3F_t*>(&geo);
	return first;
}

GeoVector3F_t* GeoVector3F_divideIntoVector(GeoVector3F_t* first, const GeoVector3F_t* other) {
	static NovelRT::Maths::GeoVector3<float> geo = *reinterpret_cast<const Maths::GeoVector3<float>*>(first);
	geo /= *reinterpret_cast<const Maths::GeoVector3<float>*>(other);
	first = reinterpret_cast<GeoVector3F_t*>(&geo);
	return first;
}

GeoVector3F_t* GeoVector3F_addFloatIntoVector(GeoVector3F_t* vector, float value) {
	static NovelRT::Maths::GeoVector3<float> geo = *reinterpret_cast<const Maths::GeoVector3<float>*>(vector);
	geo += value;
	vector = reinterpret_cast<GeoVector3F_t*>(&geo);
	return vector;
}

GeoVector3F_t* GeoVector3F_subFloatFromVector(GeoVector3F_t* vector, float value) {
	static NovelRT::Maths::GeoVector3<float> geo = *reinterpret_cast<const Maths::GeoVector3<float>*>(vector);
	geo -= value;
	vector = reinterpret_cast<GeoVector3F_t*>(&geo);
	return vector;
}

GeoVector3F_t* GeoVector3F_multiplyFloatIntoVector(GeoVector3F_t* vector, float value) {
	static NovelRT::Maths::GeoVector3<float> geo = *reinterpret_cast<const Maths::GeoVector3<float>*>(vector);
	geo *= value;
	vector = reinterpret_cast<GeoVector3F_t*>(&geo);
	return vector;
}

GeoVector3F_t* GeoVector3F_divideFloatIntoVector(GeoVector3F_t* vector, float value) {
	static NovelRT::Maths::GeoVector3<float> geo = *reinterpret_cast<const Maths::GeoVector3<float>*>(vector);
	geo /= value;
	vector = reinterpret_cast<GeoVector3F_t*>(&geo);
	return vector;
}

GeoVector3F_t* GeoVector3F_multiplyFloatIntoVectorInverse(float lhs, GeoVector3F_t* rhs) {
  return GeoVector3F_multiplyFloat(rhs, lhs);
}

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_MATHS_GEOVECTOR3F_H
