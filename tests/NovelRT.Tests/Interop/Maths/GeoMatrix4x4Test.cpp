
// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include <NovelRT.Interop/Maths/NovelRTGeoMatrix4x4F.h>
#include <cmath>

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(InteropGeoMatrix4x4FTest, getDefaultIdentityReturnsCorrectIdentityMatrix) {
  NovelRTGeoMatrix4x4F mat4 = NovelRT_GeoMatrix4x4F_getDefaultIdentity();
  EXPECT_EQ(Maths::GeoMatrix4x4F::getDefaultIdentity(), reinterpret_cast<Maths::GeoMatrix4x4F &>(mat4));
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
  Maths::GeoMatrix4x4F expectedMatrix = Maths::GeoMatrix4x4F::getDefaultIdentity() + Maths::GeoMatrix4x4F::getDefaultIdentity();
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
  Maths::GeoMatrix4x4F expectedMatrix = Maths::GeoMatrix4x4F(Maths::GeoVector4F::zero(), Maths::GeoVector4F::zero(), Maths::GeoVector4F::zero(), Maths::GeoVector4F::zero());
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
  Maths::GeoMatrix4x4F inputMatrix = Maths::GeoMatrix4x4F(Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f));
  Maths::GeoMatrix4x4F expectedMatrix = Maths::GeoMatrix4x4F(Maths::GeoVector4F::uniform(16.0f), Maths::GeoVector4F::uniform(16.0f), Maths::GeoVector4F::uniform(16.0f), Maths::GeoVector4F::uniform(16.0f));
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

TEST(InteropGeoMatrix4x4FTest, addAssignMatrixAddsMatricesTogetherCorrectly) {
  NovelRTGeoMatrix4x4F inputMatrix = NovelRT_GeoMatrix4x4F_getDefaultIdentity();
  Maths::GeoMatrix4x4F expectedMatrix = Maths::GeoMatrix4x4F::getDefaultIdentity() + Maths::GeoMatrix4x4F::getDefaultIdentity();
  
  ASSERT_EQ(NovelRT_GeoMatrix4x4F_addAssignMatrix(&reinterpret_cast<NovelRTGeoMatrix4x4F&>(inputMatrix), reinterpret_cast<NovelRTGeoMatrix4x4F&>(inputMatrix), nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoMatrix4x4F_equal(reinterpret_cast<NovelRTGeoMatrix4x4F&>(expectedMatrix), inputMatrix));
}

TEST(InteropGeoMatrix4x4FTest, addAssignMatrixReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorMessage = nullptr;

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_addAssignMatrix(nullptr, NovelRT_GeoMatrix4x4F_getDefaultIdentity(), &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, addAssignMatrixReturnsNaNFailureWhenGivenNanMatrixForLhs) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F nanInput = NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) };

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_addAssignMatrix(&nanInput, NovelRT_GeoMatrix4x4F_getDefaultIdentity(), &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, addAssignMatrixReturnsNaNFailureWhenGivenNanMatrixForRhs) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F dummyInput = NovelRT_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_addAssignMatrix(&dummyInput, NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) }, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, addAssignMatrixReturnsNaNFailureWhenGivenNanMatrixForBoth) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F nanInput = NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) };

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_addAssignMatrix(&nanInput, nanInput, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, subtractAssignMatrixSubtractsMatricesTogetherCorrectly) {
  NovelRTGeoMatrix4x4F inputMatrix = NovelRT_GeoMatrix4x4F_getDefaultIdentity();
  NovelRTGeoMatrix4x4F expectedMatrix = NovelRTGeoMatrix4x4F{ NovelRT_GeoVector4F_zero(), NovelRT_GeoVector4F_zero(), NovelRT_GeoVector4F_zero(), NovelRT_GeoVector4F_zero() };
  
  ASSERT_EQ(NovelRT_GeoMatrix4x4F_subtractAssignMatrix(&inputMatrix, inputMatrix, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoMatrix4x4F_equal(expectedMatrix, inputMatrix));
}

TEST(InteropGeoMatrix4x4FTest, subtractAssignMatrixReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorMessage = nullptr;

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_subtractAssignMatrix(nullptr, NovelRT_GeoMatrix4x4F_getDefaultIdentity(), &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, subtractAssignMatrixReturnsNaNFailureWhenGivenNanMatrixForLhs) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F nanInput = NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) };

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_subtractAssignMatrix(&nanInput, NovelRT_GeoMatrix4x4F_getDefaultIdentity(), &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, subtractAssignMatrixReturnsNaNFailureWhenGivenNanMatrixForRhs) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F dummyInput = NovelRT_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_subtractAssignMatrix(&dummyInput, NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) }, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, subtractAssignMatrixReturnsNaNFailureWhenGivenNanMatrixForBoth) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F nanInput = NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) };

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_subtractAssignMatrix(&nanInput, nanInput, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, multiplyAssignMatrixMultipliesMatricesTogetherCorrectly) {
  Maths::GeoMatrix4x4F inputMatrix = Maths::GeoMatrix4x4F(Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f));
  Maths::GeoMatrix4x4F expectedMatrix = Maths::GeoMatrix4x4F(Maths::GeoVector4F::uniform(16.0f), Maths::GeoVector4F::uniform(16.0f), Maths::GeoVector4F::uniform(16.0f), Maths::GeoVector4F::uniform(16.0f));
  
  ASSERT_EQ(NovelRT_GeoMatrix4x4F_multiplyAssignMatrix(&reinterpret_cast<NovelRTGeoMatrix4x4F&>(inputMatrix), reinterpret_cast<NovelRTGeoMatrix4x4F&>(inputMatrix), nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoMatrix4x4F_equal(reinterpret_cast<NovelRTGeoMatrix4x4F&>(expectedMatrix), reinterpret_cast<NovelRTGeoMatrix4x4F&>(inputMatrix)));
}

