// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include <NovelRT.Interop/Maths/NrtGeoVector2F.h>
#include <cmath>

using namespace NovelRT;
using namespace NovelRT::Maths;

NrtGeoVector2F vec2One = Nrt_GeoVector2F_uniform(0.0);
NrtGeoVector2F vec2Two = Nrt_GeoVector2F_uniform(0.0f);
NrtGeoVector2F vec2Three = Nrt_GeoVector2F_uniform(1.0f);

TEST(InteropGeoVector2Test, equalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(Nrt_GeoVector2F_equal(vec2One, vec2Two));
}

TEST(InteropGeoVector2Test, inequalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(Nrt_GeoVector2F_notEqual(vec2One, vec2Three));
}

TEST(InteropGeoVector2Test, lessThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(Nrt_GeoVector2F_lessThan(vec2One, vec2Three));
}

TEST(InteropGeoVector2Test, lessOrEqualToThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(Nrt_GeoVector2F_lessThanOrEqualTo(vec2One, vec2Three));
  EXPECT_TRUE(Nrt_GeoVector2F_lessThanOrEqualTo(vec2Three, vec2Three));
}

TEST(InteropGeoVector2Test, greaterThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(Nrt_GeoVector2F_greaterThan(vec2Three, vec2One));
}

TEST(InteropGeoVector2Test, greaterThanOrEqualToOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(Nrt_GeoVector2F_greaterThanOrEqualTo(vec2Three, vec2One));
  EXPECT_TRUE(Nrt_GeoVector2F_greaterThanOrEqualTo(vec2Three, vec2Three));
}

TEST(InteropGeoVector2Test, staticUniformCallReturnsGeoVector2WithUniformValues) {
  EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(1.0f), vec2Three));
}

TEST(InteropGeoVector2Test, staticZeroCallReturnsGeoVector2Zero) {
  NrtGeoVector2F test = Nrt_GeoVector2F_uniform(0.0f);
  EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_zero(), test));
}

TEST(InteropGeoVector2Test, staticOneCallReturnsGeoVector2One) {
  NrtGeoVector2F test = Nrt_GeoVector2F_uniform(1.0f);
  EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_one(), test));
}

TEST(InteropGeoVector2Test, addOperatorAddsCorrectlyForGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_addVector(test, test, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);  
  EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(2.0f), result));
}

