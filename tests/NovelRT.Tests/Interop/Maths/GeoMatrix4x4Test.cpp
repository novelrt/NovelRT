
// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include <NovelRT.Interop/Maths/NovelRTGeoMatrix4x4F.h>
#include <cmath>

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(InteropGeoMatrix4x4FTest, getDefaultIdentityReturnsCorrectIdentityMatrix) {
  NovelRTGeoMatrix4x4F mat4 = NovelRT_GeoMatrix4x4F_getDefaultIdentity();
  EXPECT_EQ(Maths::GeoMatrix4x4<float>::getDefaultIdentity(), reinterpret_cast<Maths::GeoMatrix4x4<float> &>(mat4));
}

TEST(InteropGeoMatrix4x4FTest, isNaNReturnsTrueWhenGivenNaNMatrix) {
  EXPECT_TRUE(NovelRT_GeoMatrix4x4F_isNaN(NovelRTGeoMatrix4x4F{NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN)}));
}

TEST(InteropGeoMatrix4x4FTest, isNaNReturnsFalseWhenGivenValidMatrix) {
  EXPECT_FALSE(NovelRT_GeoMatrix4x4F_isNaN(NovelRT_GeoMatrix4x4F_getDefaultIdentity()));
}

TEST(InteropGeoMatrix4x4FTest, equalsOperatorReturnsTrueWhenMatricesAreEqual) {
  EXPECT_TRUE(NovelRT_GeoMatrix4x4F_equal(NovelRT_GeoMatrix4x4F_getDefaultIdentity(), NovelRT_GeoMatrix4x4F_getDefaultIdentity()));
}

TEST(InteropGeoMatrix4x4FTest, equalsOperatorReturnsFalseWhenMatricesAreDifferent) {
  EXPECT_FALSE(NovelRT_GeoMatrix4x4F_equal(NovelRT_GeoMatrix4x4F_getDefaultIdentity(), NovelRTGeoMatrix4x4F {NovelRT_GeoVector4F_zero(), NovelRT_GeoVector4F_zero(), NovelRT_GeoVector4F_zero(), NovelRT_GeoVector4F_zero(), }));
}

TEST(InteropGeoMatrix4x4FTest, notEqualsOperatorReturnsTrueWhenMatricesAreDifferent) {
  EXPECT_TRUE(NovelRT_GeoMatrix4x4F_notEqual(NovelRT_GeoMatrix4x4F_getDefaultIdentity(), NovelRTGeoMatrix4x4F {NovelRT_GeoVector4F_zero(), NovelRT_GeoVector4F_zero(), NovelRT_GeoVector4F_zero(), NovelRT_GeoVector4F_zero(), }));
}

TEST(InteropGeoMatrix4x4FTest, notEqualsOperatorReturnsFalseWhenMatricesAreEqual) {
  EXPECT_FALSE(NovelRT_GeoMatrix4x4F_notEqual(NovelRT_GeoMatrix4x4F_getDefaultIdentity(), NovelRT_GeoMatrix4x4F_getDefaultIdentity()));
}

