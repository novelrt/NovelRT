// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include <NovelRT.Interop/Maths/NrtGeoVector3F.h>
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
  int32_t nrtResult = Nrt_GeoVector3F_addVector(test, test, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);  
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(2.0f), result));
}

TEST(InteropGeoVector3Test, addOperatorReturnsNullptrFailureWhenGivenNullptrForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_addVector(test, test, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector3Test, addOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_addVector(test, Nrt_GeoVector3F_zero(), &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, addOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_addVector(Nrt_GeoVector3F_zero(), test, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, addOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_addVector(test, test, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, subtractOperatorSubtractsCorrectlyForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_subtractVector(test, test, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);  
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_zero(), result));
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsNullptrFailureWhenGivenNullptrForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_subtractVector(test, test, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_subtractVector(test, Nrt_GeoVector3F_zero(), &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);  
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_subtractVector(Nrt_GeoVector3F_zero(), test, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_subtractVector(test, test, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, multiplyOperatorMultipliesCorrectlyForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_uniform(2.0f);
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_multiplyVector(test, test, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);  
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(4.0f), result));
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsFailureStatusWhenUnableToOperateForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_multiplyVector(test, test, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_multiplyVector(test, Nrt_GeoVector3F_zero(), &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_multiplyVector(Nrt_GeoVector3F_zero(), test, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER); 
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_subtractVector(test, test, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, divideOperatorDividesCorrectlyForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_uniform(4.0f);
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err = nullptr;
  int32_t nrtResult = Nrt_GeoVector3F_divideVector(test, test, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);  
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_one(), result));
}

TEST(InteropGeoVector3Test, divideOperatorReturnsNullptrFailureWhenGivenNullptrForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_divideVector(test, test, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector3Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForLhsForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_divideVector(test, Nrt_GeoVector3F_zero(), &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForRhsForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_divideVector(Nrt_GeoVector3F_zero(), test, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, divideOperatorReturnsNaNMessageOnFailureStatusWhenNaNIsProvidedForBothForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_divideVector(test, test, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, divideOperatorReturnsDivideByZeroMessageOnFailureStatusReturnsGeoVector3FZeroIsProvidedForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_divideVector(test, Nrt_GeoVector3F_zero(), &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_DIVIDE_BY_ZERO);
}

TEST(InteropGeoVector3Test, addOperatorAddsCorrectlyForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_addFloat(test, 1.0f, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(2.0f), result));
}

TEST(InteropGeoVector3Test, addOperatorReturnsNullptrFailureWhenGivenNullptrForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_addFloat(test, 1.0f, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector3Test, addOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_addFloat(test, 0.0f, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, addOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_zero();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_addFloat(test, NAN, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, addOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_addFloat(test, NAN, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, subtractOperatorSubtractsCorrectlyForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_subtractFloat(test, 1.0f, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_zero(), result));
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsNullptrFailureWhenGivenNullptrForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_subtractFloat(test, 1.0f, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_subtractFloat(test, 0.0f, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_zero();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_subtractFloat(test, NAN, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, subtractOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_subtractFloat(test, NAN, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, multiplyOperatorMultipliesCorrectlyForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_uniform(2.0f);
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_multiplyFloat(test, 2.0f, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(4.0f), result));
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsNullptrFailureWhenGivenNullptrForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_multiplyFloat(test, 1.0f, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_multiplyFloat(test, 0.0f, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_zero();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_multiplyFloat(test, NAN, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, multiplyOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_multiplyFloat(test, NAN, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, divideOperatorDividesCorrectlyForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_uniform(4.0f);
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideFloat(test, 2.0f, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(2.0f), result));
}

TEST(InteropGeoVector3Test, divideOperatorReturnsNullptrFailureWhenGivenNullptrForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_divideFloat(test, 1.0f, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector3Test, divideOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_divideFloat(test, 0.0f, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, divideOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_zero();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_divideFloat(test, NAN, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, divideOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector3F test { NAN, NAN };
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_divideFloat(test, NAN, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, divideOperatorReturnsDivideByZeroFailureWhenFloatZeroIsProvidedForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();
  NrtGeoVector3F result = Nrt_GeoVector3F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector3F_divideFloat(test, 0.0f, &result);

  ASSERT_EQ(nrtResult, NRT_FAILURE_DIVIDE_BY_ZERO);
}

TEST(InteropGeoVector3Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_addAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(2.0f), test));
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsNullptrFailureWhenGivenNullptrForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_addAssignVector(nullptr, test);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_addAssignVector(&test, Nrt_GeoVector3F_one());

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_addAssignVector(&test, Nrt_GeoVector3F_uniform(NAN));

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_addAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_subtractAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_zero(), test));
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsNullptrFailureWhenGivenNullptrForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_subtractAssignVector(nullptr, test);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_subtractAssignVector(&test, Nrt_GeoVector3F_one());

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_subtractAssignVector(&test, Nrt_GeoVector3F_uniform(NAN));

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_subtractAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_uniform(2.0f);

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_multiplyAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(4.0f), test));
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsNullptrFailureWhenGivenNullptrForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_multiplyAssignVector(nullptr, test);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_multiplyAssignVector(&test, Nrt_GeoVector3F_one());

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_multiplyAssignVector(&test, Nrt_GeoVector3F_uniform(NAN));

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_multiplyAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_uniform(2.0f);

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_one(), test));
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsNullptrFailureWhenGivenNullptrForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideAssignVector(nullptr, test);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideAssignVector(&test, Nrt_GeoVector3F_one());

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideAssignVector(&test, Nrt_GeoVector3F_uniform(NAN));

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForGeoVector3F) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsDivideByZeroFailureWhenGeoVector3FZeroIsProvidedForGeoVector3F) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideAssignVector(&test, Nrt_GeoVector3F_zero());

  ASSERT_EQ(nrtResult, NRT_FAILURE_DIVIDE_BY_ZERO);
}

TEST(InteropGeoVector3Test, addAssignOperatorAddsAndAssignsCorrectlyForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_addAssignFloat(&test, 1.0f);
  
  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(2.0f), test));
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsNullptrFailureWhenGivenNullptrForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_addAssignFloat(nullptr, 1.0f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_addAssignFloat(&test, 1.0f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_addAssignFloat(&test, NAN);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, addAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_addAssignFloat(&test, NAN);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_subtractAssignFloat(&test, 1.0f);
  
  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(0.0f), test));
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsFailureStatusWhenUnableToOperateForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_subtractAssignFloat(nullptr, 1.0f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_subtractAssignFloat(&test, 1.0f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_subtractAssignFloat(&test, NAN);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, subtractAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_subtractAssignFloat(&test, NAN);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_uniform(2.0f);

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_multiplyAssignFloat(&test, 1.0f);
  
  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(2.0f), test));
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsNullptrFailureWhenGivenNullptrForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_multiplyAssignFloat(nullptr, 1.0f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_multiplyAssignFloat(&test, 1.0f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_multiplyAssignFloat(&test, NAN);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_multiplyAssignFloat(&test, NAN);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, divideAssignOperatorDividesAndAssignsCorrectlyForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_uniform(2.0f);

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideAssignFloat(&test, 2.0f);
  
  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(1.0f), test));
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsNullptrFailureWhenGivenNullptrForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideAssignFloat(nullptr, 1.0f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideAssignFloat(&test, 1.0f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideAssignFloat(&test, NAN);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector3F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideAssignFloat(&test, NAN);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector3Test, divideAssignOperatorReturnsDivideByFailureWhenFloatZeroIsProvidedForFloat) {
  NrtGeoVector3F test = Nrt_GeoVector3F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_divideAssignFloat(&test, 0.0f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_DIVIDE_BY_ZERO);
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

  int32_t nrtResult = Nrt_GeoVector3F_rotateToAngleAroundPoint(&vec, 90.0f, zero);
  NrtGeoVector3F other{-1.0f, 0.0f};
  NrtGeoVector3F epsilon = Nrt_GeoVector3F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector3F_epsilonEquals(vec, other, epsilon));
}

TEST(InteropGeoVector3Test, rotateToAngleAroundPointReturnsNullptrFailureWhenGivenNullptr) {
  NrtGeoVector3F zero = Nrt_GeoVector3F_zero();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_rotateToAngleAroundPoint(nullptr, 90.0f, zero);
  NrtGeoVector3F other{-1.0f, 0.0f};
  NrtGeoVector3F epsilon = Nrt_GeoVector3F_uniform(1e-7f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector3Test, rotateToAngleAroundPointWhenGivenNaNValueInLhsReturnsNaNMessageOnFailureStatus) {
  NrtGeoVector3F vec{ NAN, NAN };
  NrtGeoVector3F zero = Nrt_GeoVector3F_zero();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_rotateToAngleAroundPoint(&vec, 90.0f, zero);
  NrtGeoVector3F other{-1.0f, 0.0f};
  NrtGeoVector3F epsilon = Nrt_GeoVector3F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector3Test, rotateToAngleAroundPointWhenGivenNaNValueInRhsReturnsNaNMessageOnFailureStatus) {
  NrtGeoVector3F vec{ 0.0f, 1.0f };
  NrtGeoVector3F zero { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_rotateToAngleAroundPoint(&vec, 90.0f, zero);
  NrtGeoVector3F other{-1.0f, 0.0f};
  NrtGeoVector3F epsilon = Nrt_GeoVector3F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector3Test, rotateToAngleAroundPointWhenGivenNaNValueForBothReturnsNaNMessageOnFailureStatus) {
  NrtGeoVector3F vec{ NAN, NAN };
  NrtGeoVector3F zero{ NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector3F_rotateToAngleAroundPoint(&vec, 90.0f, zero);
  NrtGeoVector3F other{-1.0f, 0.0f};
  NrtGeoVector3F epsilon = Nrt_GeoVector3F_uniform(1e-7f);

  ASSERT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), err); //TODO: fix this
}

TEST(InteropGeoVector3Test, isNaNReturnsTrueNaNVector) {
  NrtGeoVector3F nanVec {NAN, NAN};
  EXPECT_TRUE(Nrt_GeoVector3F_isNaN(nanVec));
}