TEST(InteropGeoMatrix4x4FTest, multiplyAssignMatrixReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorMessage = nullptr;

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_multiplyAssignMatrix(nullptr, NovelRT_GeoMatrix4x4F_getDefaultIdentity(), &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, multiplyAssignMatrixReturnsNaNFailureWhenGivenNanMatrixForLhs) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F nanInput = NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) };

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_multiplyAssignMatrix(&nanInput, NovelRT_GeoMatrix4x4F_getDefaultIdentity(), &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, multiplyAssignMatrixReturnsNaNFailureWhenGivenNanMatrixForRhs) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F dummyInput = NovelRT_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_multiplyAssignMatrix(&dummyInput, NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) }, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, multiplyAssignMatrixReturnsNaNFailureWhenGivenNanMatrixForBoth) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F nanInput = NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) };

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_multiplyAssignMatrix(&nanInput, nanInput, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, addFloatAddsMatrixAndFloatTogetherCorrectly) {
  Maths::GeoMatrix4x4F expectedMatrix = Maths::GeoMatrix4x4F(Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f));
  NovelRTGeoMatrix4x4F actualMatrix = NovelRT_GeoMatrix4x4F_getDefaultIdentity();
  
  ASSERT_EQ(NovelRT_GeoMatrix4x4F_addFloat(NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_one(), NovelRT_GeoVector4F_one(), NovelRT_GeoVector4F_one(), NovelRT_GeoVector4F_one() }, 1.0f, &actualMatrix, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoMatrix4x4F_equal(reinterpret_cast<NovelRTGeoMatrix4x4F&>(expectedMatrix), actualMatrix));
}

TEST(InteropGeoMatrix4x4FTest, addFloatReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorMessage = nullptr;

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_addFloat(NovelRT_GeoMatrix4x4F_getDefaultIdentity(), 1.0f, nullptr, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, addFloatReturnsNaNFailureWhenGivenNanMatrixForLhs) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F outputThatDoesntGetUsed = NovelRT_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_addFloat(NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) }, 1.0f, &outputThatDoesntGetUsed, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, addFloatReturnsNaNFailureWhenGivenNanFloatForRhs) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F outputThatDoesntGetUsed = NovelRT_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_addFloat(NovelRT_GeoMatrix4x4F_getDefaultIdentity(), NAN, &outputThatDoesntGetUsed, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, addFloatReturnsNaNFailureWhenGivenNanValuesForBoth) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F outputThatDoesntGetUsed = NovelRT_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_addFloat(NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) }, NAN, &outputThatDoesntGetUsed, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, subtractFloatSubtractsMatricxAndFloatTogetherCorrectly) {
  Maths::GeoMatrix4x4F expectedMatrix = Maths::GeoMatrix4x4F(Maths::GeoVector4F::zero(), Maths::GeoVector4F::zero(), Maths::GeoVector4F::zero(), Maths::GeoVector4F::zero());
  NovelRTGeoMatrix4x4F actualMatrix = NovelRT_GeoMatrix4x4F_getDefaultIdentity();
  
  ASSERT_EQ(NovelRT_GeoMatrix4x4F_subtractFloat(NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_one(), NovelRT_GeoVector4F_one(), NovelRT_GeoVector4F_one(), NovelRT_GeoVector4F_one() }, 1.0f, &actualMatrix, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoMatrix4x4F_equal(reinterpret_cast<NovelRTGeoMatrix4x4F&>(expectedMatrix), actualMatrix));
}

