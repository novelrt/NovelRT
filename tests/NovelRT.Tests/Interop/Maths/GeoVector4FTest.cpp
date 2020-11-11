// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include <NovelRT.Interop/Maths/NrtGeoVector4F.h>
#include <cmath>

using namespace NovelRT;
using namespace NovelRT::Maths;

NrtGeoVector4F vec4One = Nrt_GeoVector4F_uniform(0.0);
NrtGeoVector4F vec4Two = Nrt_GeoVector4F_uniform(0.0f);
NrtGeoVector4F vec4Three = Nrt_GeoVector4F_uniform(1.0f);

TEST(InteropGeoVector4Test, createFromGeoVector2ReturnsGeoVector4WithCorrectAndVerbatimValues) {
  NrtGeoVector4F vec = Nrt_GeoVector4F_createFromGeoVector2F(Nrt_GeoVector2F_uniform(1.0f));
  EXPECT_TRUE(Nrt_GeoVector4F_equal(NrtGeoVector4F{1.0f, 1.0f, 0.0f, 0.0f}, vec));
}

TEST(InteropGeoVector4Test, equalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(Nrt_GeoVector4F_equal(vec4One, vec4Two));
}

TEST(InteropGeoVector4Test, inequalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(Nrt_GeoVector4F_notEqual(vec4One, vec4Three));
}

TEST(InteropGeoVector4Test, lessThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(Nrt_GeoVector4F_lessThan(vec4One, vec4Three));
}

TEST(InteropGeoVector4Test, lessOrEqualToThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(Nrt_GeoVector4F_lessThanOrEqualTo(vec4One, vec4Three));
  EXPECT_TRUE(Nrt_GeoVector4F_lessThanOrEqualTo(vec4Three, vec4Three));
}

TEST(InteropGeoVector4Test, greaterThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(Nrt_GeoVector4F_greaterThan(vec4Three, vec4One));
}

TEST(InteropGeoVector4Test, greaterThanOrEqualToOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(Nrt_GeoVector4F_greaterThanOrEqualTo(vec4Three, vec4One));
  EXPECT_TRUE(Nrt_GeoVector4F_greaterThanOrEqualTo(vec4Three, vec4Three));
}

TEST(InteropGeoVector4Test, staticUniformCallReturnsGeoVector4WithUniformValues) {
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(1.0f), vec4Three));
}

TEST(InteropGeoVector4Test, staticZeroCallReturnsGeoVector4Zero) {
  NrtGeoVector4F test = Nrt_GeoVector4F_uniform(0.0f);
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_zero(), test));
}

TEST(InteropGeoVector4Test, staticOneCallReturnsGeoVector4One) {
  NrtGeoVector4F test = Nrt_GeoVector4F_uniform(1.0f);
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_one(), test));
}

TEST(InteropGeoVector4Test, addOperatorAddsCorrectlyForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_addVector(test, test, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);  
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(2.0f), result));
}

