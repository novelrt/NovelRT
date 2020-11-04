// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include <NovelRT.Interop/Maths/NovelRTGeoVector3F.h>
#include <cmath>

using namespace NovelRT;
using namespace NovelRT::Maths;

NrtGeoVector3F vec3One = Nrt_GeoVector3F_uniform(0.0);
NrtGeoVector3F vec3Two = Nrt_GeoVector3F_uniform(0.0f);
NrtGeoVector3F vec3Three = Nrt_GeoVector3F_uniform(1.0f);

TEST(InteropGeoVector3Test, createFromGeoVector2ReturnsGeoVector3WithCorrectAndVerbatimValues) {
  NrtGeoVector3F vec = Nrt_GeoVector3F_createFromGeoVector2F(Nrt_GeoVector2F_uniform(1.0f));
  EXPECT_TRUE(Nrt_GeoVector3F_equal(NrtGeoVector3F{1.0f, 1.0f, 0.0f}, vec));
}

TEST(InteropGeoVector3Test, equalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(Nrt_GeoVector3F_equal(vec3One, vec3Two));
}

TEST(InteropGeoVector3Test, inequalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(Nrt_GeoVector3F_notEqual(vec3One, vec3Three));
}

TEST(InteropGeoVector3Test, lessThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(Nrt_GeoVector3F_lessThan(vec3One, vec3Three));
}

TEST(InteropGeoVector3Test, lessOrEqualToThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(Nrt_GeoVector3F_lessThanOrEqualTo(vec3One, vec3Three));
  EXPECT_TRUE(Nrt_GeoVector3F_lessThanOrEqualTo(vec3Three, vec3Three));
}

TEST(InteropGeoVector3Test, greaterThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(Nrt_GeoVector3F_greaterThan(vec3Three, vec3One));
}

TEST(InteropGeoVector3Test, greaterThanOrEqualToOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(Nrt_GeoVector3F_greaterThanOrEqualTo(vec3Three, vec3One));
  EXPECT_TRUE(Nrt_GeoVector3F_greaterThanOrEqualTo(vec3Three, vec3Three));
}

TEST(InteropGeoVector3Test, staticUniformCallReturnsGeoVector3WithUniformValues) {
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(1.0f), vec3Three));
}

TEST(InteropGeoVector3Test, staticZeroCallReturnsGeoVector3Zero) {
  NrtGeoVector3F test = Nrt_GeoVector3F_uniform(0.0f);
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_zero(), test));
}

TEST(InteropGeoVector3Test, staticOneCallReturnsGeoVector3One) {
  NrtGeoVector3F test = Nrt_GeoVector3F_uniform(1.0f);
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_one(), test));
}

TEST(InteropGeoVector3Test, addOperatorAddsCorrectlyForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_addVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);  
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(2.0f), result));
}

