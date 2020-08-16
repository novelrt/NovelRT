// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include <NovelRT.Interop/Maths/NovelRTGeoVector3F.h>
#include <cmath>

using namespace NovelRT;
using namespace NovelRT::Maths;

NovelRTGeoVector3F vec3One = NovelRT_GeoVector3F_uniform(0.0);
NovelRTGeoVector3F vec3Two = NovelRT_GeoVector3F_uniform(0.0f);
NovelRTGeoVector3F vec3Three = NovelRT_GeoVector3F_uniform(1.0f);

TEST(InteropGeoVector3Test, createFromGeoVector2ReturnsGeoVector3WithCorrectAndVerbatimValues) {
  NovelRTGeoVector3F vec = NovelRT_GeoVector3F_createFromGeoVector2F(NovelRT_GeoVector2F_uniform(1.0f));
  EXPECT_TRUE(NovelRT_GeoVector3F_equal(NovelRTGeoVector3F{1.0f, 1.0f, 0.0f}, vec));
}

TEST(InteropGeoVector3Test, equalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(NovelRT_GeoVector3F_equal(vec3One, vec3Two));
}

TEST(InteropGeoVector3Test, inequalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(NovelRT_GeoVector3F_notEqual(vec3One, vec3Three));
}

TEST(InteropGeoVector3Test, lessThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(NovelRT_GeoVector3F_lessThan(vec3One, vec3Three));
}

TEST(InteropGeoVector3Test, lessOrEqualToThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(NovelRT_GeoVector3F_lessThanOrEqualTo(vec3One, vec3Three));
  EXPECT_TRUE(NovelRT_GeoVector3F_lessThanOrEqualTo(vec3Three, vec3Three));
}

TEST(InteropGeoVector3Test, greaterThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(NovelRT_GeoVector3F_greaterThan(vec3Three, vec3One));
}

TEST(InteropGeoVector3Test, greaterThanOrEqualToOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(NovelRT_GeoVector3F_greaterThanOrEqualTo(vec3Three, vec3One));
  EXPECT_TRUE(NovelRT_GeoVector3F_greaterThanOrEqualTo(vec3Three, vec3Three));
}

TEST(InteropGeoVector3Test, staticUniformCallReturnsGeoVector2WithUniformValues) {
  EXPECT_TRUE(NovelRT_GeoVector3F_equal(NovelRT_GeoVector3F_uniform(1.0f), vec3Three));
}

TEST(InteropGeoVector3Test, staticZeroCallReturnsGeoVector2Zero) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_uniform(0.0f);
  EXPECT_TRUE(NovelRT_GeoVector3F_equal(NovelRT_GeoVector3F_zero(), test));
}

TEST(InteropGeoVector3Test, staticOneCallReturnsGeoVector2One) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_uniform(1.0f);
  EXPECT_TRUE(NovelRT_GeoVector3F_equal(NovelRT_GeoVector3F_one(), test));
}

TEST(InteropGeoVector3Test, addOperatorAddsCorrectlyForGeoVector3F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_addVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);  
  EXPECT_TRUE(NovelRT_GeoVector3F_equal(NovelRT_GeoVector3F_uniform(2.0f), result));
}

