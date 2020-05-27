// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.h"
#include "NovelRTInterop/Maths/GeoVector2F_t.h"

#ifdef __cplusplus
extern "C" {
  using namespace NovelRT;
#endif

   GeoVector2F_t* GeoVector2F_create(float x, float y) {
    return new Maths::GeoVector2<float>(x, y);
  }

  GeoVector2F_t* GeoVector2F_uniform(float value) {
    return new Maths::GeoVector2<float>(value, value);
  }

  GeoVector2F_t* GeoVector2F_zero() {
    return GeoVector2F_uniform(0.0f);
  }

  GeoVector2F_t* GeoVector2F_one() {
    return GeoVector2F_uniform(1.0f);
  }

  float GeoVector2F_getX(GeoVector2F_t* gv) {
    Maths::GeoVector2<float>* cVector = reinterpret_cast<Maths::GeoVector2<float>*>(gv);
    return cVector->getX();
  }

  void GeoVector2F_setX(GeoVector2F_t* gv, float value) {
    Maths::GeoVector2<float>* cVector = reinterpret_cast<Maths::GeoVector2<float>*>(gv);
    cVector->setX(value);
    gv = reinterpret_cast<GeoVector2F_t*>(cVector);
  }

  float GeoVector2F_getY(GeoVector2F_t* gv) {
    Maths::GeoVector2<float>* cVector = reinterpret_cast<Maths::GeoVector2<float>*>(gv);
    return cVector->getY();
  }

  void GeoVector2F_setY(GeoVector2F_t* gv, float value) {
    Maths::GeoVector2<float>* cVector = reinterpret_cast<Maths::GeoVector2<float>*>(gv);
    cVector->setY(value);
    gv = reinterpret_cast<GeoVector2F_t*>(cVector);
  }

  void GeoVector2F_rotateToAngleAroundPoint(GeoVector2F_t* vector, float angleRotationValue, GeoVector2F_t* point) noexcept {
    Maths::GeoVector2<float>* cVector = reinterpret_cast<Maths::GeoVector2<float>*>(vector);
    Maths::GeoVector2<float>* cPoint = reinterpret_cast<Maths::GeoVector2<float>*>(point);
    Maths::GeoVector2<float> realPoint = { cPoint->getX(), cPoint->getY() };
    cVector->rotateToAngleAroundPoint(angleRotationValue, realPoint);
    vector = reinterpret_cast<GeoVector2F_t*>(cVector);
  }

  bool GeoVector2F_epsilonEquals(GeoVector2F_t* vector, GeoVector2F_t* other, GeoVector2F_t* epsilonValue) noexcept {
    Maths::GeoVector2<float>* cVector = reinterpret_cast<Maths::GeoVector2<float>*>(vector);
    Maths::GeoVector2<float>* cOther = reinterpret_cast<Maths::GeoVector2<float>*>(other);
    Maths::GeoVector2<float>* cEpsilonValue = reinterpret_cast<Maths::GeoVector2<float>*>(epsilonValue);
    Maths::GeoVector2<float> realOther = { cOther->getX(), cOther->getY() };
    Maths::GeoVector2<float> realEpsilonValue = { cEpsilonValue->getX(), cEpsilonValue->getY() };
    return cVector->epsilonEquals(realOther, realEpsilonValue);
  }

  GeoVector2F_t* GeoVector2F_getNormalised(GeoVector2F_t* gv) {
    Maths::GeoVector2<float>* cVector = reinterpret_cast<Maths::GeoVector2<float>*>(gv);
    static Maths::GeoVector2<float> normal = cVector->getNormalised();
    return reinterpret_cast<GeoVector2F_t*>(&normal);
  }

  float GeoVector2F_getLength(GeoVector2F_t* gv) {
    Maths::GeoVector2<float>* cVector = reinterpret_cast<Maths::GeoVector2<float>*>(gv);
    return cVector->getLength();
  }

  float GeoVector2F_getMagnitude(GeoVector2F_t* gv) {
    Maths::GeoVector2<float>* cVector = reinterpret_cast<Maths::GeoVector2<float>*>(gv);
    return cVector->getMagnitude();
  }

  bool GeoVector2F_equal(const GeoVector2F_t* first, const GeoVector2F_t* other) {
    Maths::GeoVector2<float> cFirst = *(reinterpret_cast<const Maths::GeoVector2<float>*>(first));
    Maths::GeoVector2<float> cOther = *(reinterpret_cast<const Maths::GeoVector2<float>*>(other));
    return cFirst == cOther;
  }

  bool GeoVector2F_notEqual(const GeoVector2F_t* first, const GeoVector2F_t* other) {
    Maths::GeoVector2<float> cFirst = *(reinterpret_cast<const Maths::GeoVector2<float>*>(first));
    Maths::GeoVector2<float> cOther = *(reinterpret_cast<const Maths::GeoVector2<float>*>(other));
    return cFirst != cOther;
  }

  bool GeoVector2F_lessThan(const GeoVector2F_t* first, const GeoVector2F_t* other) {
    Maths::GeoVector2<float> cFirst = *(reinterpret_cast<const Maths::GeoVector2<float>*>(first));
    Maths::GeoVector2<float> cOther = *(reinterpret_cast<const Maths::GeoVector2<float>*>(other));
    return cFirst < cOther;
  }

  bool GeoVector2F_lessThanOrEqualTo(const GeoVector2F_t* first, const GeoVector2F_t* other) {
    Maths::GeoVector2<float> cFirst = *(reinterpret_cast<const Maths::GeoVector2<float>*>(first));
    Maths::GeoVector2<float> cOther = *(reinterpret_cast<const Maths::GeoVector2<float>*>(other));
    return cFirst <= cOther;
  }

  bool GeoVector2F_greaterThan(const GeoVector2F_t* first, const GeoVector2F_t* other) {
    Maths::GeoVector2<float> cFirst = *(reinterpret_cast<const Maths::GeoVector2<float>*>(first));
    Maths::GeoVector2<float> cOther = *(reinterpret_cast<const Maths::GeoVector2<float>*>(other));
    return cFirst > cOther;
  }

  bool GeoVector2F_greaterThanOrEqualTo(const GeoVector2F_t* first, const GeoVector2F_t* other) {
    Maths::GeoVector2<float> cFirst = *(reinterpret_cast<const Maths::GeoVector2<float>*>(first));
    Maths::GeoVector2<float> cOther = *(reinterpret_cast<const Maths::GeoVector2<float>*>(other));
    return cFirst >= cOther;
  }

  GeoVector2F_t* GeoVector2F_addVector(GeoVector2F_t* first, const GeoVector2F_t* other) {
    Maths::GeoVector2<float> cFirst = *reinterpret_cast<Maths::GeoVector2<float>*>(first);
    Maths::GeoVector2<float> cOther = *reinterpret_cast<const Maths::GeoVector2<float>*>(other);
    static Maths::GeoVector2<float> newVector = (cFirst + cOther);
    return reinterpret_cast<GeoVector2F_t*>(&newVector);
  }

  GeoVector2F_t* GeoVector2F_subtractVector(GeoVector2F_t* first, const GeoVector2F_t* other) {
    Maths::GeoVector2<float> cFirst = *reinterpret_cast<Maths::GeoVector2<float>*>(first);
    Maths::GeoVector2<float> cOther = *reinterpret_cast<const Maths::GeoVector2<float>*>(other);
    static Maths::GeoVector2<float> newVector = (cFirst - cOther);
    return reinterpret_cast<GeoVector2F_t*>(&newVector);
  }

  GeoVector2F_t* GeoVector2F_multiplyVector(GeoVector2F_t* first, const GeoVector2F_t* other) {
    Maths::GeoVector2<float> cFirst = *reinterpret_cast<Maths::GeoVector2<float>*>(first);
    Maths::GeoVector2<float> cOther = *reinterpret_cast<const Maths::GeoVector2<float>*>(other);
    static Maths::GeoVector2<float> newVector = (cFirst * cOther);
    return reinterpret_cast<GeoVector2F_t*>(&newVector);
  }

  GeoVector2F_t* GeoVector2F_divideVector(GeoVector2F_t* first, const GeoVector2F_t* other) {
    Maths::GeoVector2<float> cFirst = *reinterpret_cast<Maths::GeoVector2<float>*>(first);
    Maths::GeoVector2<float> cOther = *reinterpret_cast<const Maths::GeoVector2<float>*>(other);
    static Maths::GeoVector2<float> newVector = (cFirst / cOther);
    return reinterpret_cast<GeoVector2F_t*>(&newVector);
  }

  GeoVector2F_t* GeoVector2F_addFloat(GeoVector2F_t* vector, float value) {
    Maths::GeoVector2<float> cVector = *reinterpret_cast<Maths::GeoVector2<float>*>(vector);
    static Maths::GeoVector2<float> newVector = cVector + value;
    return reinterpret_cast<GeoVector2F_t*>(&newVector);
  }

  GeoVector2F_t* GeoVector2F_subtractFloat(GeoVector2F_t* vector, float value) {
    Maths::GeoVector2<float> cVector = *reinterpret_cast<Maths::GeoVector2<float>*>(vector);
    static Maths::GeoVector2<float> newVector = cVector - value;
    return reinterpret_cast<GeoVector2F_t*>(&newVector);
  }

  GeoVector2F_t* GeoVector2F_multiplyFloat(GeoVector2F_t* vector, float value) {
    Maths::GeoVector2<float> cVector = *reinterpret_cast<Maths::GeoVector2<float>*>(vector);
    static Maths::GeoVector2<float> newVector = cVector * value;
    return reinterpret_cast<GeoVector2F_t*>(&newVector);
  }

  GeoVector2F_t* GeoVector2F_divideFloat(GeoVector2F_t* vector, float value) {
    Maths::GeoVector2<float> cVector = *reinterpret_cast<Maths::GeoVector2<float>*>(vector);
    static Maths::GeoVector2<float> newVector = cVector / value;
    return reinterpret_cast<GeoVector2F_t*>(&newVector);
  }

  GeoVector2F_t* GeoVector2F_addIntoVector(GeoVector2F_t* first, const GeoVector2F_t* other) {
    static Maths::GeoVector2<float> cFirst = *reinterpret_cast<Maths::GeoVector2<float>*>(first);
    Maths::GeoVector2<float> cOther = *reinterpret_cast<const Maths::GeoVector2<float>*>(other);
    cFirst += cOther;
    first = reinterpret_cast<GeoVector2F_t*>(&cFirst);
    return first;
  }

  GeoVector2F_t* GeoVector2F_subtractFromVector(GeoVector2F_t* first, const GeoVector2F_t* other) {
    static Maths::GeoVector2<float> cFirst = *reinterpret_cast<Maths::GeoVector2<float>*>(first);
    Maths::GeoVector2<float> cOther = *reinterpret_cast<const Maths::GeoVector2<float>*>(other);
    cFirst -= cOther;
    first = reinterpret_cast<GeoVector2F_t*>(&cFirst);
    return first;
  }

  GeoVector2F_t* GeoVector2F_multiplyIntoVector(GeoVector2F_t* first, const GeoVector2F_t* other) {
    static Maths::GeoVector2<float> cFirst = *reinterpret_cast<Maths::GeoVector2<float>*>(first);
    Maths::GeoVector2<float> cOther = *reinterpret_cast<const Maths::GeoVector2<float>*>(other);
    cFirst *= cOther;
    first = reinterpret_cast<GeoVector2F_t*>(&cFirst);
    return first;
  }

  GeoVector2F_t* GeoVector2F_divideIntoVector(GeoVector2F_t* first, const GeoVector2F_t* other) {
    static Maths::GeoVector2<float> cFirst = *reinterpret_cast<Maths::GeoVector2<float>*>(first);
    Maths::GeoVector2<float> cOther = *reinterpret_cast<const Maths::GeoVector2<float>*>(other);
    cFirst /= cOther;
    first = reinterpret_cast<GeoVector2F_t*>(&cFirst);
    return first;
  }

  GeoVector2F_t* GeoVector2F_addFloatIntoVector(GeoVector2F_t* vector, float value) {
    static Maths::GeoVector2<float> cVector = *reinterpret_cast<Maths::GeoVector2<float>*>(vector);
    cVector += value;
    vector = reinterpret_cast<GeoVector2F_t*>(&cVector);
    return vector;
  }

  GeoVector2F_t* GeoVector2F_subFloatFromVector(GeoVector2F_t* vector, float value) {
    static Maths::GeoVector2<float> cVector = *reinterpret_cast<Maths::GeoVector2<float>*>(vector);
    cVector -= value;
    vector = reinterpret_cast<GeoVector2F_t*>(&cVector);
    return vector;
  }

  GeoVector2F_t* GeoVector2F_multiplyFloatIntoVector(GeoVector2F_t* vector, float value) {
    static Maths::GeoVector2<float> cVector = *reinterpret_cast<Maths::GeoVector2<float>*>(vector);
    cVector *= value;
    vector = reinterpret_cast<GeoVector2F_t*>(&cVector);
    return vector;
  }

  GeoVector2F_t* GeoVector2F_divideFloatIntoVector(GeoVector2F_t* vector, float value) {
    static Maths::GeoVector2<float> cVector = *reinterpret_cast<Maths::GeoVector2<float>*>(vector);
    cVector /= value;
    vector = reinterpret_cast<GeoVector2F_t*>(&cVector);
    return vector;
  }

  GeoVector2F_t* GeoVector2F_multiplyFloatInverse(float lhs, GeoVector2F_t* rhs) {
    Maths::GeoVector2<float> cRightHandSide = *reinterpret_cast<Maths::GeoVector2<float>*>(rhs);
    static Maths::GeoVector2<float> correctOrder = cRightHandSide * lhs;
    return reinterpret_cast<GeoVector2F_t*>(&correctOrder);
  }

#ifdef __cplusplus
}
#endif
