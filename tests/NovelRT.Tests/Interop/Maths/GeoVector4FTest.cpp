// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include <NovelRT.Interop/Maths/NovelRTGeoVector4F.h>
#include <cmath>

using namespace NovelRT;
using namespace NovelRT::Maths;

NovelRTGeoVector4F vec4One = NovelRT_GeoVector4F_uniform(0.0);
NovelRTGeoVector4F vec4Two = NovelRT_GeoVector4F_uniform(0.0f);
NovelRTGeoVector4F vec4Three = NovelRT_GeoVector4F_uniform(1.0f);

TEST(InteropGeoVector4Test, createFromGeoVector2ReturnsGeoVector4WithCorrectAndVerbatimValues) {
  NovelRTGeoVector4F vec = NovelRT_GeoVector4F_createFromGeoVector2F(NovelRT_GeoVector2F_uniform(1.0f));
  EXPECT_TRUE(NovelRT_GeoVector4F_equal(NovelRTGeoVector4F{1.0f, 1.0f, 0.0f, 0.0f}, vec));
}

TEST(InteropGeoVector4Test, equalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(NovelRT_GeoVector4F_equal(vec4One, vec4Two));
}

TEST(InteropGeoVector4Test, inequalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(NovelRT_GeoVector4F_notEqual(vec4One, vec4Three));
}

TEST(InteropGeoVector4Test, lessThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(NovelRT_GeoVector4F_lessThan(vec4One, vec4Three));
}

TEST(InteropGeoVector4Test, lessOrEqualToThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(NovelRT_GeoVector4F_lessThanOrEqualTo(vec4One, vec4Three));
  EXPECT_TRUE(NovelRT_GeoVector4F_lessThanOrEqualTo(vec4Three, vec4Three));
}

TEST(InteropGeoVector4Test, greaterThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(NovelRT_GeoVector4F_greaterThan(vec4Three, vec4One));
}

TEST(InteropGeoVector4Test, greaterThanOrEqualToOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(NovelRT_GeoVector4F_greaterThanOrEqualTo(vec4Three, vec4One));
  EXPECT_TRUE(NovelRT_GeoVector4F_greaterThanOrEqualTo(vec4Three, vec4Three));
}

TEST(InteropGeoVector4Test, staticUniformCallReturnsGeoVector4WithUniformValues) {
  EXPECT_TRUE(NovelRT_GeoVector4F_equal(NovelRT_GeoVector4F_uniform(1.0f), vec4Three));
}

TEST(InteropGeoVector4Test, staticZeroCallReturnsGeoVector4Zero) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_uniform(0.0f);
  EXPECT_TRUE(NovelRT_GeoVector4F_equal(NovelRT_GeoVector4F_zero(), test));
}

TEST(InteropGeoVector4Test, staticOneCallReturnsGeoVector4One) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_uniform(1.0f);
  EXPECT_TRUE(NovelRT_GeoVector4F_equal(NovelRT_GeoVector4F_one(), test));
}

TEST(InteropGeoVector4Test, addOperatorAddsCorrectlyForGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_addVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);  
  EXPECT_TRUE(NovelRT_GeoVector4F_equal(NovelRT_GeoVector4F_uniform(2.0f), result));
}

