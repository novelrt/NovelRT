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

TEST(InteropGeoVector4Test, addOperatorReturnsNullptrFailureWhenGivenNullptrForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_addVector(test, test, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector4Test, addOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_addVector(test, Nrt_GeoVector4F_zero(), &result);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, addOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_addVector(Nrt_GeoVector4F_zero(), test, &result);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, addOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_addVector(test, test, &result);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, subtractOperatorSubtractsCorrectlyForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_subtractVector(test, test, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);  
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_zero(), result));
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsNullptrFailureWhenGivenNullptrForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_subtractVector(test, test, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_subtractVector(test, Nrt_GeoVector4F_zero(), &result);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_subtractVector(Nrt_GeoVector4F_zero(), test, &result);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_subtractVector(test, test, &result);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, multiplyOperatorMultipliesCorrectlyForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_uniform(2.0f);
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_multiplyVector(test, test, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);  
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(4.0f), result));
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsNullptrFailureWhenGivenNullptrForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_multiplyVector(test, test, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_multiplyVector(test, Nrt_GeoVector4F_zero(), &result);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_multiplyVector(Nrt_GeoVector4F_zero(), test, &result);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_subtractVector(test, test, &result);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, divideOperatorDividesCorrectlyForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_uniform(4.0f);
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err = nullptr;
  int32_t nrtResult = Nrt_GeoVector4F_divideVector(test, test, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);  
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_one(), result));
}

TEST(InteropGeoVector4Test, divideOperatorReturnsNullptrFailureWhenGivenNullptrForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_divideVector(test, test, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector4Test, divideOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_divideVector(test, Nrt_GeoVector4F_zero(), &result);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, divideOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_divideVector(Nrt_GeoVector4F_zero(), test, &result);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, divideOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_divideVector(test, test, &result);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, divideOperatorReturnsDivideByZeroFailureWhenGeoVector4FZeroIsProvidedForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_divideVector(test, Nrt_GeoVector4F_zero(), &result);

  EXPECT_EQ(nrtResult, NRT_FAILURE_DIVIDE_BY_ZERO);
}

TEST(InteropGeoVector4Test, addOperatorAddsCorrectlyForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_addFloat(test, 1.0f, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(2.0f), result));
}

TEST(InteropGeoVector4Test, addOperatorReturnsNullptrFailureWhenGivenNullptrForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_addFloat(test, 1.0f, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector4Test, addOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_addFloat(test, 0.0f, &result);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, addOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_zero();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_addFloat(test, NAN, &result);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, addOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_addFloat(test, NAN, &result);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, subtractOperatorSubtractsCorrectlyForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_subtractFloat(test, 1.0f, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_zero(), result));
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsNullptrFailureWhenGivenNullptrForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_subtractFloat(test, 1.0f, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_subtractFloat(test, 0.0f, &result);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_zero();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_subtractFloat(test, NAN, &result);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, subtractOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_subtractFloat(test, NAN, &result);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, multiplyOperatorMultipliesCorrectlyForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_uniform(2.0f);
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_multiplyFloat(test, 2.0f, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(4.0f), result));
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsNullptrFailureWhenGivenNullptrForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_multiplyFloat(test, 1.0f, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_multiplyFloat(test, 0.0f, &result);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_zero();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_multiplyFloat(test, NAN, &result);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, multiplyOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_multiplyFloat(test, NAN, &result);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, divideOperatorDividesCorrectlyForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_uniform(4.0f);
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideFloat(test, 2.0f, &result);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(2.0f), result));
}

TEST(InteropGeoVector4Test, divideOperatorReturnsNullptrFailureWhenGivenNullptrForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_divideFloat(test, 1.0f, nullptr);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector4Test, divideOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_divideFloat(test, 0.0f, &result);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, divideOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_zero();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_divideFloat(test, NAN, &result);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, divideOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector4F test { NAN, NAN };
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_divideFloat(test, NAN, &result);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, divideOperatorReturnsDivideByZeroFailureWhenFloatZeroIsProvidedForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();
  NrtGeoVector4F result = Nrt_GeoVector4F_zero();
  
  const char* err;
  int32_t nrtResult = Nrt_GeoVector4F_divideFloat(test, 0.0f, &result);

  EXPECT_EQ(nrtResult, NRT_FAILURE_DIVIDE_BY_ZERO);
}

TEST(InteropGeoVector4Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_addAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(2.0f), test));
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsNullptrFailureWhenGivenNullptrForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_addAssignVector(nullptr, test);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_addAssignVector(&test, Nrt_GeoVector4F_one());

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_addAssignVector(&test, Nrt_GeoVector4F_uniform(NAN));

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_addAssignVector(&test, test);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_subtractAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_zero(), test));
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsNullptrFailureWhenGivenNullptrForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_subtractAssignVector(nullptr, test);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_subtractAssignVector(&test, Nrt_GeoVector4F_one());

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_subtractAssignVector(&test, Nrt_GeoVector4F_uniform(NAN));

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_subtractAssignVector(&test, test);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_uniform(2.0f);

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_multiplyAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(4.0f), test));
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsNullptrFailureWhenGivenNullptrForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_multiplyAssignVector(nullptr, test);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_multiplyAssignVector(&test, Nrt_GeoVector4F_one());

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_multiplyAssignVector(&test, Nrt_GeoVector4F_uniform(NAN));

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_multiplyAssignVector(&test, test);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_uniform(2.0f);

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideAssignVector(&test, test);

  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_one(), test));
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsNullptrFailureWhenGivenNullptrForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideAssignVector(nullptr, test);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideAssignVector(&test, Nrt_GeoVector4F_one());

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideAssignVector(&test, Nrt_GeoVector4F_uniform(NAN));

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForGeoVector4F) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideAssignVector(&test, test);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsDivideByZeroFailureWhenGeoVector4FZeroIsProvidedForGeoVector4F) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideAssignVector(&test, Nrt_GeoVector4F_zero());

  EXPECT_EQ(nrtResult, NRT_FAILURE_DIVIDE_BY_ZERO);
}