TEST(InteropGeoVector3Test, addOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_addVector(test, test, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector3Test, addOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_addVector(test, test, nullptr, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector3Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_addVector(test, Nrt_GeoVector3F_zero(), &result, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_addVector(Nrt_GeoVector3F_zero(), test, &result, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_addVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, subtractOperatorSubtractsCorrectlyForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_subtractVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);  
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_zero(), result));
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_subtractVector(test, test, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_subtractVector(test, test, nullptr, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_subtractVector(test, Nrt_GeoVector3F_zero(), &result, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_subtractVector(Nrt_GeoVector3F_zero(), test, &result, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_subtractVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, multiplyOperatorMultipliesCorrectlyForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_uniform(2.0f);
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_multiplyVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);  
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(4.0f), result));
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_multiplyVector(test, test, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_multiplyVector(test, test, nullptr, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_multiplyVector(test, Nrt_GeoVector3F_zero(), &result, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_multiplyVector(Nrt_GeoVector3F_zero(), test, &result, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_subtractVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, divideOperatorDividesCorrectlyForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_uniform(4.0f);
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err = nullptr;
  int32_t nrtResult = Nrt_GeoVector3F_divideVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);  
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_one(), result));
}

TEST(InteropGeoVector3Test, divideOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_divideVector(test, test, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector3Test, divideOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_divideVector(test, test, nullptr, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector3Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_divideVector(test, Nrt_GeoVector3F_zero(), &result, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_divideVector(Nrt_GeoVector3F_zero(), test, &result, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_divideVector(test, test, &result, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, divideOperatorReturnsDivideByZeroMessageOnFailureStatusReturnsGeoVector3FZeroIsProvidedForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_divideVector(test, Nrt_GeoVector3F_zero(), &result, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsDivideByZero(), err);  
}

TEST(InteropGeoVector3Test, addOperatorAddsCorrectlyForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_addFloat(test, 1.0f, &result, &err);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(2.0f), result));
}

TEST(InteropGeoVector3Test, addOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_addFloat(test, 1.0f, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector3Test, addOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_addFloat(test, 1.0f, nullptr, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector3Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_addFloat(test, 0.0f, &result, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_zero();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_addFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_addFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, subtractOperatorSubtractsCorrectlyForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_subtractFloat(test, 1.0f, &result, &err);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_zero(), result));
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_subtractFloat(test, 1.0f, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_subtractFloat(test, 1.0f, nullptr, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_subtractFloat(test, 0.0f, &result, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_zero();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_subtractFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_subtractFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, multiplyOperatorMultipliesCorrectlyForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_uniform(2.0f);
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_multiplyFloat(test, 2.0f, &result, &err);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(4.0f), result));
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_multiplyFloat(test, 1.0f, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_multiplyFloat(test, 1.0f, nullptr, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_multiplyFloat(test, 0.0f, &result, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_zero();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_multiplyFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_multiplyFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, divideOperatorDividesCorrectlyForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_uniform(4.0f);
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideFloat(test, 2.0f, &result, &err);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(2.0f), result));
}

TEST(InteropGeoVector3Test, divideOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_divideFloat(test, 1.0f, nullptr, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector3Test, divideOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_divideFloat(test, 1.0f, nullptr, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);  
}

TEST(InteropGeoVector3Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_divideFloat(test, 0.0f, &result, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_zero();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_divideFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_divideFloat(test, NAN, &result, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);  
}

TEST(InteropGeoVector3Test, divideOperatorReturnsDivideByZeroMessageOnFailureStatusWhenFloatZeroIsProvidedForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_divideFloat(test, 0.0f, &result, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsDivideByZero(), err);  
}

TEST(InteropGeoVector3Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_addAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(2.0f), test));
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_addAssignVector(nullptr, test, &err);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_addAssignVector(nullptr, test, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_addAssignVector(&test, Nrt_GeoVector3F_one(), &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_addAssignVector(&test, Nrt_GeoVector3F_uniform(NAN), &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_addAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_subtractAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_zero(), test));
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_subtractAssignVector(nullptr, test, &err);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_subtractAssignVector(nullptr, test, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_subtractAssignVector(&test, Nrt_GeoVector3F_one(), &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_subtractAssignVector(&test, Nrt_GeoVector3F_uniform(NAN), &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_subtractAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_uniform(2.0f);

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_multiplyAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(4.0f), test));
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_multiplyAssignVector(nullptr, test, &err);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_multiplyAssignVector(nullptr, test, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_multiplyAssignVector(&test, Nrt_GeoVector3F_one(), &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_multiplyAssignVector(&test, Nrt_GeoVector3F_uniform(NAN), &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_multiplyAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_uniform(2.0f);

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_one(), test));
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideAssignVector(nullptr, test, &err);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideAssignVector(nullptr, test, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideAssignVector(&test, Nrt_GeoVector3F_one(), &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideAssignVector(&test, Nrt_GeoVector3F_uniform(NAN), &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideAssignVector(&test, test, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsDivideByZeroMessageOnFailureStatusReturnsGeoVector3FZeroIsProvidedForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideAssignVector(&test, Nrt_GeoVector3F_zero(), &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsDivideByZero(), err);
}

TEST(InteropGeoVector3Test, addAssignOperatorAddsAndAssignsCorrectlyForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_addAssignFloat(&test, 1.0f, &err);
  
  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(2.0f), test));
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_addAssignFloat(nullptr, 1.0f, &err);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_addAssignFloat(nullptr, 1.0f, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_addAssignFloat(&test, 1.0f, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_addAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_addAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_subtractAssignFloat(&test, 1.0f, &err);
  
  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(0.0f), test));
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_subtractAssignFloat(nullptr, 1.0f, &err);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_subtractAssignFloat(nullptr, 1.0f, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_subtractAssignFloat(&test, 1.0f, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_subtractAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_subtractAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_uniform(2.0f);

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_multiplyAssignFloat(&test, 1.0f, &err);
  
  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(2.0f), test));
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_multiplyAssignFloat(nullptr, 1.0f, &err);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_multiplyAssignFloat(nullptr, 1.0f, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_multiplyAssignFloat(&test, 1.0f, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_multiplyAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_multiplyAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, divideAssignOperatorDividesAndAssignsCorrectlyForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_uniform(2.0f);

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideAssignFloat(&test, 2.0f, &err);
  
  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(1.0f), test));
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideAssignFloat(nullptr, 1.0f, &err);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideAssignFloat(nullptr, 1.0f, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideAssignFloat(&test, 1.0f, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideAssignFloat(&test, NAN, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsDivideByZeroMessageOnFailureStatusWhenFloatZeroIsProvidedForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideAssignFloat(&test, 0.0f, &err);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsDivideByZero(), err);
}

TEST(InteropGeoVector3Test, getNormalisedReturnsNormalisedGeoVector) {
  NrtGeoVector3F cVector = Nrt_GeoVector3F_one();
  NrtGeoVector3F normal = Nrt_GeoVector3F_getNormalised(cVector);
  GeoVector3F& vec = *reinterpret_cast<GeoVector3F*>(&normal);
  float normalisedTotal = sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2));
  EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(InteropGeoVector3Test, getMagnitudeReturnsCorrectLength) {
  NrtGeoVector3F cVector = Nrt_GeoVector3F_one();
  NrtGeoVector3F normal = Nrt_GeoVector3F_getNormalised(cVector);
  GeoVector3F& vec = *reinterpret_cast<GeoVector3F*>(&normal);
  EXPECT_FLOAT_EQ(Nrt_GeoVector3F_getMagnitude(normal), sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2)));
}

TEST(InteropGeoVector3Test, getLengthReturnsCorrectLength) {
  NrtGeoVector3F cVector = Nrt_GeoVector3F_one();
  NrtGeoVector3F normal = Nrt_GeoVector3F_getNormalised(cVector);
  GeoVector3F& vec = *reinterpret_cast<GeoVector3F*>(&normal);
  EXPECT_FLOAT_EQ(Nrt_GeoVector3F_getLength(normal), sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2)));
}

TEST(InteropGeoVector3Test, rotateToAngleAroundPointRotatesCorrectAmount) {
  NrtGeoVector3F vec{0.0f, 1.0f};
  NrtGeoVector3F zero = Nrt_GeoVector3F_zero();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_rotateToAngleAroundPoint(&vec, 90.0f, zero, &err);
  NrtGeoVector3F other{-1.0f, 0.0f};
  NrtGeoVector3F epsilon = Nrt_GeoVector3F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector3F_epsilonEquals(vec, other, epsilon));
}

TEST(InteropGeoVector3Test, rotateToAngleAroundPointReturnsFailureStatucWhenUnableToOperate) {
  NrtGeoVector3F zero = Nrt_GeoVector3F_zero();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_rotateToAngleAroundPoint(nullptr, 90.0f, zero, &err);
  NrtGeoVector3F other{-1.0f, 0.0f};
  NrtGeoVector3F epsilon = Nrt_GeoVector3F_uniform(1e-7f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector3Test, rotateToAngleAroundPointWhenGivenNullptrReturnsNullPtrMessageOnFailureStatus) {
  NrtGeoVector3F zero = Nrt_GeoVector3F_zero();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_rotateToAngleAroundPoint(nullptr, 90.0f, zero, &err);
  NrtGeoVector3F other{-1.0f, 0.0f};
  NrtGeoVector3F epsilon = Nrt_GeoVector3F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);
}

TEST(InteropGeoVector3Test, rotateToAngleAroundPointWhenGivenNaNValueInLhsReturnsNaNMessageOnFailureStatus) {
  NrtGeoVector3F vec{ NAN, NAN };
  NrtGeoVector3F zero = Nrt_GeoVector3F_zero();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_rotateToAngleAroundPoint(&vec, 90.0f, zero, &err);
  NrtGeoVector3F other{-1.0f, 0.0f};
  NrtGeoVector3F epsilon = Nrt_GeoVector3F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, rotateToAngleAroundPointWhenGivenNaNValueInRhsReturnsNaNMessageOnFailureStatus) {
  NrtGeoVector3F vec{ 0.0f, 1.0f };
  NrtGeoVector3F zero { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_rotateToAngleAroundPoint(&vec, 90.0f, zero, &err);
  NrtGeoVector3F other{-1.0f, 0.0f};
  NrtGeoVector3F epsilon = Nrt_GeoVector3F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, rotateToAngleAroundPointWhenGivenNaNValueForBothReturnsNaNMessageOnFailureStatus) {
  NrtGeoVector3F vec{ NAN, NAN };
  NrtGeoVector3F zero{ NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_rotateToAngleAroundPoint(&vec, 90.0f, zero, &err);
  NrtGeoVector3F other{-1.0f, 0.0f};
  NrtGeoVector3F epsilon = Nrt_GeoVector3F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  EXPECT_EQ(Nrt_getErrMsgIsNaN(), err);
}

TEST(InteropGeoVector3Test, isNaNReturnsTrueNaNVector) {
  NrtGeoVector3F nanVec {NAN, NAN};
  EXPECT_TRUE(Nrt_GeoVector3F_isNaN(nanVec));
}