TEST(InteropGeoMatrix4x4FTest, subtractFloatReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorMessage = nullptr;

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_subtractFloat(NovelRT_GeoMatrix4x4F_getDefaultIdentity(), 1.0f, nullptr, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, subtractFloatReturnsNaNFailureWhenGivenNanMatrixForLhs) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F outputThatDoesntGetUsed = NovelRT_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_subtractFloat(NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) }, 1.0f, &outputThatDoesntGetUsed, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, subtractFloatReturnsNaNFailureWhenGivenNanFloatForRhs) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F outputThatDoesntGetUsed = NovelRT_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_subtractFloat(NovelRT_GeoMatrix4x4F_getDefaultIdentity(), NAN, &outputThatDoesntGetUsed, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, subtractFloatReturnsNaNFailureWhenGivenNanValuesForBoth) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F outputThatDoesntGetUsed = NovelRT_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_subtractFloat(NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) }, NAN, &outputThatDoesntGetUsed, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, multiplyFloatMultipliesMatrixAndFloatTogetherCorrectly) {
  Maths::GeoMatrix4x4F inputMatrix = Maths::GeoMatrix4x4F(Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f));
  Maths::GeoMatrix4x4F expectedMatrix = Maths::GeoMatrix4x4F(Maths::GeoVector4F::uniform(4.0f), Maths::GeoVector4F::uniform(4.0f), Maths::GeoVector4F::uniform(4.0f), Maths::GeoVector4F::uniform(4.0f));
  NovelRTGeoMatrix4x4F resultMatrix = NovelRT_GeoMatrix4x4F_getDefaultIdentity();
  
  ASSERT_EQ(NovelRT_GeoMatrix4x4F_multiplyFloat(reinterpret_cast<NovelRTGeoMatrix4x4F&>(inputMatrix), 2.0f, &resultMatrix, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoMatrix4x4F_equal(reinterpret_cast<NovelRTGeoMatrix4x4F&>(expectedMatrix), resultMatrix));
}

