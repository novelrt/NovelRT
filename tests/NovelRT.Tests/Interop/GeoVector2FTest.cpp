// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include "NovelRT.Interop/Maths/NovelRTGeoVector2F.h"

using namespace NovelRT;
using namespace NovelRT::Maths;

NovelRTGeoVector2F vec2One = NovelRT_GeoVector2F_uniform(0.0);
NovelRTGeoVector2F vec2Two = NovelRT_GeoVector2F_uniform(0.0f);
NovelRTGeoVector2F vec2Three = NovelRT_GeoVector2F_uniform(1.0f);

TEST(InteropGeoVector2Test, equalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(vec2One, vec2Two));
}

TEST(InteropGeoVector2Test, inequalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(NovelRT_GeoVector2F_notEqual(vec2One, vec2Three));
}

TEST(InteropGeoVector2Test, lessThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(NovelRT_GeoVector2F_lessThan(vec2One, vec2Three));
}

TEST(InteropGeoVector2Test, lessOrEqualToThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(NovelRT_GeoVector2F_lessThanOrEqualTo(vec2One, vec2Three));
  EXPECT_TRUE(NovelRT_GeoVector2F_lessThanOrEqualTo(vec2Three, vec2Three));
}

TEST(InteropGeoVector2Test, greaterThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(NovelRT_GeoVector2F_greaterThan(vec2Three, vec2One));
}

TEST(InteropGeoVector2Test, greaterThanOrEqualToOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(NovelRT_GeoVector2F_greaterThanOrEqualTo(vec2Three, vec2One));
  EXPECT_TRUE(NovelRT_GeoVector2F_greaterThanOrEqualTo(vec2Three, vec2Three));
}

TEST(InteropGeoVector2Test, staticUniformCallReturnsGeoVector2WithUniformValues) {
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(1.0f), vec2Three));
}

TEST(InteropGeoVector2Test, staticZeroCallReturnsGeoVector2Zero) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_uniform(0.0f);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_zero(), test));
}

TEST(InteropGeoVector2Test, staticOneCallReturnsGeoVector2One) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_uniform(1.0f);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_one(), test));
}

TEST(InteropGeoVector2Test, addOperatorAddsCorrectlyForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_addVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);  
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(2.0f), result));
}

TEST(InteropGeoVector2Test, subtractOperatorSubtractsCorrectlyForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_subtractVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);  
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_zero(), result));
}

TEST(InteropGeoVector2Test, multiplyOperatorMultipliesCorrectlyForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_uniform(2.0f);
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_multiplyVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);  
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(4.0f), result));
}

TEST(InteropGeoVector2Test, divideOperatorDividesCorrectlyForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_uniform(4.0f);
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err = nullptr;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_divideVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);  
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_one(), result));
}

TEST(InteropGeoVector2Test, addOperatorAddsCorrectlyForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_addFloat(test, 1.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(2.0f), result));
}

TEST(InteropGeoVector2Test, subtractOperatorSubtractsCorrectlyForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_subtractFloat(test, 1.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_zero(), result));
}

TEST(InteropGeoVector2Test, multiplyOperatorMultipliesCorrectlyForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_uniform(2.0f);
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_multiplyFloat(test, 2.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(4.0f), result));
}

TEST(InteropGeoVector2Test, divideOperatorDividesCorrectlyForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_uniform(4.0f);
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_divideFloat(test, 2.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(2.0f), result));
}

TEST(InteropGeoVector2Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_addAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(2.0f), test));
}

TEST(InteropGeoVector2Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_subtractAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_zero(), test));
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_uniform(2.0f);

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_multiplyAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(4.0f), test));
}

TEST(InteropGeoVector2Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_uniform(2.0f);

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_divideAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_one(), test));
}

TEST(InteropGeoVector2Test, addAssignOperatorAddsAndAssignsCorrectlyForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_addAssignFloat(&test, 1.0f, &err);
  
  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(2.0f), test));
}

TEST(InteropGeoVector2Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_subtractAssignFloat(&test, 1.0f, &err);
  
  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(0.0f), test));
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_uniform(2.0f);

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_multiplyAssignFloat(&test, 1.0f, &err);
  
  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(2.0f), test));
}

TEST(InteropGeoVector2Test, divideAssignOperatorDividesAndAssignsCorrectlyForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_uniform(2.0f);

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_divideAssignFloat(&test, 2.0f, &err);
  
  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(1.0f), test));
}

TEST(InteropGeoVector2Test, getNormalisedReturnsNormalisedGeoVector) {
  NovelRTGeoVector2F cVector = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F normal = NovelRT_GeoVector2F_getNormalised(cVector);
  GeoVector2<float>& vec = reinterpret_cast<GeoVector2<float>&>(normal);
  float normalisedTotal = sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2));
  EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(InteropGeoVector2Test, getMagnitudeReturnsCorrectLength) {
  NovelRTGeoVector2F cVector = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F normal = NovelRT_GeoVector2F_getNormalised(cVector);
  GeoVector2<float>& vec = reinterpret_cast<GeoVector2<float>&>(normal);
  EXPECT_FLOAT_EQ(NovelRT_GeoVector2F_getMagnitude(normal), sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2)));
}

TEST(InteropGeoVector2Test, getLengthReturnsCorrectLength) {
  NovelRTGeoVector2F cVector = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F normal = NovelRT_GeoVector2F_getNormalised(cVector);
  GeoVector2<float>& vec = reinterpret_cast<GeoVector2<float>&>(normal);
  EXPECT_FLOAT_EQ(NovelRT_GeoVector2F_getLength(normal), sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2)));
}

TEST(InteropGeoVector2Test, rotateToAngleAroundPointRotatesCorrectAmount) {
  NovelRTGeoVector2F vec{0.0f, 1.0f};
  NovelRTGeoVector2F zero = NovelRT_GeoVector2F_zero();
  const char* err = nullptr;
  NovelRTResult nrtResult = NovelRT_GeoVector2F_rotateToAngleAroundPoint(&vec, 90.0f, zero, &err);
  NovelRTGeoVector2F other{-1.0f, 0.0f};
  NovelRTGeoVector2F epsilon = NovelRT_GeoVector2F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector2F_epsilonEquals(vec, other, epsilon));
}