TEST(InteropGeoMatrix4x4FTest, addMatrixAddsMatricesTogetherCorrectly) {
  Maths::GeoMatrix4x4<float> expectedMatrix = Maths::GeoMatrix4x4<float>::getDefaultIdentity() + Maths::GeoMatrix4x4<float>::getDefaultIdentity();
  NovelRTGeoMatrix4x4F actualMatrix = NovelRT_GeoMatrix4x4F_getDefaultIdentity();
  
  ASSERT_EQ(NovelRT_GeoMatrix4x4F_addMatrix(NovelRT_GeoMatrix4x4F_getDefaultIdentity(), NovelRT_GeoMatrix4x4F_getDefaultIdentity(), &actualMatrix, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoMatrix4x4F_equal(reinterpret_cast<NovelRTGeoMatrix4x4F&>(expectedMatrix), actualMatrix));
}

TEST(InteropGeoMatrix4x4FTest, addMatrixReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorMessage = nullptr;

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_addMatrix(NovelRT_GeoMatrix4x4F_getDefaultIdentity(), NovelRT_GeoMatrix4x4F_getDefaultIdentity(), nullptr, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, addMatrixReturnsNaNFailureWhenGivenNanMatrixForLhs) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F outputThatDoesntGetUsed = NovelRT_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_addMatrix(NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) }, NovelRT_GeoMatrix4x4F_getDefaultIdentity(), &outputThatDoesntGetUsed, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, addMatrixReturnsNaNFailureWhenGivenNanMatrixForRhs) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F outputThatDoesntGetUsed = NovelRT_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_addMatrix(NovelRT_GeoMatrix4x4F_getDefaultIdentity(), NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) }, &outputThatDoesntGetUsed, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, addMatrixReturnsNaNFailureWhenGivenNanMatrixForBoth) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F outputThatDoesntGetUsed = NovelRT_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_addMatrix(NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) }, NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) }, &outputThatDoesntGetUsed, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, subtractMatrixSubtractsMatricesTogetherCorrectly) {
  Maths::GeoMatrix4x4<float> expectedMatrix = Maths::GeoMatrix4x4<float>(Maths::GeoVector4<float>::zero(), Maths::GeoVector4<float>::zero(), Maths::GeoVector4<float>::zero(), Maths::GeoVector4<float>::zero());
  NovelRTGeoMatrix4x4F actualMatrix = NovelRT_GeoMatrix4x4F_getDefaultIdentity();
  
  ASSERT_EQ(NovelRT_GeoMatrix4x4F_subtractMatrix(NovelRT_GeoMatrix4x4F_getDefaultIdentity(), NovelRT_GeoMatrix4x4F_getDefaultIdentity(), &actualMatrix, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoMatrix4x4F_equal(reinterpret_cast<NovelRTGeoMatrix4x4F&>(expectedMatrix), actualMatrix));
}

TEST(InteropGeoMatrix4x4FTest, subtractMatrixReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorMessage = nullptr;

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_subtractMatrix(NovelRT_GeoMatrix4x4F_getDefaultIdentity(), NovelRT_GeoMatrix4x4F_getDefaultIdentity(), nullptr, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, subtractMatrixReturnsNaNFailureWhenGivenNanMatrixForLhs) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F outputThatDoesntGetUsed = NovelRT_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_subtractMatrix(NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) }, NovelRT_GeoMatrix4x4F_getDefaultIdentity(), &outputThatDoesntGetUsed, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, subtractMatrixReturnsNaNFailureWhenGivenNanMatrixForRhs) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F outputThatDoesntGetUsed = NovelRT_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_subtractMatrix(NovelRT_GeoMatrix4x4F_getDefaultIdentity(), NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) }, &outputThatDoesntGetUsed, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, subtractMatrixReturnsNaNFailureWhenGivenNanMatrixForBoth) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F outputThatDoesntGetUsed = NovelRT_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_subtractMatrix(NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) }, NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) }, &outputThatDoesntGetUsed, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, multiplyMatrixMultipliesMatricesTogetherCorrectly) {
  Maths::GeoMatrix4x4<float> inputMatrix = Maths::GeoMatrix4x4<float>(Maths::GeoVector4<float>::uniform(2.0f), Maths::GeoVector4<float>::uniform(2.0f), Maths::GeoVector4<float>::uniform(2.0f), Maths::GeoVector4<float>::uniform(2.0f));
  Maths::GeoMatrix4x4<float> expectedMatrix = Maths::GeoMatrix4x4<float>(Maths::GeoVector4<float>::uniform(16.0f), Maths::GeoVector4<float>::uniform(16.0f), Maths::GeoVector4<float>::uniform(16.0f), Maths::GeoVector4<float>::uniform(16.0f));
  NovelRTGeoMatrix4x4F resultMatrix = NovelRT_GeoMatrix4x4F_getDefaultIdentity();
  
  ASSERT_EQ(NovelRT_GeoMatrix4x4F_multiplyMatrix(reinterpret_cast<NovelRTGeoMatrix4x4F&>(inputMatrix), reinterpret_cast<NovelRTGeoMatrix4x4F&>(inputMatrix), &resultMatrix, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoMatrix4x4F_equal(reinterpret_cast<NovelRTGeoMatrix4x4F&>(expectedMatrix), resultMatrix));
}

TEST(InteropGeoMatrix4x4FTest, multiplyMatrixReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorMessage = nullptr;

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_multiplyMatrix(NovelRT_GeoMatrix4x4F_getDefaultIdentity(), NovelRT_GeoMatrix4x4F_getDefaultIdentity(), nullptr, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, multiplyMatrixReturnsNaNFailureWhenGivenNanMatrixForLhs) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F outputThatDoesntGetUsed = NovelRT_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_multiplyMatrix(NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) }, NovelRT_GeoMatrix4x4F_getDefaultIdentity(), &outputThatDoesntGetUsed, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, multiplyMatrixReturnsNaNFailureWhenGivenNanMatrixForRhs) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F outputThatDoesntGetUsed = NovelRT_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_multiplyMatrix(NovelRT_GeoMatrix4x4F_getDefaultIdentity(), NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) }, &outputThatDoesntGetUsed, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, multiplyMatrixReturnsNaNFailureWhenGivenNanMatrixForBoth) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F outputThatDoesntGetUsed = NovelRT_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_multiplyMatrix(NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) }, NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) }, &outputThatDoesntGetUsed, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}