TEST(InteropGeoVector3Test, addOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector3F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_addVector(test, test, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector3Test, addOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForGeoVector3F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_addVector(test, test, nullptr, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector3Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector3F) {
  NovelRTGeoVector3F test { NAN, NAN };
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_addVector(test, NovelRT_GeoVector3F_zero(), &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector3F) {
  NovelRTGeoVector3F test { NAN, NAN };
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_addVector(NovelRT_GeoVector3F_zero(), test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector3F) {
  NovelRTGeoVector3F test { NAN, NAN };
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_addVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, subtractOperatorSubtractsCorrectlyForGeoVector3F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_subtractVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);  
  EXPECT_TRUE(NovelRT_GeoVector3F_equal(NovelRT_GeoVector3F_zero(), result));
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector3F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_subtractVector(test, test, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForGeoVector3F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_subtractVector(test, test, nullptr, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector3F) {
  NovelRTGeoVector3F test { NAN, NAN };
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_subtractVector(test, NovelRT_GeoVector3F_zero(), &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector3F) {
  NovelRTGeoVector3F test { NAN, NAN };
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_subtractVector(NovelRT_GeoVector3F_zero(), test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector3F) {
  NovelRTGeoVector3F test { NAN, NAN };
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_subtractVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, multiplyOperatorMultipliesCorrectlyForGeoVector3F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_uniform(2.0f);
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_multiplyVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);  
  EXPECT_TRUE(NovelRT_GeoVector3F_equal(NovelRT_GeoVector3F_uniform(4.0f), result));
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector3F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_multiplyVector(test, test, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForGeoVector3F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_multiplyVector(test, test, nullptr, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector3F) {
  NovelRTGeoVector3F test { NAN, NAN };
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_multiplyVector(test, NovelRT_GeoVector3F_zero(), &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector3F) {
  NovelRTGeoVector3F test { NAN, NAN };
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_multiplyVector(NovelRT_GeoVector3F_zero(), test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector3F) {
  NovelRTGeoVector3F test { NAN, NAN };
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_subtractVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, divideOperatorDividesCorrectlyForGeoVector3F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_uniform(4.0f);
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err = nullptr;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_divideVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);  
  EXPECT_TRUE(NovelRT_GeoVector3F_equal(NovelRT_GeoVector3F_one(), result));
}

TEST(InteropGeoVector3Test, divideOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector3F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_divideVector(test, test, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector3Test, divideOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForGeoVector3F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_divideVector(test, test, nullptr, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector3Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector3F) {
  NovelRTGeoVector3F test { NAN, NAN };
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_divideVector(test, NovelRT_GeoVector3F_zero(), &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector3F) {
  NovelRTGeoVector3F test { NAN, NAN };
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_divideVector(NovelRT_GeoVector3F_zero(), test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector3F) {
  NovelRTGeoVector3F test { NAN, NAN };
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_divideVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, divideOperatorReturnsDivideByZeroMessageOnFailureStatusWhenGeoVector2FZeroIsProvidedForGeoVector3F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_divideVector(test, NovelRT_GeoVector3F_zero(), &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsDivideByZero(), err);  
}

TEST(InteropGeoVector3Test, addOperatorAddsCorrectlyForFloat) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_addFloat(test, 1.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector3F_equal(NovelRT_GeoVector3F_uniform(2.0f), result));
}

TEST(InteropGeoVector3Test, addOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_addFloat(test, 1.0f, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector3Test, addOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_addFloat(test, 1.0f, nullptr, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector3Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NovelRTGeoVector3F test { NAN, NAN };
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_addFloat(test, 0.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_zero();
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_addFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NovelRTGeoVector3F test { NAN, NAN };
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_addFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, subtractOperatorSubtractsCorrectlyForFloat) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_subtractFloat(test, 1.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector3F_equal(NovelRT_GeoVector3F_zero(), result));
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_subtractFloat(test, 1.0f, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_subtractFloat(test, 1.0f, nullptr, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NovelRTGeoVector3F test { NAN, NAN };
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_subtractFloat(test, 0.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_zero();
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_subtractFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NovelRTGeoVector3F test { NAN, NAN };
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_subtractFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, multiplyOperatorMultipliesCorrectlyForFloat) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_uniform(2.0f);
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_multiplyFloat(test, 2.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector3F_equal(NovelRT_GeoVector3F_uniform(4.0f), result));
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_multiplyFloat(test, 1.0f, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_multiplyFloat(test, 1.0f, nullptr, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NovelRTGeoVector3F test { NAN, NAN };
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_multiplyFloat(test, 0.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_zero();
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_multiplyFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NovelRTGeoVector3F test { NAN, NAN };
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_multiplyFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, divideOperatorDividesCorrectlyForFloat) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_uniform(4.0f);
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_divideFloat(test, 2.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector3F_equal(NovelRT_GeoVector3F_uniform(2.0f), result));
}

TEST(InteropGeoVector3Test, divideOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_divideFloat(test, 1.0f, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector3Test, divideOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_divideFloat(test, 1.0f, nullptr, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector3Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NovelRTGeoVector3F test { NAN, NAN };
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_divideFloat(test, 0.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_zero();
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_divideFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NovelRTGeoVector3F test { NAN, NAN };
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_divideFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, divideOperatorReturnsDivideByZeroMessageOnFailureStatusWhenFloatZeroIsProvidedForFloat) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();
  NovelRTGeoVector3F result = NovelRT_GeoVector3F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector3F_divideFloat(test, 0.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsDivideByZero(), err);  
}

TEST(InteropGeoVector3Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector3F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_addAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector3F_equal(NovelRT_GeoVector3F_uniform(2.0f), test));
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector3F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_addAssignVector(nullptr, test, &err);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullGeoVector2F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_addAssignVector(nullptr, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector3F) {
  NovelRTGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_addAssignVector(&test, NovelRT_GeoVector3F_one(), &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector3F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_addAssignVector(&test, NovelRT_GeoVector3F_uniform(NAN), &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector3F) {
  NovelRTGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_addAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector3F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_subtractAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector3F_equal(NovelRT_GeoVector3F_zero(), test));
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector3F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_subtractAssignVector(nullptr, test, &err);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullGeoVector2F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_subtractAssignVector(nullptr, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector3F) {
  NovelRTGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_subtractAssignVector(&test, NovelRT_GeoVector3F_one(), &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector3F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_subtractAssignVector(&test, NovelRT_GeoVector3F_uniform(NAN), &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector3F) {
  NovelRTGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_subtractAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector3F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_uniform(2.0f);

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_multiplyAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector3F_equal(NovelRT_GeoVector3F_uniform(4.0f), test));
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector3F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_multiplyAssignVector(nullptr, test, &err);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullGeoVector2F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_multiplyAssignVector(nullptr, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector3F) {
  NovelRTGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_multiplyAssignVector(&test, NovelRT_GeoVector3F_one(), &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector3F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_multiplyAssignVector(&test, NovelRT_GeoVector3F_uniform(NAN), &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector3F) {
  NovelRTGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_multiplyAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector3F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_uniform(2.0f);

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_divideAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector3F_equal(NovelRT_GeoVector3F_one(), test));
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector3F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_divideAssignVector(nullptr, test, &err);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullGeoVector2F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_divideAssignVector(nullptr, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector3F) {
  NovelRTGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_divideAssignVector(&test, NovelRT_GeoVector3F_one(), &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector3F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_divideAssignVector(&test, NovelRT_GeoVector3F_uniform(NAN), &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector3F) {
  NovelRTGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_divideAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsDivideByZeroMessageOnFailureStatusWhenGeoVector2FZeroIsProvidedForGeoVector3F) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_divideAssignVector(&test, NovelRT_GeoVector3F_zero(), &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsDivideByZero(), err);
}

TEST(InteropGeoVector3Test, addAssignOperatorAddsAndAssignsCorrectlyForFloat) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_addAssignFloat(&test, 1.0f, &err);
  
  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector3F_equal(NovelRT_GeoVector3F_uniform(2.0f), test));
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_addAssignFloat(nullptr, 1.0f, &err);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_addAssignFloat(nullptr, 1.0f, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NovelRTGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_addAssignFloat(&test, 1.0f, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_addAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NovelRTGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_addAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForFloat) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_subtractAssignFloat(&test, 1.0f, &err);
  
  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector3F_equal(NovelRT_GeoVector3F_uniform(0.0f), test));
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_subtractAssignFloat(nullptr, 1.0f, &err);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_subtractAssignFloat(nullptr, 1.0f, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NovelRTGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_subtractAssignFloat(&test, 1.0f, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_subtractAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NovelRTGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_subtractAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForFloat) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_uniform(2.0f);

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_multiplyAssignFloat(&test, 1.0f, &err);
  
  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector3F_equal(NovelRT_GeoVector3F_uniform(2.0f), test));
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_multiplyAssignFloat(nullptr, 1.0f, &err);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_multiplyAssignFloat(nullptr, 1.0f, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NovelRTGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_multiplyAssignFloat(&test, 1.0f, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_multiplyAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NovelRTGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_multiplyAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, divideAssignOperatorDividesAndAssignsCorrectlyForFloat) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_uniform(2.0f);

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_divideAssignFloat(&test, 2.0f, &err);
  
  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector3F_equal(NovelRT_GeoVector3F_uniform(1.0f), test));
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_divideAssignFloat(nullptr, 1.0f, &err);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_divideAssignFloat(nullptr, 1.0f, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NovelRTGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_divideAssignFloat(&test, 1.0f, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_divideAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NovelRTGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_divideAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsDivideByZeroMessageOnFailureStatusWhenFloatZeroIsProvidedForFloat) {
  NovelRTGeoVector3F test = NovelRT_GeoVector3F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_divideAssignFloat(&test, 0.0f, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsDivideByZero(), err);
}

TEST(InteropGeoVector3Test, getNormalisedReturnsNormalisedGeoVector) {
  NovelRTGeoVector3F cVector = NovelRT_GeoVector3F_one();
  NovelRTGeoVector3F normal = NovelRT_GeoVector3F_getNormalised(cVector);
  GeoVector3<float>& vec = reinterpret_cast<GeoVector3<float>&>(normal);
  float normalisedTotal = sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2) + powf(vec.getZ(), 2));
  EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(InteropGeoVector3Test, getMagnitudeReturnsCorrectLength) {
  NovelRTGeoVector3F cVector = NovelRT_GeoVector3F_one();
  NovelRTGeoVector3F normal = NovelRT_GeoVector3F_getNormalised(cVector);
  GeoVector3<float>& vec = reinterpret_cast<GeoVector3<float>&>(normal);
  EXPECT_FLOAT_EQ(NovelRT_GeoVector3F_getMagnitude(normal), sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2) + powf(vec.getZ(), 2)));
}

TEST(InteropGeoVector3Test, getLengthReturnsCorrectLength) {
  NovelRTGeoVector3F cVector = NovelRT_GeoVector3F_one();
  NovelRTGeoVector3F normal = NovelRT_GeoVector3F_getNormalised(cVector);
  GeoVector3<float>& vec = reinterpret_cast<GeoVector3<float>&>(normal);
  EXPECT_FLOAT_EQ(NovelRT_GeoVector3F_getLength(normal), sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2) + powf(vec.getZ(), 2)));
}

TEST(InteropGeoVector3Test, rotateToAngleAroundPointRotatesCorrectAmount) {
  NovelRTGeoVector3F vec{0.0f, 1.0f};
  NovelRTGeoVector3F zero = NovelRT_GeoVector3F_zero();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_rotateToAngleAroundPoint(&vec, 90.0f, zero, &err);
  NovelRTGeoVector3F other{-1.0f, 0.0f};
  NovelRTGeoVector3F epsilon = NovelRT_GeoVector3F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector3F_epsilonEquals(vec, other, epsilon));
}

TEST(InteropGeoVector3Test, rotateToAngleAroundPointReturnsFailureStatucWhenUnableToOperate) {
  NovelRTGeoVector3F zero = NovelRT_GeoVector3F_zero();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_rotateToAngleAroundPoint(nullptr, 90.0f, zero, &err);
  NovelRTGeoVector3F other{-1.0f, 0.0f};
  NovelRTGeoVector3F epsilon = NovelRT_GeoVector3F_uniform(1e-7f);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector3Test, rotateToAngleAroundPointWhenGivenNullptrReturnsNullPtrMessageOnFailureStatus) {
  NovelRTGeoVector3F zero = NovelRT_GeoVector3F_zero();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_rotateToAngleAroundPoint(nullptr, 90.0f, zero, &err);
  NovelRTGeoVector3F other{-1.0f, 0.0f};
  NovelRTGeoVector3F epsilon = NovelRT_GeoVector3F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector3Test, rotateToAngleAroundPointWhenGivenNaNValueInLhsReturnsNaNMessageOnFailureStatus) {
  NovelRTGeoVector3F vec{ NAN, NAN };
  NovelRTGeoVector3F zero = NovelRT_GeoVector3F_zero();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_rotateToAngleAroundPoint(&vec, 90.0f, zero, &err);
  NovelRTGeoVector3F other{-1.0f, 0.0f};
  NovelRTGeoVector3F epsilon = NovelRT_GeoVector3F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, rotateToAngleAroundPointWhenGivenNaNValueInRhsReturnsNaNMessageOnFailureStatus) {
  NovelRTGeoVector3F vec{ 0.0f, 1.0f };
  NovelRTGeoVector3F zero { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_rotateToAngleAroundPoint(&vec, 90.0f, zero, &err);
  NovelRTGeoVector3F other{-1.0f, 0.0f};
  NovelRTGeoVector3F epsilon = NovelRT_GeoVector3F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, rotateToAngleAroundPointWhenGivenNaNValueForBothReturnsNaNMessageOnFailureStatus) {
  NovelRTGeoVector3F vec{ NAN, NAN };
  NovelRTGeoVector3F zero{ NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector3F_rotateToAngleAroundPoint(&vec, 90.0f, zero, &err);
  NovelRTGeoVector3F other{-1.0f, 0.0f};
  NovelRTGeoVector3F epsilon = NovelRT_GeoVector3F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, isNaNReturnsTrueNaNVector) {
  NovelRTGeoVector3F nanVec {NAN, NAN};
  EXPECT_TRUE(NovelRT_GeoVector3F_isNaN(nanVec));
}