TEST(InteropGeoVector4Test, addAssignOperatorAddsAndAssignsCorrectlyForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_addAssignFloat(&test, 1.0f);
  
  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(2.0f), test));
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsNullptrFailureWhenGivenNullptrForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_addAssignFloat(nullptr, 1.0f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_addAssignFloat(&test, 1.0f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_addAssignFloat(&test, NAN);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, addAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_addAssignFloat(&test, NAN);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_subtractAssignFloat(&test, 1.0f);
  
  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(0.0f), test));
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsNullptrFailureWhenGivenNullptrForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_subtractAssignFloat(nullptr, 1.0f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_subtractAssignFloat(&test, 1.0f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_subtractAssignFloat(&test, NAN);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, subtractAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_subtractAssignFloat(&test, NAN);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_uniform(2.0f);

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_multiplyAssignFloat(&test, 1.0f);
  
  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(2.0f), test));
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsNullptrFailureWhenGivenNullptrForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_multiplyAssignFloat(nullptr, 1.0f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_multiplyAssignFloat(&test, 1.0f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_multiplyAssignFloat(&test, NAN);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_multiplyAssignFloat(&test, NAN);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, divideAssignOperatorDividesAndAssignsCorrectlyForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_uniform(2.0f);

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideAssignFloat(&test, 2.0f);
  
  ASSERT_EQ(nrtResult, NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(1.0f), test));
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsNullptrFailureWhenGivenNullptrForFloat) {
  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideAssignFloat(nullptr, 1.0f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForLhsForFloat) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideAssignFloat(&test, 1.0f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForRhsForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideAssignFloat(&test, NAN);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsNaNFailureWhenNaNIsProvidedForBothForFloat) {
  NrtGeoVector4F test { NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideAssignFloat(&test, NAN);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, divideAssignOperatorReturnsDivideByZeroFailureWhenFloatZeroIsProvidedForFloat) {
  NrtGeoVector4F test = Nrt_GeoVector4F_one();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_divideAssignFloat(&test, 0.0f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_DIVIDE_BY_ZERO);
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

TEST(InteropGeoVector4Test, rotateToAngleAroundPointReturnsNullptrFailureWhenGivenNullptr) {
  NrtGeoVector3F zero = Nrt_GeoVector3F_zero();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_rotateToAngleAroundPoint(nullptr, 90.0f, zero);
  NrtGeoVector4F other{-1.0f, 0.0f};
  NrtGeoVector4F epsilon = Nrt_GeoVector4F_uniform(1e-7f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NULLPTR_PROVIDED);
}

TEST(InteropGeoVector4Test, rotateToAngleAroundPointWhenGivenNaNValueInLhsReturnsNaNFailure) {
  NrtGeoVector4F vec{ NAN, NAN, NAN, NAN };
  NrtGeoVector3F zero = Nrt_GeoVector3F_zero();

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_rotateToAngleAroundPoint(&vec, 90.0f, zero);
  NrtGeoVector4F other{-1.0f, 0.0f};
  NrtGeoVector4F epsilon = Nrt_GeoVector4F_uniform(1e-7f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, rotateToAngleAroundPointWhenGivenNaNValueInRhsReturnsNaNFailure) {
  NrtGeoVector4F vec{ 0.0f, 1.0f, 0.0f, 0.0f };
  NrtGeoVector3F zero { NAN, NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_rotateToAngleAroundPoint(&vec, 90.0f, zero);
  NrtGeoVector4F other{-1.0f, 0.0f};
  NrtGeoVector4F epsilon = Nrt_GeoVector4F_uniform(1e-7f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, rotateToAngleAroundPointWhenGivenNaNValueForBothReturnsNaNFailure) {
  NrtGeoVector4F vec{ NAN, NAN, NAN, NAN };
  NrtGeoVector3F zero{ NAN, NAN, NAN };

  const char* err = nullptr;

  int32_t nrtResult = Nrt_GeoVector4F_rotateToAngleAroundPoint(&vec, 90.0f, zero);
  NrtGeoVector4F other{-1.0f, 0.0f};
  NrtGeoVector4F epsilon = Nrt_GeoVector4F_uniform(1e-7f);

  EXPECT_EQ(nrtResult, NRT_FAILURE_NOT_A_NUMBER);
}

TEST(InteropGeoVector4Test, isNaNReturnsTrueNaNVector) {
  NrtGeoVector4F nanVec {NAN, NAN};
  EXPECT_TRUE(Nrt_GeoVector4F_isNaN(nanVec));
}