TEST(InteropGeoVector2Test, addOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_addVector(test, test, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector2Test, addOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_addVector(test, test, nullptr);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector2F) {
  NrtGeoVector2F test { NAN, NAN };
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_addVector(test, Nrt_GeoVector2F_zero(), &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector2F) {
  NrtGeoVector2F test { NAN, NAN };
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_addVector(Nrt_GeoVector2F_zero(), test, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector2F) {
  NrtGeoVector2F test { NAN, NAN };
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_addVector(test, test, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, subtractOperatorSubtractsCorrectlyForGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_subtractVector(test, test, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);  
  EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_zero(), result));
}

TEST(InteropGeoVector2Test, subtractOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_subtractVector(test, test, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector2Test, subtractOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_subtractVector(test, test, nullptr);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector2F) {
  NrtGeoVector2F test { NAN, NAN };
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_subtractVector(test, Nrt_GeoVector2F_zero(), &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector2F) {
  NrtGeoVector2F test { NAN, NAN };
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_subtractVector(Nrt_GeoVector2F_zero(), test, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector2F) {
  NrtGeoVector2F test { NAN, NAN };
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_subtractVector(test, test, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, multiplyOperatorMultipliesCorrectlyForGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_uniform(2.0f);
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_multiplyVector(test, test, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);  
  EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(4.0f), result));
}

TEST(InteropGeoVector2Test, multiplyOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_multiplyVector(test, test, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector2Test, multiplyOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_multiplyVector(test, test, nullptr);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector2F) {
  NrtGeoVector2F test { NAN, NAN };
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_multiplyVector(test, Nrt_GeoVector2F_zero(), &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector2F) {
  NrtGeoVector2F test { NAN, NAN };
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_multiplyVector(Nrt_GeoVector2F_zero(), test, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector2F) {
  NrtGeoVector2F test { NAN, NAN };
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_subtractVector(test, test, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, divideOperatorDividesCorrectlyForGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_uniform(4.0f);
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err = nullptr;
  int32_t nrtResult = Nrt_GeoVector2F_divideVector(test, test, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);  
  EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_one(), result));
}

TEST(InteropGeoVector2Test, divideOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_divideVector(test, test, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector2Test, divideOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_divideVector(test, test, nullptr);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector2F) {
  NrtGeoVector2F test { NAN, NAN };
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_divideVector(test, Nrt_GeoVector2F_zero(), &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector2F) {
  NrtGeoVector2F test { NAN, NAN };
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_divideVector(Nrt_GeoVector2F_zero(), test, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector2F) {
  NrtGeoVector2F test { NAN, NAN };
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_divideVector(test, test, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, divideOperatorReturnsDivideByZeroMessageOnFailureStatusWhenGeoVector2FZeroIsProvidedForGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_divideVector(test, Nrt_GeoVector2F_zero(), &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsDivideByZero, err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, addOperatorAddsCorrectlyForFloat) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_addFloat(test, 1.0f, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(2.0f), result));
}

TEST(InteropGeoVector2Test, addOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_addFloat(test, 1.0f, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector2Test, addOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_addFloat(test, 1.0f, nullptr);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector2F test { NAN, NAN };
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_addFloat(test, 0.0f, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector2F test = Nrt_GeoVector2F_zero();
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_addFloat(test, NAN, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector2F test { NAN, NAN };
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_addFloat(test, NAN, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, subtractOperatorSubtractsCorrectlyForFloat) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_subtractFloat(test, 1.0f, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_zero(), result));
}

TEST(InteropGeoVector2Test, subtractOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_subtractFloat(test, 1.0f, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector2Test, subtractOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_subtractFloat(test, 1.0f, nullptr);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector2F test { NAN, NAN };
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_subtractFloat(test, 0.0f, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector2F test = Nrt_GeoVector2F_zero();
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_subtractFloat(test, NAN, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector2F test { NAN, NAN };
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_subtractFloat(test, NAN, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, multiplyOperatorMultipliesCorrectlyForFloat) {
  NrtGeoVector2F test = Nrt_GeoVector2F_uniform(2.0f);
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_multiplyFloat(test, 2.0f, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(4.0f), result));
}

TEST(InteropGeoVector2Test, multiplyOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_multiplyFloat(test, 1.0f, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector2Test, multiplyOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_multiplyFloat(test, 1.0f, nullptr);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector2F test { NAN, NAN };
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_multiplyFloat(test, 0.0f, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector2F test = Nrt_GeoVector2F_zero();
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_multiplyFloat(test, NAN, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector2F test { NAN, NAN };
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_multiplyFloat(test, NAN, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, divideOperatorDividesCorrectlyForFloat) {
  NrtGeoVector2F test = Nrt_GeoVector2F_uniform(4.0f);
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_divideFloat(test, 2.0f, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(2.0f), result));
}

TEST(InteropGeoVector2Test, divideOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_divideFloat(test, 1.0f, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector2Test, divideOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_divideFloat(test, 1.0f, nullptr);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector2F test { NAN, NAN };
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_divideFloat(test, 0.0f, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector2F test = Nrt_GeoVector2F_zero();
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_divideFloat(test, NAN, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector2F test { NAN, NAN };
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_divideFloat(test, NAN, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, divideOperatorReturnsDivideByZeroMessageOnFailureStatusWhenFloatZeroIsProvidedForFloat) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();
  NrtGeoVector2F result = Nrt_GeoVector2F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector2F_divideFloat(test, 0.0f, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsDivideByZero, err); //TODO: fix this  
}

TEST(InteropGeoVector2Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_addAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(2.0f), test));
}

TEST(InteropGeoVector2Test, addAssignOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_addAssignVector(nullptr, test);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector2Test, addAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_addAssignVector(nullptr, test);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err); //TODO: fix this
}

TEST(InteropGeoVector2Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector2F) {
  NrtGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_addAssignVector(&test, Nrt_GeoVector2F_one());

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_addAssignVector(&test, Nrt_GeoVector2F_uniform(NAN));

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector2F) {
  NrtGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_addAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_subtractAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_zero(), test));
}

TEST(InteropGeoVector2Test, subtractAssignOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_subtractAssignVector(nullptr, test);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector2Test, subtractAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_subtractAssignVector(nullptr, test);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err); //TODO: fix this
}

TEST(InteropGeoVector2Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector2F) {
  NrtGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_subtractAssignVector(&test, Nrt_GeoVector2F_one());

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_subtractAssignVector(&test, Nrt_GeoVector2F_uniform(NAN));

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector2F) {
  NrtGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_subtractAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_uniform(2.0f);

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_multiplyAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(4.0f), test));
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_multiplyAssignVector(nullptr, test);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_multiplyAssignVector(nullptr, test);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err); //TODO: fix this
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector2F) {
  NrtGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_multiplyAssignVector(&test, Nrt_GeoVector2F_one());

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_multiplyAssignVector(&test, Nrt_GeoVector2F_uniform(NAN));

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector2F) {
  NrtGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_multiplyAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_uniform(2.0f);

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_divideAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_one(), test));
}

TEST(InteropGeoVector2Test, divideAssignOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_divideAssignVector(nullptr, test);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector2Test, divideAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_divideAssignVector(nullptr, test);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err); //TODO: fix this
}

TEST(InteropGeoVector2Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector2F) {
  NrtGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_divideAssignVector(&test, Nrt_GeoVector2F_one());

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_divideAssignVector(&test, Nrt_GeoVector2F_uniform(NAN));

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector2F) {
  NrtGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_divideAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, divideAssignOperatorReturnsDivideByZeroMessageOnFailureStatusWhenGeoVector2FZeroIsProvidedForGeoVector2F) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_divideAssignVector(&test, Nrt_GeoVector2F_zero());

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsDivideByZero, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, addAssignOperatorAddsAndAssignsCorrectlyForFloat) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_addAssignFloat(&test, 1.0f);
  
  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(2.0f), test));
}

TEST(InteropGeoVector2Test, addAssignOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_addAssignFloat(nullptr, 1.0f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector2Test, addAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_addAssignFloat(nullptr, 1.0f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err); //TODO: fix this
}

TEST(InteropGeoVector2Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_addAssignFloat(&test, 1.0f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_addAssignFloat(&test, NAN);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_addAssignFloat(&test, NAN);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForFloat) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_subtractAssignFloat(&test, 1.0f);
  
  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(0.0f), test));
}

TEST(InteropGeoVector2Test, subtractAssignOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_subtractAssignFloat(nullptr, 1.0f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector2Test, subtractAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_subtractAssignFloat(nullptr, 1.0f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err); //TODO: fix this
}

TEST(InteropGeoVector2Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_subtractAssignFloat(&test, 1.0f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_subtractAssignFloat(&test, NAN);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_subtractAssignFloat(&test, NAN);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForFloat) {
  NrtGeoVector2F test = Nrt_GeoVector2F_uniform(2.0f);

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_multiplyAssignFloat(&test, 1.0f);
  
  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(2.0f), test));
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_multiplyAssignFloat(nullptr, 1.0f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_multiplyAssignFloat(nullptr, 1.0f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err); //TODO: fix this
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_multiplyAssignFloat(&test, 1.0f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_multiplyAssignFloat(&test, NAN);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_multiplyAssignFloat(&test, NAN);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, divideAssignOperatorDividesAndAssignsCorrectlyForFloat) {
  NrtGeoVector2F test = Nrt_GeoVector2F_uniform(2.0f);

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_divideAssignFloat(&test, 2.0f);
  
  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(1.0f), test));
}

TEST(InteropGeoVector2Test, divideAssignOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_divideAssignFloat(nullptr, 1.0f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector2Test, divideAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_divideAssignFloat(nullptr, 1.0f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err); //TODO: fix this
}

TEST(InteropGeoVector2Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_divideAssignFloat(&test, 1.0f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_divideAssignFloat(&test, NAN);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector2F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_divideAssignFloat(&test, NAN);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, divideAssignOperatorReturnsDivideByZeroMessageOnFailureStatusWhenFloatZeroIsProvidedForFloat) {
  NrtGeoVector2F test = Nrt_GeoVector2F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_divideAssignFloat(&test, 0.0f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsDivideByZero, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, getNormalisedReturnsNormalisedGeoVector) {
  NrtGeoVector2F cVector = Nrt_GeoVector2F_one();
  NrtGeoVector2F normal = Nrt_GeoVector2F_getNormalised(cVector);
  GeoVector2F& vec = *reinterpret_cast<GeoVector2F*>(&normal);
  float normalisedTotal = sqrtf(powf(vec.x, 2) + powf(vec.y, 2));
  EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(InteropGeoVector2Test, getMagnitudeReturnsCorrectLength) {
  NrtGeoVector2F cVector = Nrt_GeoVector2F_one();
  NrtGeoVector2F normal = Nrt_GeoVector2F_getNormalised(cVector);
  GeoVector2F& vec = *reinterpret_cast<GeoVector2F*>(&normal);
  EXPECT_FLOAT_EQ(Nrt_GeoVector2F_getMagnitude(normal), sqrtf(powf(vec.x, 2) + powf(vec.y, 2)));
}

TEST(InteropGeoVector2Test, getLengthReturnsCorrectLength) {
  NrtGeoVector2F cVector = Nrt_GeoVector2F_one();
  NrtGeoVector2F normal = Nrt_GeoVector2F_getNormalised(cVector);
  GeoVector2F& vec = *reinterpret_cast<GeoVector2F*>(&normal);
  EXPECT_FLOAT_EQ(Nrt_GeoVector2F_getLength(normal), sqrtf(powf(vec.x, 2) + powf(vec.y, 2)));
}

TEST(InteropGeoVector2Test, rotateToAngleAroundPointRotatesCorrectAmount) {
  NrtGeoVector2F vec{0.0f, 1.0f};
  NrtGeoVector2F zero = Nrt_GeoVector2F_zero();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_rotateToAngleAroundPoint(&vec, 90.0f, zero);
  NrtGeoVector2F other{-1.0f, 0.0f};
  NrtGeoVector2F epsilon = Nrt_GeoVector2F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector2F_epsilonEquals(vec, other, epsilon));
}

TEST(InteropGeoVector2Test, rotateToAngleAroundPointReturnsFailureStatucWhenUnableToOperate) {
  NrtGeoVector2F zero = Nrt_GeoVector2F_zero();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_rotateToAngleAroundPoint(nullptr, 90.0f, zero);
  NrtGeoVector2F other{-1.0f, 0.0f};
  NrtGeoVector2F epsilon = Nrt_GeoVector2F_uniform(1e-7f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
}

TEST(InteropGeoVector2Test, rotateToAngleAroundPointWhenGivenNullptrReturnsNullPtrMessageOnFailureStatus) {
  NrtGeoVector2F zero = Nrt_GeoVector2F_zero();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_rotateToAngleAroundPoint(nullptr, 90.0f, zero);
  NrtGeoVector2F other{-1.0f, 0.0f};
  NrtGeoVector2F epsilon = Nrt_GeoVector2F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err); //TODO: fix this
}

TEST(InteropGeoVector2Test, rotateToAngleAroundPointWhenGivenNaNValueInLhsReturnsNaNMessageOnFailureStatus) {
  NrtGeoVector2F vec{ NAN, NAN };
  NrtGeoVector2F zero = Nrt_GeoVector2F_zero();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_rotateToAngleAroundPoint(&vec, 90.0f, zero);
  NrtGeoVector2F other{-1.0f, 0.0f};
  NrtGeoVector2F epsilon = Nrt_GeoVector2F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, rotateToAngleAroundPointWhenGivenNaNValueInRhsReturnsNaNMessageOnFailureStatus) {
  NrtGeoVector2F vec{ 0.0f, 1.0f };
  NrtGeoVector2F zero { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_rotateToAngleAroundPoint(&vec, 90.0f, zero);
  NrtGeoVector2F other{-1.0f, 0.0f};
  NrtGeoVector2F epsilon = Nrt_GeoVector2F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, rotateToAngleAroundPointWhenGivenNaNValueForBothReturnsNaNMessageOnFailureStatus) {
  NrtGeoVector2F vec{ NAN, NAN };
  NrtGeoVector2F zero{ NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector2F_rotateToAngleAroundPoint(&vec, 90.0f, zero);
  NrtGeoVector2F other{-1.0f, 0.0f};
  NrtGeoVector2F epsilon = Nrt_GeoVector2F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN, err); //TODO: fix this
}

TEST(InteropGeoVector2Test, isNaNReturnsTrueNaNVector) {
  NrtGeoVector2F nanVec {NAN, NAN};
  EXPECT_TRUE(Nrt_GeoVector2F_isNaN(nanVec));
}