TEST(InteropGeoVector4Test, addOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_addVector(test, test, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector4Test, addOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_addVector(test, test, nullptr, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector4Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector4F) {
  NovelRTGeoVector4F test { NAN, NAN };
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_addVector(test, NovelRT_GeoVector4F_zero(), &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector4Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector4F) {
  NovelRTGeoVector4F test { NAN, NAN };
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_addVector(NovelRT_GeoVector4F_zero(), test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector4Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector4F) {
  NovelRTGeoVector4F test { NAN, NAN };
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_addVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector4Test, subtractOperatorSubtractsCorrectlyForGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_subtractVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);  
  EXPECT_TRUE(NovelRT_GeoVector4F_equal(NovelRT_GeoVector4F_zero(), result));
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_subtractVector(test, test, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_subtractVector(test, test, nullptr, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector4F) {
  NovelRTGeoVector4F test { NAN, NAN };
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_subtractVector(test, NovelRT_GeoVector4F_zero(), &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector4F) {
  NovelRTGeoVector4F test { NAN, NAN };
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_subtractVector(NovelRT_GeoVector4F_zero(), test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector4F) {
  NovelRTGeoVector4F test { NAN, NAN };
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_subtractVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector4Test, multiplyOperatorMultipliesCorrectlyForGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_uniform(2.0f);
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_multiplyVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);  
  EXPECT_TRUE(NovelRT_GeoVector4F_equal(NovelRT_GeoVector4F_uniform(4.0f), result));
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_multiplyVector(test, test, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_multiplyVector(test, test, nullptr, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector4F) {
  NovelRTGeoVector4F test { NAN, NAN };
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_multiplyVector(test, NovelRT_GeoVector4F_zero(), &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector4F) {
  NovelRTGeoVector4F test { NAN, NAN };
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_multiplyVector(NovelRT_GeoVector4F_zero(), test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector4F) {
  NovelRTGeoVector4F test { NAN, NAN };
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_subtractVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector4Test, divideOperatorDividesCorrectlyForGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_uniform(4.0f);
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err = nullptr;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_divideVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);  
  EXPECT_TRUE(NovelRT_GeoVector4F_equal(NovelRT_GeoVector4F_one(), result));
}

TEST(InteropGeoVector4Test, divideOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_divideVector(test, test, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector4Test, divideOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_divideVector(test, test, nullptr, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector4Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector4F) {
  NovelRTGeoVector4F test { NAN, NAN };
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_divideVector(test, NovelRT_GeoVector4F_zero(), &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector4Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector4F) {
  NovelRTGeoVector4F test { NAN, NAN };
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_divideVector(NovelRT_GeoVector4F_zero(), test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector4Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector4F) {
  NovelRTGeoVector4F test { NAN, NAN };
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_divideVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector4Test, divideOperatorReturnsDivideByZeroMessageOnFailureStatusWhenGeoVector4FZeroIsProvidedForGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_divideVector(test, NovelRT_GeoVector4F_zero(), &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsDivideByZero(), err);  
}

TEST(InteropGeoVector4Test, addOperatorAddsCorrectlyForFloat) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_addFloat(test, 1.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector4F_equal(NovelRT_GeoVector4F_uniform(2.0f), result));
}

TEST(InteropGeoVector4Test, addOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_addFloat(test, 1.0f, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector4Test, addOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_addFloat(test, 1.0f, nullptr, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector4Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NovelRTGeoVector4F test { NAN, NAN };
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_addFloat(test, 0.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector4Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_zero();
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_addFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector4Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NovelRTGeoVector4F test { NAN, NAN };
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_addFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector4Test, subtractOperatorSubtractsCorrectlyForFloat) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_subtractFloat(test, 1.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector4F_equal(NovelRT_GeoVector4F_zero(), result));
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_subtractFloat(test, 1.0f, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_subtractFloat(test, 1.0f, nullptr, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NovelRTGeoVector4F test { NAN, NAN };
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_subtractFloat(test, 0.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_zero();
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_subtractFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NovelRTGeoVector4F test { NAN, NAN };
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_subtractFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector4Test, multiplyOperatorMultipliesCorrectlyForFloat) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_uniform(2.0f);
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_multiplyFloat(test, 2.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector4F_equal(NovelRT_GeoVector4F_uniform(4.0f), result));
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_multiplyFloat(test, 1.0f, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_multiplyFloat(test, 1.0f, nullptr, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NovelRTGeoVector4F test { NAN, NAN };
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_multiplyFloat(test, 0.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_zero();
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_multiplyFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NovelRTGeoVector4F test { NAN, NAN };
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_multiplyFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector4Test, divideOperatorDividesCorrectlyForFloat) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_uniform(4.0f);
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_divideFloat(test, 2.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector4F_equal(NovelRT_GeoVector4F_uniform(2.0f), result));
}

TEST(InteropGeoVector4Test, divideOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_divideFloat(test, 1.0f, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector4Test, divideOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_divideFloat(test, 1.0f, nullptr, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector4Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NovelRTGeoVector4F test { NAN, NAN };
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_divideFloat(test, 0.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector4Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_zero();
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_divideFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector4Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NovelRTGeoVector4F test { NAN, NAN };
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_divideFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector4Test, divideOperatorReturnsDivideByZeroMessageOnFailureStatusWhenFloatZeroIsProvidedForFloat) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();
  NovelRTGeoVector4F result = NovelRT_GeoVector4F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector4F_divideFloat(test, 0.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsDivideByZero(), err);  
}

TEST(InteropGeoVector4Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_addAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector4F_equal(NovelRT_GeoVector4F_uniform(2.0f), test));
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_addAssignVector(nullptr, test, &err);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_addAssignVector(nullptr, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector4F) {
  NovelRTGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_addAssignVector(&test, NovelRT_GeoVector4F_one(), &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_addAssignVector(&test, NovelRT_GeoVector4F_uniform(NAN), &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector4F) {
  NovelRTGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_addAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector4Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_subtractAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector4F_equal(NovelRT_GeoVector4F_zero(), test));
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_subtractAssignVector(nullptr, test, &err);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_subtractAssignVector(nullptr, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector4F) {
  NovelRTGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_subtractAssignVector(&test, NovelRT_GeoVector4F_one(), &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_subtractAssignVector(&test, NovelRT_GeoVector4F_uniform(NAN), &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector4F) {
  NovelRTGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_subtractAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_uniform(2.0f);

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_multiplyAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector4F_equal(NovelRT_GeoVector4F_uniform(4.0f), test));
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_multiplyAssignVector(nullptr, test, &err);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_multiplyAssignVector(nullptr, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector4F) {
  NovelRTGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_multiplyAssignVector(&test, NovelRT_GeoVector4F_one(), &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_multiplyAssignVector(&test, NovelRT_GeoVector4F_uniform(NAN), &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector4F) {
  NovelRTGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_multiplyAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector4Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_uniform(2.0f);

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_divideAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector4F_equal(NovelRT_GeoVector4F_one(), test));
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_divideAssignVector(nullptr, test, &err);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_divideAssignVector(nullptr, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector4F) {
  NovelRTGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_divideAssignVector(&test, NovelRT_GeoVector4F_one(), &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_divideAssignVector(&test, NovelRT_GeoVector4F_uniform(NAN), &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector4F) {
  NovelRTGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_divideAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsDivideByZeroMessageOnFailureStatusWhenGeoVector4FZeroIsProvidedForGeoVector4F) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_divideAssignVector(&test, NovelRT_GeoVector4F_zero(), &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsDivideByZero(), err);
}

TEST(InteropGeoVector4Test, addAssignOperatorAddsAndAssignsCorrectlyForFloat) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_addAssignFloat(&test, 1.0f, &err);
  
  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector4F_equal(NovelRT_GeoVector4F_uniform(2.0f), test));
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_addAssignFloat(nullptr, 1.0f, &err);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_addAssignFloat(nullptr, 1.0f, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NovelRTGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_addAssignFloat(&test, 1.0f, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_addAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NovelRTGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_addAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector4Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForFloat) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_subtractAssignFloat(&test, 1.0f, &err);
  
  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector4F_equal(NovelRT_GeoVector4F_uniform(0.0f), test));
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_subtractAssignFloat(nullptr, 1.0f, &err);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_subtractAssignFloat(nullptr, 1.0f, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NovelRTGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_subtractAssignFloat(&test, 1.0f, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_subtractAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NovelRTGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_subtractAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForFloat) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_uniform(2.0f);

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_multiplyAssignFloat(&test, 1.0f, &err);
  
  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector4F_equal(NovelRT_GeoVector4F_uniform(2.0f), test));
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_multiplyAssignFloat(nullptr, 1.0f, &err);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_multiplyAssignFloat(nullptr, 1.0f, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NovelRTGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_multiplyAssignFloat(&test, 1.0f, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_multiplyAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NovelRTGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_multiplyAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector4Test, divideAssignOperatorDividesAndAssignsCorrectlyForFloat) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_uniform(2.0f);

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_divideAssignFloat(&test, 2.0f, &err);
  
  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector4F_equal(NovelRT_GeoVector4F_uniform(1.0f), test));
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_divideAssignFloat(nullptr, 1.0f, &err);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_divideAssignFloat(nullptr, 1.0f, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NovelRTGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_divideAssignFloat(&test, 1.0f, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_divideAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NovelRTGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_divideAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsDivideByZeroMessageOnFailureStatusWhenFloatZeroIsProvidedForFloat) {
  NovelRTGeoVector4F test = NovelRT_GeoVector4F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_divideAssignFloat(&test, 0.0f, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsDivideByZero(), err);
}

TEST(InteropGeoVector4Test, getNormalisedReturnsNormalisedGeoVector) {
  NovelRTGeoVector4F cVector = NovelRT_GeoVector4F_one();
  NovelRTGeoVector4F normal = NovelRT_GeoVector4F_getNormalised(cVector);
  GeoVector4<float>& vec = reinterpret_cast<GeoVector4<float>&>(normal);
  float normalisedTotal = sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2) + powf(vec.getZ(), 2) + powf(vec.getW(), 2));
  EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(InteropGeoVector4Test, getMagnitudeReturnsCorrectLength) {
  NovelRTGeoVector4F cVector = NovelRT_GeoVector4F_one();
  NovelRTGeoVector4F normal = NovelRT_GeoVector4F_getNormalised(cVector);
  GeoVector4<float>& vec = reinterpret_cast<GeoVector4<float>&>(normal);
  EXPECT_FLOAT_EQ(NovelRT_GeoVector4F_getMagnitude(normal), sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2) + powf(vec.getZ(), 2) + powf(vec.getW(), 2)));
}

TEST(InteropGeoVector4Test, getLengthReturnsCorrectLength) {
  NovelRTGeoVector4F cVector = NovelRT_GeoVector4F_one();
  NovelRTGeoVector4F normal = NovelRT_GeoVector4F_getNormalised(cVector);
  GeoVector4<float>& vec = reinterpret_cast<GeoVector4<float>&>(normal);
  EXPECT_FLOAT_EQ(NovelRT_GeoVector4F_getLength(normal), sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2) + powf(vec.getZ(), 2) + powf(vec.getW(), 2)));
}

TEST(InteropGeoVector4Test, rotateToAngleAroundPointRotatesCorrectAmount) {
  NovelRTGeoVector4F vec{0.0f, 1.0f};
  NovelRTGeoVector3F zero = NovelRT_GeoVector3F_zero();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_rotateToAngleAroundPoint(&vec, 90.0f, zero, &err);
  NovelRTGeoVector4F other{-1.0f, 0.0f};
  NovelRTGeoVector4F epsilon = NovelRT_GeoVector4F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector4F_epsilonEquals(vec, other, epsilon));
}

TEST(InteropGeoVector4Test, rotateToAngleAroundPointReturnsFailureStatucWhenUnableToOperate) {
  NovelRTGeoVector3F zero = NovelRT_GeoVector3F_zero();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_rotateToAngleAroundPoint(nullptr, 90.0f, zero, &err);
  NovelRTGeoVector4F other{-1.0f, 0.0f};
  NovelRTGeoVector4F epsilon = NovelRT_GeoVector4F_uniform(1e-7f);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector4Test, rotateToAngleAroundPointWhenGivenNullptrReturnsNullPtrMessageOnFailureStatus) {
  NovelRTGeoVector3F zero = NovelRT_GeoVector3F_zero();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_rotateToAngleAroundPoint(nullptr, 90.0f, zero, &err);
  NovelRTGeoVector4F other{-1.0f, 0.0f};
  NovelRTGeoVector4F epsilon = NovelRT_GeoVector4F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector4Test, rotateToAngleAroundPointWhenGivenNaNValueInLhsReturnsNaNMessageOnFailureStatus) {
  NovelRTGeoVector4F vec{ NAN, NAN, NAN, NAN };
  NovelRTGeoVector3F zero = NovelRT_GeoVector3F_zero();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_rotateToAngleAroundPoint(&vec, 90.0f, zero, &err);
  NovelRTGeoVector4F other{-1.0f, 0.0f};
  NovelRTGeoVector4F epsilon = NovelRT_GeoVector4F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector4Test, rotateToAngleAroundPointWhenGivenNaNValueInRhsReturnsNaNMessageOnFailureStatus) {
  NovelRTGeoVector4F vec{ 0.0f, 1.0f };
  NovelRTGeoVector3F zero { NAN, NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_rotateToAngleAroundPoint(&vec, 90.0f, zero, &err);
  NovelRTGeoVector4F other{-1.0f, 0.0f};
  NovelRTGeoVector4F epsilon = NovelRT_GeoVector4F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector4Test, rotateToAngleAroundPointWhenGivenNaNValueForBothReturnsNaNMessageOnFailureStatus) {
  NovelRTGeoVector4F vec{ NAN, NAN, NAN, NAN };
  NovelRTGeoVector3F zero{ NAN, NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector4F_rotateToAngleAroundPoint(&vec, 90.0f, zero, &err);
  NovelRTGeoVector4F other{-1.0f, 0.0f};
  NovelRTGeoVector4F epsilon = NovelRT_GeoVector4F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector4Test, isNaNReturnsTrueNaNVector) {
  NovelRTGeoVector4F nanVec {NAN, NAN};
  EXPECT_TRUE(NovelRT_GeoVector4F_isNaN(nanVec));
}