TEST(InteropGeoVector4Test, addOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_addVector(test, test, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, addOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_addVector(test, test, nullptr);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  ////EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);  //TODO: fix this  //TODO: fix this 
}

TEST(InteropGeoVector4Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_addVector(test, Nrt_GeoVector4F_zero(), &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //////EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this  //TODO: fix this //TODO: fix this 
}

TEST(InteropGeoVector4Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_addVector(Nrt_GeoVector4F_zero(), test, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //////EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this  //TODO: fix this //TODO: fix this 
}

TEST(InteropGeoVector4Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_addVector(test, test, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //////EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this  //TODO: fix this //TODO: fix this 
}

TEST(InteropGeoVector4Test, subtractOperatorSubtractsCorrectlyForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_subtractVector(test, test, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);  
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_zero(), result));
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_subtractVector(test, test, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_subtractVector(test, test, nullptr);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  ////EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);  //TODO: fix this  //TODO: fix this 
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_subtractVector(test, Nrt_GeoVector4F_zero(), &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //////EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this  //TODO: fix this //TODO: fix this 
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_subtractVector(Nrt_GeoVector4F_zero(), test, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //////EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this  //TODO: fix this //TODO: fix this 
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_subtractVector(test, test, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //////EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this  //TODO: fix this //TODO: fix this 
}

TEST(InteropGeoVector4Test, multiplyOperatorMultipliesCorrectlyForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_uniform(2.0f);
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_multiplyVector(test, test, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);  
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(4.0f), result));
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_multiplyVector(test, test, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_multiplyVector(test, test, nullptr);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  ////EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);  //TODO: fix this  //TODO: fix this 
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_multiplyVector(test, Nrt_GeoVector4F_zero(), &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //////EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this  //TODO: fix this //TODO: fix this 
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_multiplyVector(Nrt_GeoVector4F_zero(), test, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //////EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this  //TODO: fix this //TODO: fix this 
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_subtractVector(test, test, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //////EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this  //TODO: fix this //TODO: fix this 
}

TEST(InteropGeoVector4Test, divideOperatorDividesCorrectlyForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_uniform(4.0f);
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err = nullptr;
  int32_t nrtResult = Nrt_GeoVector4F_divideVector(test, test, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);  
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_one(), result));
}

TEST(InteropGeoVector4Test, divideOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_divideVector(test, test, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, divideOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_divideVector(test, test, nullptr);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  ////EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);  //TODO: fix this  //TODO: fix this 
}

TEST(InteropGeoVector4Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_divideVector(test, Nrt_GeoVector4F_zero(), &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //////EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this  //TODO: fix this //TODO: fix this 
}

TEST(InteropGeoVector4Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_divideVector(Nrt_GeoVector4F_zero(), test, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //////EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this  //TODO: fix this //TODO: fix this 
}

TEST(InteropGeoVector4Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_divideVector(test, test, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //////EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this  //TODO: fix this //TODO: fix this 
}

TEST(InteropGeoVector4Test, divideOperatorReturnsDivideByZeroMessageOnFailureStatusWhenGeoVector4FZeroIsProvidedForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_divideVector(test, Nrt_GeoVector4F_zero(), &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  ////EXPECT_EQ(Nrt_getErrMsgIsDivideByZero(), err); //TODO: fix this  //TODO: fix this 
}

TEST(InteropGeoVector4Test, addOperatorAddsCorrectlyForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_addFloat(test, 1.0f, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(2.0f), result));
}

TEST(InteropGeoVector4Test, addOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_addFloat(test, 1.0f, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, addOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_addFloat(test, 1.0f, nullptr);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  ////EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);  //TODO: fix this  //TODO: fix this 
}

TEST(InteropGeoVector4Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_addFloat(test, 0.0f, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //////EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this  //TODO: fix this //TODO: fix this 
}

TEST(InteropGeoVector4Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_zero();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_addFloat(test, NAN, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //////EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this  //TODO: fix this //TODO: fix this 
}

TEST(InteropGeoVector4Test, addOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_addFloat(test, NAN, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //////EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this  //TODO: fix this //TODO: fix this 
}

TEST(InteropGeoVector4Test, subtractOperatorSubtractsCorrectlyForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_subtractFloat(test, 1.0f, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_zero(), result));
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_subtractFloat(test, 1.0f, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_subtractFloat(test, 1.0f, nullptr);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  ////EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);  //TODO: fix this  //TODO: fix this 
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_subtractFloat(test, 0.0f, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //////EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this  //TODO: fix this //TODO: fix this 
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_zero();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_subtractFloat(test, NAN, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //////EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this  //TODO: fix this //TODO: fix this 
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_subtractFloat(test, NAN, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //////EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this  //TODO: fix this //TODO: fix this 
}

TEST(InteropGeoVector4Test, multiplyOperatorMultipliesCorrectlyForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_uniform(2.0f);
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_multiplyFloat(test, 2.0f, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(4.0f), result));
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_multiplyFloat(test, 1.0f, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_multiplyFloat(test, 1.0f, nullptr);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  ////EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);  //TODO: fix this  //TODO: fix this 
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_multiplyFloat(test, 0.0f, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //////EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this  //TODO: fix this //TODO: fix this 
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_zero();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_multiplyFloat(test, NAN, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //////EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this  //TODO: fix this //TODO: fix this 
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_multiplyFloat(test, NAN, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //////EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this  //TODO: fix this //TODO: fix this 
}

TEST(InteropGeoVector4Test, divideOperatorDividesCorrectlyForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_uniform(4.0f);
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideFloat(test, 2.0f, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(2.0f), result));
}

TEST(InteropGeoVector4Test, divideOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_divideFloat(test, 1.0f, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, divideOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_divideFloat(test, 1.0f, nullptr);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  ////EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);  //TODO: fix this  //TODO: fix this 
}

TEST(InteropGeoVector4Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_divideFloat(test, 0.0f, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //////EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this  //TODO: fix this //TODO: fix this 
}

TEST(InteropGeoVector4Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_zero();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_divideFloat(test, NAN, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //////EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this  //TODO: fix this //TODO: fix this 
}

TEST(InteropGeoVector4Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_divideFloat(test, NAN, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //////EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this  //TODO: fix this //TODO: fix this 
}

TEST(InteropGeoVector4Test, divideOperatorReturnsDivideByZeroMessageOnFailureStatusWhenFloatZeroIsProvidedForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_divideFloat(test, 0.0f, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  ////EXPECT_EQ(Nrt_getErrMsgIsDivideByZero(), err); //TODO: fix this  //TODO: fix this 
}

TEST(InteropGeoVector4Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_addAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(2.0f), test));
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_addAssignVector(nullptr, test);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_addAssignVector(nullptr, test);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);  //TODO: fix this
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_addAssignVector(&test, Nrt_GeoVector4F_one());

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_addAssignVector(&test, Nrt_GeoVector4F_uniform(NAN));

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_addAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_subtractAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_zero(), test));
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_subtractAssignVector(nullptr, test);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_subtractAssignVector(nullptr, test);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);  //TODO: fix this
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_subtractAssignVector(&test, Nrt_GeoVector4F_one());

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_subtractAssignVector(&test, Nrt_GeoVector4F_uniform(NAN));

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_subtractAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_uniform(2.0f);

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_multiplyAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(4.0f), test));
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_multiplyAssignVector(nullptr, test);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_multiplyAssignVector(nullptr, test);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);  //TODO: fix this
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_multiplyAssignVector(&test, Nrt_GeoVector4F_one());

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_multiplyAssignVector(&test, Nrt_GeoVector4F_uniform(NAN));

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_multiplyAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_uniform(2.0f);

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_one(), test));
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideAssignVector(nullptr, test);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideAssignVector(nullptr, test);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);  //TODO: fix this
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideAssignVector(&test, Nrt_GeoVector4F_one());

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideAssignVector(&test, Nrt_GeoVector4F_uniform(NAN));

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsDivideByZeroMessageOnFailureStatusWhenGeoVector4FZeroIsProvidedForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideAssignVector(&test, Nrt_GeoVector4F_zero());

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsDivideByZero(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, addAssignOperatorAddsAndAssignsCorrectlyForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_addAssignFloat(&test, 1.0f);
  
  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(2.0f), test));
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_addAssignFloat(nullptr, 1.0f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_addAssignFloat(nullptr, 1.0f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);  //TODO: fix this
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_addAssignFloat(&test, 1.0f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_addAssignFloat(&test, NAN);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_addAssignFloat(&test, NAN);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_subtractAssignFloat(&test, 1.0f);
  
  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(0.0f), test));
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_subtractAssignFloat(nullptr, 1.0f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_subtractAssignFloat(nullptr, 1.0f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);  //TODO: fix this
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_subtractAssignFloat(&test, 1.0f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_subtractAssignFloat(&test, NAN);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_subtractAssignFloat(&test, NAN);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_uniform(2.0f);

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_multiplyAssignFloat(&test, 1.0f);
  
  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(2.0f), test));
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_multiplyAssignFloat(nullptr, 1.0f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_multiplyAssignFloat(nullptr, 1.0f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);  //TODO: fix this
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_multiplyAssignFloat(&test, 1.0f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_multiplyAssignFloat(&test, NAN);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_multiplyAssignFloat(&test, NAN);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, divideAssignOperatorDividesAndAssignsCorrectlyForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_uniform(2.0f);

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideAssignFloat(&test, 2.0f);
  
  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(1.0f), test));
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideAssignFloat(nullptr, 1.0f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsNullptrMessageOnFailureStatusWhenResultPtrIsNullForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideAssignFloat(nullptr, 1.0f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);  //TODO: fix this
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideAssignFloat(&test, 1.0f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideAssignFloat(&test, NAN);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideAssignFloat(&test, NAN);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsDivideByZeroMessageOnFailureStatusWhenFloatZeroIsProvidedForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideAssignFloat(&test, 0.0f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsDivideByZero(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, getNormalisedReturnsNormalisedGeoVector) {
  NrtGeoVector4F cVector = Nrt_GeoVector4F_one();
  NrtGeoVector4F normal = Nrt_GeoVector4F_getNormalised(cVector);
  GeoVector4F& vec = *reinterpret_cast<GeoVector4F*>(&normal);
  float normalisedTotal = sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2) + powf(vec.w, 2));
  EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(InteropGeoVector4Test, getMagnitudeReturnsCorrectLength) {
  NrtGeoVector4F cVector = Nrt_GeoVector4F_one();
  NrtGeoVector4F normal = Nrt_GeoVector4F_getNormalised(cVector);
  GeoVector4F& vec = *reinterpret_cast<GeoVector4F*>(&normal);
  EXPECT_FLOAT_EQ(Nrt_GeoVector4F_getMagnitude(normal), sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2) + powf(vec.w, 2)));
}

TEST(InteropGeoVector4Test, getLengthReturnsCorrectLength) {
  NrtGeoVector4F cVector = Nrt_GeoVector4F_one();
  NrtGeoVector4F normal = Nrt_GeoVector4F_getNormalised(cVector);
  GeoVector4F& vec = *reinterpret_cast<GeoVector4F*>(&normal);
  EXPECT_FLOAT_EQ(Nrt_GeoVector4F_getLength(normal), sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2) + powf(vec.w, 2)));
}

TEST(InteropGeoVector4Test, rotateToAngleAroundPointRotatesCorrectAmount) {
  NrtGeoVector4F vec{0.0f, 1.0f};
  NrtGeoVector3F zero = Nrt_GeoVector3F_zero();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_rotateToAngleAroundPoint(&vec, 90.0f, zero);
  NrtGeoVector4F other{-1.0f, 0.0f};
  NrtGeoVector4F epsilon = Nrt_GeoVector4F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector4F_epsilonEquals(vec, other, epsilon));
}

TEST(InteropGeoVector4Test, rotateToAngleAroundPointReturnsFailureStatucWhenUnableToOperate) {
  NrtGeoVector3F zero = Nrt_GeoVector3F_zero();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_rotateToAngleAroundPoint(nullptr, 90.0f, zero);
  NrtGeoVector4F other{-1.0f, 0.0f};
  NrtGeoVector4F epsilon = Nrt_GeoVector4F_uniform(1e-7f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, rotateToAngleAroundPointWhenGivenNullptrReturnsNullPtrMessageOnFailureStatus) {
  NrtGeoVector3F zero = Nrt_GeoVector3F_zero();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_rotateToAngleAroundPoint(nullptr, 90.0f, zero);
  NrtGeoVector4F other{-1.0f, 0.0f};
  NrtGeoVector4F epsilon = Nrt_GeoVector4F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), err);  //TODO: fix this
}

TEST(InteropGeoVector4Test, rotateToAngleAroundPointWhenGivenNaNValueInLhsReturnsNaNMessageOnFailureStatus) {
  NrtGeoVector4F vec{ NAN, NAN, NAN, NAN };
  NrtGeoVector3F zero = Nrt_GeoVector3F_zero();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_rotateToAngleAroundPoint(&vec, 90.0f, zero);
  NrtGeoVector4F other{-1.0f, 0.0f};
  NrtGeoVector4F epsilon = Nrt_GeoVector4F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, rotateToAngleAroundPointWhenGivenNaNValueInRhsReturnsNaNMessageOnFailureStatus) {
  NrtGeoVector4F vec{ 0.0f, 1.0f };
  NrtGeoVector3F zero { NAN, NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_rotateToAngleAroundPoint(&vec, 90.0f, zero);
  NrtGeoVector4F other{-1.0f, 0.0f};
  NrtGeoVector4F epsilon = Nrt_GeoVector4F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, rotateToAngleAroundPointWhenGivenNaNValueForBothReturnsNaNMessageOnFailureStatus) {
  NrtGeoVector4F vec{ NAN, NAN, NAN, NAN };
  NrtGeoVector3F zero{ NAN, NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_rotateToAngleAroundPoint(&vec, 90.0f, zero);
  NrtGeoVector4F other{-1.0f, 0.0f};
  NrtGeoVector4F epsilon = Nrt_GeoVector4F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector4Test, isNaNReturnsTrueNaNVector) {
  NrtGeoVector4F nanVec {NAN, NAN};
  EXPECT_TRUE(Nrt_GeoVector4F_isNaN(nanVec));
}