TEST(InteropGeoMatrix4x4FTest, multiplyFloatReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorMessage = nullptr;

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_multiplyFloat(NovelRT_GeoMatrix4x4F_getDefaultIdentity(), 1.0f, nullptr, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, multiplyFloatReturnsNaNFailureWhenGivenNanMatrixForLhs) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F outputThatDoesntGetUsed = NovelRT_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_multiplyFloat(NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) }, 1.0f, &outputThatDoesntGetUsed, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, multiplyFloatReturnsNaNFailureWhenGivenNanFloatForRhs) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F outputThatDoesntGetUsed = NovelRT_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_multiplyFloat(NovelRT_GeoMatrix4x4F_getDefaultIdentity(), NAN, &outputThatDoesntGetUsed, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, multiplyFloatReturnsNaNFailureWhenGivenNanValuesForBoth) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F outputThatDoesntGetUsed = NovelRT_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_multiplyFloat(NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) }, NAN, &outputThatDoesntGetUsed, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, addAssignFloatAddsMatrixAndFloatTogetherCorrectly) {
  NovelRTGeoMatrix4x4F inputMatrix { NovelRT_GeoVector4F_uniform(1.0f), NovelRT_GeoVector4F_uniform(1.0f), NovelRT_GeoVector4F_uniform(1.0f), NovelRT_GeoVector4F_uniform(1.0f) };
  Maths::GeoMatrix4x4F expectedMatrix = reinterpret_cast<Maths::GeoMatrix4x4F&>(inputMatrix) + reinterpret_cast<Maths::GeoMatrix4x4F&>(inputMatrix);
  
  ASSERT_EQ(NovelRT_GeoMatrix4x4F_addAssignFloat(&reinterpret_cast<NovelRTGeoMatrix4x4F&>(inputMatrix), 1.0f, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoMatrix4x4F_equal(reinterpret_cast<NovelRTGeoMatrix4x4F&>(expectedMatrix), inputMatrix));
}

TEST(InteropGeoMatrix4x4FTest, addAssignFloatReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorMessage = nullptr;

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_addAssignFloat(nullptr, 1.0f, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, addAssignFloatReturnsNaNFailureWhenGivenNanMatrixForLhs) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F nanInput = NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) };

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_addAssignFloat(&nanInput, 1.0f, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, addAssignFloatReturnsNaNFailureWhenGivenNanFloatForRhs) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F dummyInput = NovelRT_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_addAssignFloat(&dummyInput, NAN, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, addAssignFloatReturnsNaNFailureWhenGivenNanMatrixForBoth) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F nanInput = NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) };

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_addAssignFloat(&nanInput, NAN, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, subtractAssignFloatSubtractsMatrixAndFloatTogetherCorrectly) {
  NovelRTGeoMatrix4x4F inputMatrix {NovelRT_GeoVector4F_one(), NovelRT_GeoVector4F_one(), NovelRT_GeoVector4F_one(), NovelRT_GeoVector4F_one() };
  NovelRTGeoMatrix4x4F expectedMatrix = NovelRTGeoMatrix4x4F{ NovelRT_GeoVector4F_zero(), NovelRT_GeoVector4F_zero(), NovelRT_GeoVector4F_zero(), NovelRT_GeoVector4F_zero() };
  
  ASSERT_EQ(NovelRT_GeoMatrix4x4F_subtractAssignFloat(&inputMatrix, 1.0f, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoMatrix4x4F_equal(expectedMatrix, inputMatrix));
}

TEST(InteropGeoMatrix4x4FTest, subtractAssignFloatReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorMessage = nullptr;

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_subtractAssignFloat(nullptr, 1.0f, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, subtractAssignFloatReturnsNaNFailureWhenGivenNanMatrixForLhs) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F nanInput = NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) };

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_subtractAssignFloat(&nanInput, 1.0f, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, subtractAssignFloatReturnsNaNFailureWhenGivenNanFloatForRhs) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F dummyInput = NovelRT_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_subtractAssignFloat(&dummyInput, NAN, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, subtractAssignFloatReturnsNaNFailureWhenGivenNanValuesForBoth) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F nanInput = NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) };

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_subtractAssignFloat(&nanInput, NAN, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, multiplyAssignFloatMultipliesMatrixAndFloatTogetherCorrectly) {
  Maths::GeoMatrix4x4F inputMatrix = Maths::GeoMatrix4x4F(Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f));
  Maths::GeoMatrix4x4F expectedMatrix = Maths::GeoMatrix4x4F(Maths::GeoVector4F::uniform(4.0f), Maths::GeoVector4F::uniform(4.0f), Maths::GeoVector4F::uniform(4.0f), Maths::GeoVector4F::uniform(4.0f));
  
  ASSERT_EQ(NovelRT_GeoMatrix4x4F_multiplyAssignFloat(&reinterpret_cast<NovelRTGeoMatrix4x4F&>(inputMatrix), 2.0f, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(NovelRT_GeoMatrix4x4F_equal(reinterpret_cast<NovelRTGeoMatrix4x4F&>(expectedMatrix), reinterpret_cast<NovelRTGeoMatrix4x4F&>(inputMatrix)));
}

TEST(InteropGeoMatrix4x4FTest, multiplyAssignFloatReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorMessage = nullptr;

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_multiplyAssignFloat(nullptr, 1.0f, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, multiplyAssignFloatReturnsNaNFailureWhenGivenNanMatrixForLhs) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F nanInput = NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) };

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_multiplyAssignFloat(&nanInput, 1.0f, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, multiplyAssignFloatReturnsNaNFailureWhenGivenNanFloatForRhs) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F dummyInput = NovelRT_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_multiplyAssignFloat(&dummyInput, NAN, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}

TEST(InteropGeoMatrix4x4FTest, multiplyAssignFloatReturnsNaNFailureWhenGivenNanValuesForBoth) {
  const char* errorMessage = nullptr;
  NovelRTGeoMatrix4x4F nanInput = NovelRTGeoMatrix4x4F { NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN) };

  ASSERT_EQ(NovelRT_GeoMatrix4x4F_multiplyAssignFloat(&nanInput, NAN, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNaN(), errorMessage); 
}
