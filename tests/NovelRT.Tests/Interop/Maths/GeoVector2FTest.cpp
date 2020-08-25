// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include <NovelRT.Interop/Maths/NovelRTGeoVector2F.h>
#include <cmath>

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

TEST(InteropGeoVector2Test, addOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_addVector(test, test, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector2Test, addOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_addVector(test, test, nullptr, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector2Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector2F) {
  NovelRTGeoVector2F test { NAN, NAN };
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_addVector(test, NovelRT_GeoVector2F_zero(), &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector2Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector2F) {
  NovelRTGeoVector2F test { NAN, NAN };
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_addVector(NovelRT_GeoVector2F_zero(), test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector2Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector2F) {
  NovelRTGeoVector2F test { NAN, NAN };
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_addVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector2Test, subtractOperatorSubtractsCorrectlyForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_subtractVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);  
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_zero(), result));
}

TEST(InteropGeoVector2Test, subtractOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_subtractVector(test, test, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector2Test, subtractOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_subtractVector(test, test, nullptr, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector2Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector2F) {
  NovelRTGeoVector2F test { NAN, NAN };
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_subtractVector(test, NovelRT_GeoVector2F_zero(), &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector2Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector2F) {
  NovelRTGeoVector2F test { NAN, NAN };
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_subtractVector(NovelRT_GeoVector2F_zero(), test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector2Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector2F) {
  NovelRTGeoVector2F test { NAN, NAN };
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_subtractVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector2Test, multiplyOperatorMultipliesCorrectlyForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_uniform(2.0f);
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_multiplyVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);  
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(4.0f), result));
}

TEST(InteropGeoVector2Test, multiplyOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_multiplyVector(test, test, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector2Test, multiplyOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_multiplyVector(test, test, nullptr, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector2Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector2F) {
  NovelRTGeoVector2F test { NAN, NAN };
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_multiplyVector(test, NovelRT_GeoVector2F_zero(), &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector2Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector2F) {
  NovelRTGeoVector2F test { NAN, NAN };
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_multiplyVector(NovelRT_GeoVector2F_zero(), test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector2Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector2F) {
  NovelRTGeoVector2F test { NAN, NAN };
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_subtractVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector2Test, divideOperatorDividesCorrectlyForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_uniform(4.0f);
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err = nullptr;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_divideVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);  
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_one(), result));
}

TEST(InteropGeoVector2Test, divideOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_divideVector(test, test, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector2Test, divideOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_divideVector(test, test, nullptr, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector2Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector2F) {
  NovelRTGeoVector2F test { NAN, NAN };
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_divideVector(test, NovelRT_GeoVector2F_zero(), &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector2Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector2F) {
  NovelRTGeoVector2F test { NAN, NAN };
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_divideVector(NovelRT_GeoVector2F_zero(), test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector2Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector2F) {
  NovelRTGeoVector2F test { NAN, NAN };
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_divideVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector2Test, divideOperatorReturnsDivideByZeroMessageOnFailureStatusWhenGeoVector2FZeroIsProvidedForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_divideVector(test, NovelRT_GeoVector2F_zero(), &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsDivideByZero(), err);  
}

TEST(InteropGeoVector2Test, addOperatorAddsCorrectlyForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_addFloat(test, 1.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(2.0f), result));
}

TEST(InteropGeoVector2Test, addOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_addFloat(test, 1.0f, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector2Test, addOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_addFloat(test, 1.0f, nullptr, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector2Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NovelRTGeoVector2F test { NAN, NAN };
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_addFloat(test, 0.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector2Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_zero();
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_addFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector2Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NovelRTGeoVector2F test { NAN, NAN };
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_addFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector2Test, subtractOperatorSubtractsCorrectlyForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_subtractFloat(test, 1.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_zero(), result));
}

TEST(InteropGeoVector2Test, subtractOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_subtractFloat(test, 1.0f, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector2Test, subtractOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_subtractFloat(test, 1.0f, nullptr, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector2Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NovelRTGeoVector2F test { NAN, NAN };
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_subtractFloat(test, 0.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector2Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_zero();
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_subtractFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector2Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NovelRTGeoVector2F test { NAN, NAN };
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_subtractFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector2Test, multiplyOperatorMultipliesCorrectlyForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_uniform(2.0f);
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_multiplyFloat(test, 2.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(4.0f), result));
}

TEST(InteropGeoVector2Test, multiplyOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_multiplyFloat(test, 1.0f, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector2Test, multiplyOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_multiplyFloat(test, 1.0f, nullptr, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector2Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NovelRTGeoVector2F test { NAN, NAN };
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_multiplyFloat(test, 0.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector2Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_zero();
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_multiplyFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector2Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NovelRTGeoVector2F test { NAN, NAN };
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_multiplyFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector2Test, divideOperatorDividesCorrectlyForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_uniform(4.0f);
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_divideFloat(test, 2.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(2.0f), result));
}

TEST(InteropGeoVector2Test, divideOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_divideFloat(test, 1.0f, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector2Test, divideOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_divideFloat(test, 1.0f, nullptr, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector2Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NovelRTGeoVector2F test { NAN, NAN };
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_divideFloat(test, 0.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector2Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_zero();
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_divideFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector2Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NovelRTGeoVector2F test { NAN, NAN };
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_divideFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector2Test, divideOperatorReturnsDivideByZeroMessageOnFailureStatusWhenFloatZeroIsProvidedForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_zero();
  
  const char* err;
  NovelRTBool nrtResult = NovelRT_GeoVector2F_divideFloat(test, 0.0f, &result, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsDivideByZero(), err);  
}

TEST(InteropGeoVector2Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_addAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(2.0f), test));
}

TEST(InteropGeoVector2Test, addAssignOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_addAssignVector(nullptr, test, &err);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector2Test, addAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_addAssignVector(nullptr, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector2Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector2F) {
  NovelRTGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_addAssignVector(&test, NovelRT_GeoVector2F_one(), &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector2Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_addAssignVector(&test, NovelRT_GeoVector2F_uniform(NAN), &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector2Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector2F) {
  NovelRTGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_addAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector2Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_subtractAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_zero(), test));
}

TEST(InteropGeoVector2Test, subtractAssignOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_subtractAssignVector(nullptr, test, &err);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector2Test, subtractAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_subtractAssignVector(nullptr, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector2Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector2F) {
  NovelRTGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_subtractAssignVector(&test, NovelRT_GeoVector2F_one(), &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector2Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_subtractAssignVector(&test, NovelRT_GeoVector2F_uniform(NAN), &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector2Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector2F) {
  NovelRTGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_subtractAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_uniform(2.0f);

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_multiplyAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(4.0f), test));
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_multiplyAssignVector(nullptr, test, &err);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_multiplyAssignVector(nullptr, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector2F) {
  NovelRTGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_multiplyAssignVector(&test, NovelRT_GeoVector2F_one(), &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_multiplyAssignVector(&test, NovelRT_GeoVector2F_uniform(NAN), &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector2F) {
  NovelRTGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_multiplyAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector2Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_uniform(2.0f);

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_divideAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_one(), test));
}

TEST(InteropGeoVector2Test, divideAssignOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_divideAssignVector(nullptr, test, &err);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector2Test, divideAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_divideAssignVector(nullptr, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector2Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector2F) {
  NovelRTGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_divideAssignVector(&test, NovelRT_GeoVector2F_one(), &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector2Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_divideAssignVector(&test, NovelRT_GeoVector2F_uniform(NAN), &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector2Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector2F) {
  NovelRTGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_divideAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector2Test, divideAssignOperatorReturnsDivideByZeroMessageOnFailureStatusWhenGeoVector2FZeroIsProvidedForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_divideAssignVector(&test, NovelRT_GeoVector2F_zero(), &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsDivideByZero(), err);
}

TEST(InteropGeoVector2Test, addAssignOperatorAddsAndAssignsCorrectlyForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_addAssignFloat(&test, 1.0f, &err);
  
  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(2.0f), test));
}

TEST(InteropGeoVector2Test, addAssignOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_addAssignFloat(nullptr, 1.0f, &err);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector2Test, addAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_addAssignFloat(nullptr, 1.0f, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector2Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NovelRTGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_addAssignFloat(&test, 1.0f, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector2Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_addAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector2Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NovelRTGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_addAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector2Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_subtractAssignFloat(&test, 1.0f, &err);
  
  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(0.0f), test));
}

TEST(InteropGeoVector2Test, subtractAssignOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_subtractAssignFloat(nullptr, 1.0f, &err);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector2Test, subtractAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_subtractAssignFloat(nullptr, 1.0f, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector2Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NovelRTGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_subtractAssignFloat(&test, 1.0f, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector2Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_subtractAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector2Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NovelRTGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_subtractAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_uniform(2.0f);

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_multiplyAssignFloat(&test, 1.0f, &err);
  
  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(2.0f), test));
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_multiplyAssignFloat(nullptr, 1.0f, &err);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_multiplyAssignFloat(nullptr, 1.0f, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NovelRTGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_multiplyAssignFloat(&test, 1.0f, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_multiplyAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NovelRTGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_multiplyAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector2Test, divideAssignOperatorDividesAndAssignsCorrectlyForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_uniform(2.0f);

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_divideAssignFloat(&test, 2.0f, &err);
  
  ASSERT_EQ(nrtResult, NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(1.0f), test));
}

TEST(InteropGeoVector2Test, divideAssignOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_divideAssignFloat(nullptr, 1.0f, &err);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector2Test, divideAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_divideAssignFloat(nullptr, 1.0f, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector2Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NovelRTGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_divideAssignFloat(&test, 1.0f, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector2Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_divideAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector2Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NovelRTGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_divideAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector2Test, divideAssignOperatorReturnsDivideByZeroMessageOnFailureStatusWhenFloatZeroIsProvidedForFloat) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_divideAssignFloat(&test, 0.0f, &err);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsDivideByZero(), err);
}

TEST(InteropGeoVector2Test, getNormalisedReturnsNormalisedGeoVector) {
  NovelRTGeoVector2F cVector = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F normal = NovelRT_GeoVector2F_getNormalised(cVector);
  GeoVector2F& vec = reinterpret_cast<GeoVector2F&>(normal);
  float normalisedTotal = sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2));
  EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(InteropGeoVector2Test, getMagnitudeReturnsCorrectLength) {
  NovelRTGeoVector2F cVector = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F normal = NovelRT_GeoVector2F_getNormalised(cVector);
  GeoVector2F& vec = reinterpret_cast<GeoVector2F&>(normal);
  EXPECT_FLOAT_EQ(NovelRT_GeoVector2F_getMagnitude(normal), sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2)));
}

TEST(InteropGeoVector2Test, getLengthReturnsCorrectLength) {
  NovelRTGeoVector2F cVector = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F normal = NovelRT_GeoVector2F_getNormalised(cVector);
  GeoVector2F& vec = reinterpret_cast<GeoVector2F&>(normal);
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

TEST(InteropGeoVector2Test, rotateToAngleAroundPointReturnsFailureStatucWhenUnableToOperate) {
  NovelRTGeoVector2F zero = NovelRT_GeoVector2F_zero();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_rotateToAngleAroundPoint(nullptr, 90.0f, zero, &err);
  NovelRTGeoVector2F other{-1.0f, 0.0f};
  NovelRTGeoVector2F epsilon = NovelRT_GeoVector2F_uniform(1e-7f);

  EXPECT_EQ(nrtResult, NOVELRT_FAILURE);
}

TEST(InteropGeoVector2Test, rotateToAngleAroundPointWhenGivenNullptrReturnsNullPtrMessageOnFailureStatus) {
  NovelRTGeoVector2F zero = NovelRT_GeoVector2F_zero();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_rotateToAngleAroundPoint(nullptr, 90.0f, zero, &err);
  NovelRTGeoVector2F other{-1.0f, 0.0f};
  NovelRTGeoVector2F epsilon = NovelRT_GeoVector2F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector2Test, rotateToAngleAroundPointWhenGivenNaNValueInLhsReturnsNaNMessageOnFailureStatus) {
  NovelRTGeoVector2F vec{ NAN, NAN };
  NovelRTGeoVector2F zero = NovelRT_GeoVector2F_zero();

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_rotateToAngleAroundPoint(&vec, 90.0f, zero, &err);
  NovelRTGeoVector2F other{-1.0f, 0.0f};
  NovelRTGeoVector2F epsilon = NovelRT_GeoVector2F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector2Test, rotateToAngleAroundPointWhenGivenNaNValueInRhsReturnsNaNMessageOnFailureStatus) {
  NovelRTGeoVector2F vec{ 0.0f, 1.0f };
  NovelRTGeoVector2F zero { NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_rotateToAngleAroundPoint(&vec, 90.0f, zero, &err);
  NovelRTGeoVector2F other{-1.0f, 0.0f};
  NovelRTGeoVector2F epsilon = NovelRT_GeoVector2F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector2Test, rotateToAngleAroundPointWhenGivenNaNValueForBothReturnsNaNMessageOnFailureStatus) {
  NovelRTGeoVector2F vec{ NAN, NAN };
  NovelRTGeoVector2F zero{ NAN, NAN };

  const char* err = nullptr;

  NovelRTResult nrtResult = NovelRT_GeoVector2F_rotateToAngleAroundPoint(&vec, 90.0f, zero, &err);
  NovelRTGeoVector2F other{-1.0f, 0.0f};
  NovelRTGeoVector2F epsilon = NovelRT_GeoVector2F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector2Test, isNaNReturnsTrueNaNVector) {
  NovelRTGeoVector2F nanVec {NAN, NAN};
  EXPECT_TRUE(NovelRT_GeoVector2F_isNaN(nanVec));
}