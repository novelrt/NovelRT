// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include <NovelRT.Interop/Maths/NrtGeoMatrix4x4F.h>
#include <cmath>

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(InteropGeoMatrix4x4FTest, getDefaultIdentityReturnsCorrectIdentityMatrix) {
  NrtGeoMatrix4x4F mat4 = Nrt_GeoMatrix4x4F_getDefaultIdentity();
  EXPECT_EQ(Maths::GeoMatrix4x4F::getDefaultIdentity(), reinterpret_cast<Maths::GeoMatrix4x4F &>(mat4));
}

TEST(InteropGeoMatrix4x4FTest, isNaNReturnsTrueWhenGivenNaNMatrix) {
  EXPECT_TRUE(Nrt_GeoMatrix4x4F_isNaN(NrtGeoMatrix4x4F{Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN)}));
}

TEST(InteropGeoMatrix4x4FTest, isNaNReturnsFalseWhenGivenValidMatrix) {
  EXPECT_FALSE(Nrt_GeoMatrix4x4F_isNaN(Nrt_GeoMatrix4x4F_getDefaultIdentity()));
}

TEST(InteropGeoMatrix4x4FTest, equalsOperatorReturnsTrueWhenMatricesAreEqual) {
  EXPECT_TRUE(Nrt_GeoMatrix4x4F_equal(Nrt_GeoMatrix4x4F_getDefaultIdentity(), Nrt_GeoMatrix4x4F_getDefaultIdentity()));
}

TEST(InteropGeoMatrix4x4FTest, equalsOperatorReturnsFalseWhenMatricesAreDifferent) {
  EXPECT_FALSE(Nrt_GeoMatrix4x4F_equal(Nrt_GeoMatrix4x4F_getDefaultIdentity(), NrtGeoMatrix4x4F {Nrt_GeoVector4F_zero(), Nrt_GeoVector4F_zero(), Nrt_GeoVector4F_zero(), Nrt_GeoVector4F_zero(), }));
}

TEST(InteropGeoMatrix4x4FTest, notEqualsOperatorReturnsTrueWhenMatricesAreDifferent) {
  EXPECT_TRUE(Nrt_GeoMatrix4x4F_notEqual(Nrt_GeoMatrix4x4F_getDefaultIdentity(), NrtGeoMatrix4x4F {Nrt_GeoVector4F_zero(), Nrt_GeoVector4F_zero(), Nrt_GeoVector4F_zero(), Nrt_GeoVector4F_zero(), }));
}

TEST(InteropGeoMatrix4x4FTest, notEqualsOperatorReturnsFalseWhenMatricesAreEqual) {
  EXPECT_FALSE(Nrt_GeoMatrix4x4F_notEqual(Nrt_GeoMatrix4x4F_getDefaultIdentity(), Nrt_GeoMatrix4x4F_getDefaultIdentity()));
}

TEST(InteropGeoMatrix4x4FTest, addMatrixAddsMatricesTogetherCorrectly) {
  Maths::GeoMatrix4x4F expectedMatrix = Maths::GeoMatrix4x4F::getDefaultIdentity() + Maths::GeoMatrix4x4F::getDefaultIdentity();
  NrtGeoMatrix4x4F actualMatrix = Nrt_GeoMatrix4x4F_getDefaultIdentity();
  
  ASSERT_EQ(Nrt_GeoMatrix4x4F_addMatrix(Nrt_GeoMatrix4x4F_getDefaultIdentity(), Nrt_GeoMatrix4x4F_getDefaultIdentity(), &actualMatrix), NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoMatrix4x4F_equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix), actualMatrix));
}

TEST(InteropGeoMatrix4x4FTest, addMatrixReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorMessage = nullptr;

  ASSERT_EQ(Nrt_GeoMatrix4x4F_addMatrix(Nrt_GeoMatrix4x4F_getDefaultIdentity(), Nrt_GeoMatrix4x4F_getDefaultIdentity(), nullptr), NRT_FAILURE_NULLPTR_PROVIDED);
  ////EXPECT_EQ(Nrt_getErrMsgIsNullptr(), errorMessage);  //TODO: fix this//TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, addMatrixReturnsNaNFailureWhenGivenNanMatrixForLhs) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F outputThatDoesntGetUsed = Nrt_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(Nrt_GeoMatrix4x4F_addMatrix(NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) }, Nrt_GeoMatrix4x4F_getDefaultIdentity(), &outputThatDoesntGetUsed), NRT_FAILURE_NOT_A_NUMBER);
  ////EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this//TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, addMatrixReturnsNaNFailureWhenGivenNanMatrixForRhs) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F outputThatDoesntGetUsed = Nrt_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(Nrt_GeoMatrix4x4F_addMatrix(Nrt_GeoMatrix4x4F_getDefaultIdentity(), NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) }, &outputThatDoesntGetUsed), NRT_FAILURE_NOT_A_NUMBER);
  ////EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this//TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, addMatrixReturnsNaNFailureWhenGivenNanMatrixForBoth) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F outputThatDoesntGetUsed = Nrt_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(Nrt_GeoMatrix4x4F_addMatrix(NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) }, NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) }, &outputThatDoesntGetUsed), NRT_FAILURE_NOT_A_NUMBER);
  ////EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, subtractMatrixSubtractsMatricesTogetherCorrectly) {
  Maths::GeoMatrix4x4F expectedMatrix = Maths::GeoMatrix4x4F(Maths::GeoVector4F::zero(), Maths::GeoVector4F::zero(), Maths::GeoVector4F::zero(), Maths::GeoVector4F::zero());
  NrtGeoMatrix4x4F actualMatrix = Nrt_GeoMatrix4x4F_getDefaultIdentity();
  
  ASSERT_EQ(Nrt_GeoMatrix4x4F_subtractMatrix(Nrt_GeoMatrix4x4F_getDefaultIdentity(), Nrt_GeoMatrix4x4F_getDefaultIdentity(), &actualMatrix), NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoMatrix4x4F_equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix), actualMatrix));
}

TEST(InteropGeoMatrix4x4FTest, subtractMatrixReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorMessage = nullptr;

  ASSERT_EQ(Nrt_GeoMatrix4x4F_subtractMatrix(Nrt_GeoMatrix4x4F_getDefaultIdentity(), Nrt_GeoMatrix4x4F_getDefaultIdentity(), nullptr), NRT_FAILURE_NULLPTR_PROVIDED);
  ////EXPECT_EQ(Nrt_getErrMsgIsNullptr(), errorMessage);  //TODO: fix this//TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, subtractMatrixReturnsNaNFailureWhenGivenNanMatrixForLhs) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F outputThatDoesntGetUsed = Nrt_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(Nrt_GeoMatrix4x4F_subtractMatrix(NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) }, Nrt_GeoMatrix4x4F_getDefaultIdentity(), &outputThatDoesntGetUsed), NRT_FAILURE_NOT_A_NUMBER);
  ////EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this//TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, subtractMatrixReturnsNaNFailureWhenGivenNanMatrixForRhs) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F outputThatDoesntGetUsed = Nrt_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(Nrt_GeoMatrix4x4F_subtractMatrix(Nrt_GeoMatrix4x4F_getDefaultIdentity(), NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) }, &outputThatDoesntGetUsed), NRT_FAILURE_NOT_A_NUMBER);
  ////EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this//TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, subtractMatrixReturnsNaNFailureWhenGivenNanMatrixForBoth) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F outputThatDoesntGetUsed = Nrt_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(Nrt_GeoMatrix4x4F_subtractMatrix(NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) }, NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) }, &outputThatDoesntGetUsed), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, multiplyMatrixMultipliesMatricesTogetherCorrectly) {
  Maths::GeoMatrix4x4F inputMatrix = Maths::GeoMatrix4x4F(Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f));
  Maths::GeoMatrix4x4F expectedMatrix = Maths::GeoMatrix4x4F(Maths::GeoVector4F::uniform(16.0f), Maths::GeoVector4F::uniform(16.0f), Maths::GeoVector4F::uniform(16.0f), Maths::GeoVector4F::uniform(16.0f));
  NrtGeoMatrix4x4F resultMatrix = Nrt_GeoMatrix4x4F_getDefaultIdentity();
  
  ASSERT_EQ(Nrt_GeoMatrix4x4F_multiplyMatrix(*reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix), *reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix), &resultMatrix), NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoMatrix4x4F_equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix), resultMatrix));
}

TEST(InteropGeoMatrix4x4FTest, multiplyMatrixReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorMessage = nullptr;

  ASSERT_EQ(Nrt_GeoMatrix4x4F_multiplyMatrix(Nrt_GeoMatrix4x4F_getDefaultIdentity(), Nrt_GeoMatrix4x4F_getDefaultIdentity(), nullptr), NRT_FAILURE_NULLPTR_PROVIDED);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, multiplyMatrixReturnsNaNFailureWhenGivenNanMatrixForLhs) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F outputThatDoesntGetUsed = Nrt_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(Nrt_GeoMatrix4x4F_multiplyMatrix(NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) }, Nrt_GeoMatrix4x4F_getDefaultIdentity(), &outputThatDoesntGetUsed), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, multiplyMatrixReturnsNaNFailureWhenGivenNanMatrixForRhs) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F outputThatDoesntGetUsed = Nrt_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(Nrt_GeoMatrix4x4F_multiplyMatrix(Nrt_GeoMatrix4x4F_getDefaultIdentity(), NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) }, &outputThatDoesntGetUsed), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, multiplyMatrixReturnsNaNFailureWhenGivenNanMatrixForBoth) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F outputThatDoesntGetUsed = Nrt_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(Nrt_GeoMatrix4x4F_multiplyMatrix(NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) }, NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) }, &outputThatDoesntGetUsed), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, addAssignMatrixAddsMatricesTogetherCorrectly) {
  NrtGeoMatrix4x4F inputMatrix = Nrt_GeoMatrix4x4F_getDefaultIdentity();
  Maths::GeoMatrix4x4F expectedMatrix = Maths::GeoMatrix4x4F::getDefaultIdentity() + Maths::GeoMatrix4x4F::getDefaultIdentity();
  
  ASSERT_EQ(Nrt_GeoMatrix4x4F_addAssignMatrix(reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix), *reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix)), NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoMatrix4x4F_equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix), inputMatrix));
}

TEST(InteropGeoMatrix4x4FTest, addAssignMatrixReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorMessage = nullptr;

  ASSERT_EQ(Nrt_GeoMatrix4x4F_addAssignMatrix(nullptr, Nrt_GeoMatrix4x4F_getDefaultIdentity()), NRT_FAILURE_NULLPTR_PROVIDED);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, addAssignMatrixReturnsNaNFailureWhenGivenNanMatrixForLhs) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F nanInput = NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) };

  ASSERT_EQ(Nrt_GeoMatrix4x4F_addAssignMatrix(&nanInput, Nrt_GeoMatrix4x4F_getDefaultIdentity()), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, addAssignMatrixReturnsNaNFailureWhenGivenNanMatrixForRhs) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F dummyInput = Nrt_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(Nrt_GeoMatrix4x4F_addAssignMatrix(&dummyInput, NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) }), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, addAssignMatrixReturnsNaNFailureWhenGivenNanMatrixForBoth) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F nanInput = NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) };

  ASSERT_EQ(Nrt_GeoMatrix4x4F_addAssignMatrix(&nanInput, nanInput), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, subtractAssignMatrixSubtractsMatricesTogetherCorrectly) {
  NrtGeoMatrix4x4F inputMatrix = Nrt_GeoMatrix4x4F_getDefaultIdentity();
  NrtGeoMatrix4x4F expectedMatrix = NrtGeoMatrix4x4F{ Nrt_GeoVector4F_zero(), Nrt_GeoVector4F_zero(), Nrt_GeoVector4F_zero(), Nrt_GeoVector4F_zero() };
  
  ASSERT_EQ(Nrt_GeoMatrix4x4F_subtractAssignMatrix(&inputMatrix, inputMatrix), NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoMatrix4x4F_equal(expectedMatrix, inputMatrix));
}

TEST(InteropGeoMatrix4x4FTest, subtractAssignMatrixReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorMessage = nullptr;

  ASSERT_EQ(Nrt_GeoMatrix4x4F_subtractAssignMatrix(nullptr, Nrt_GeoMatrix4x4F_getDefaultIdentity()), NRT_FAILURE_NULLPTR_PROVIDED);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, subtractAssignMatrixReturnsNaNFailureWhenGivenNanMatrixForLhs) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F nanInput = NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) };

  ASSERT_EQ(Nrt_GeoMatrix4x4F_subtractAssignMatrix(&nanInput, Nrt_GeoMatrix4x4F_getDefaultIdentity()), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, subtractAssignMatrixReturnsNaNFailureWhenGivenNanMatrixForRhs) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F dummyInput = Nrt_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(Nrt_GeoMatrix4x4F_subtractAssignMatrix(&dummyInput, NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) }), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, subtractAssignMatrixReturnsNaNFailureWhenGivenNanMatrixForBoth) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F nanInput = NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) };

  ASSERT_EQ(Nrt_GeoMatrix4x4F_subtractAssignMatrix(&nanInput, nanInput), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, multiplyAssignMatrixMultipliesMatricesTogetherCorrectly) {
  Maths::GeoMatrix4x4F inputMatrix = Maths::GeoMatrix4x4F(Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f));
  Maths::GeoMatrix4x4F expectedMatrix = Maths::GeoMatrix4x4F(Maths::GeoVector4F::uniform(16.0f), Maths::GeoVector4F::uniform(16.0f), Maths::GeoVector4F::uniform(16.0f), Maths::GeoVector4F::uniform(16.0f));
  
  ASSERT_EQ(Nrt_GeoMatrix4x4F_multiplyAssignMatrix(reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix), *reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix)), NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoMatrix4x4F_equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix), *reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix)));
}

TEST(InteropGeoMatrix4x4FTest, multiplyAssignMatrixReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorMessage = nullptr;

  ASSERT_EQ(Nrt_GeoMatrix4x4F_multiplyAssignMatrix(nullptr, Nrt_GeoMatrix4x4F_getDefaultIdentity()), NRT_FAILURE_NULLPTR_PROVIDED);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, multiplyAssignMatrixReturnsNaNFailureWhenGivenNanMatrixForLhs) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F nanInput = NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) };

  ASSERT_EQ(Nrt_GeoMatrix4x4F_multiplyAssignMatrix(&nanInput, Nrt_GeoMatrix4x4F_getDefaultIdentity()), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, multiplyAssignMatrixReturnsNaNFailureWhenGivenNanMatrixForRhs) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F dummyInput = Nrt_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(Nrt_GeoMatrix4x4F_multiplyAssignMatrix(&dummyInput, NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) }), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, multiplyAssignMatrixReturnsNaNFailureWhenGivenNanMatrixForBoth) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F nanInput = NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) };

  ASSERT_EQ(Nrt_GeoMatrix4x4F_multiplyAssignMatrix(&nanInput, nanInput), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, addFloatAddsMatrixAndFloatTogetherCorrectly) {
  Maths::GeoMatrix4x4F expectedMatrix = Maths::GeoMatrix4x4F(Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f));
  NrtGeoMatrix4x4F actualMatrix = Nrt_GeoMatrix4x4F_getDefaultIdentity();
  
  ASSERT_EQ(Nrt_GeoMatrix4x4F_addFloat(NrtGeoMatrix4x4F { Nrt_GeoVector4F_one(), Nrt_GeoVector4F_one(), Nrt_GeoVector4F_one(), Nrt_GeoVector4F_one() }, 1.0f, &actualMatrix), NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoMatrix4x4F_equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix), actualMatrix));
}

TEST(InteropGeoMatrix4x4FTest, addFloatReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorMessage = nullptr;

  ASSERT_EQ(Nrt_GeoMatrix4x4F_addFloat(Nrt_GeoMatrix4x4F_getDefaultIdentity(), 1.0f, nullptr), NRT_FAILURE_NULLPTR_PROVIDED);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, addFloatReturnsNaNFailureWhenGivenNanMatrixForLhs) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F outputThatDoesntGetUsed = Nrt_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(Nrt_GeoMatrix4x4F_addFloat(NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) }, 1.0f, &outputThatDoesntGetUsed), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, addFloatReturnsNaNFailureWhenGivenNanFloatForRhs) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F outputThatDoesntGetUsed = Nrt_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(Nrt_GeoMatrix4x4F_addFloat(Nrt_GeoMatrix4x4F_getDefaultIdentity(), NAN, &outputThatDoesntGetUsed), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, addFloatReturnsNaNFailureWhenGivenNanValuesForBoth) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F outputThatDoesntGetUsed = Nrt_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(Nrt_GeoMatrix4x4F_addFloat(NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) }, NAN, &outputThatDoesntGetUsed), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, subtractFloatSubtractsMatricxAndFloatTogetherCorrectly) {
  Maths::GeoMatrix4x4F expectedMatrix = Maths::GeoMatrix4x4F(Maths::GeoVector4F::zero(), Maths::GeoVector4F::zero(), Maths::GeoVector4F::zero(), Maths::GeoVector4F::zero());
  NrtGeoMatrix4x4F actualMatrix = Nrt_GeoMatrix4x4F_getDefaultIdentity();
  
  ASSERT_EQ(Nrt_GeoMatrix4x4F_subtractFloat(NrtGeoMatrix4x4F { Nrt_GeoVector4F_one(), Nrt_GeoVector4F_one(), Nrt_GeoVector4F_one(), Nrt_GeoVector4F_one() }, 1.0f, &actualMatrix), NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoMatrix4x4F_equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix), actualMatrix));
}

TEST(InteropGeoMatrix4x4FTest, subtractFloatReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorMessage = nullptr;

  ASSERT_EQ(Nrt_GeoMatrix4x4F_subtractFloat(Nrt_GeoMatrix4x4F_getDefaultIdentity(), 1.0f, nullptr), NRT_FAILURE_NULLPTR_PROVIDED);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, subtractFloatReturnsNaNFailureWhenGivenNanMatrixForLhs) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F outputThatDoesntGetUsed = Nrt_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(Nrt_GeoMatrix4x4F_subtractFloat(NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) }, 1.0f, &outputThatDoesntGetUsed), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, subtractFloatReturnsNaNFailureWhenGivenNanFloatForRhs) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F outputThatDoesntGetUsed = Nrt_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(Nrt_GeoMatrix4x4F_subtractFloat(Nrt_GeoMatrix4x4F_getDefaultIdentity(), NAN, &outputThatDoesntGetUsed), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, subtractFloatReturnsNaNFailureWhenGivenNanValuesForBoth) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F outputThatDoesntGetUsed = Nrt_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(Nrt_GeoMatrix4x4F_subtractFloat(NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) }, NAN, &outputThatDoesntGetUsed), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, multiplyFloatMultipliesMatrixAndFloatTogetherCorrectly) {
  Maths::GeoMatrix4x4F inputMatrix = Maths::GeoMatrix4x4F(Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f));
  Maths::GeoMatrix4x4F expectedMatrix = Maths::GeoMatrix4x4F(Maths::GeoVector4F::uniform(4.0f), Maths::GeoVector4F::uniform(4.0f), Maths::GeoVector4F::uniform(4.0f), Maths::GeoVector4F::uniform(4.0f));
  NrtGeoMatrix4x4F resultMatrix = Nrt_GeoMatrix4x4F_getDefaultIdentity();
  
  ASSERT_EQ(Nrt_GeoMatrix4x4F_multiplyFloat(*reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix), 2.0f, &resultMatrix), NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoMatrix4x4F_equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix), resultMatrix));
}

TEST(InteropGeoMatrix4x4FTest, multiplyFloatReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorMessage = nullptr;

  ASSERT_EQ(Nrt_GeoMatrix4x4F_multiplyFloat(Nrt_GeoMatrix4x4F_getDefaultIdentity(), 1.0f, nullptr), NRT_FAILURE_NULLPTR_PROVIDED);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, multiplyFloatReturnsNaNFailureWhenGivenNanMatrixForLhs) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F outputThatDoesntGetUsed = Nrt_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(Nrt_GeoMatrix4x4F_multiplyFloat(NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) }, 1.0f, &outputThatDoesntGetUsed), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, multiplyFloatReturnsNaNFailureWhenGivenNanFloatForRhs) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F outputThatDoesntGetUsed = Nrt_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(Nrt_GeoMatrix4x4F_multiplyFloat(Nrt_GeoMatrix4x4F_getDefaultIdentity(), NAN, &outputThatDoesntGetUsed), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, multiplyFloatReturnsNaNFailureWhenGivenNanValuesForBoth) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F outputThatDoesntGetUsed = Nrt_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(Nrt_GeoMatrix4x4F_multiplyFloat(NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) }, NAN, &outputThatDoesntGetUsed), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, addAssignFloatAddsMatrixAndFloatTogetherCorrectly) {
  NrtGeoMatrix4x4F inputMatrix { Nrt_GeoVector4F_uniform(1.0f), Nrt_GeoVector4F_uniform(1.0f), Nrt_GeoVector4F_uniform(1.0f), Nrt_GeoVector4F_uniform(1.0f) };
  Maths::GeoMatrix4x4F expectedMatrix = *reinterpret_cast<Maths::GeoMatrix4x4F*>(&inputMatrix) + *reinterpret_cast<Maths::GeoMatrix4x4F*>(&inputMatrix);
  
  ASSERT_EQ(Nrt_GeoMatrix4x4F_addAssignFloat(reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix), 1.0f), NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoMatrix4x4F_equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix), inputMatrix));
}

TEST(InteropGeoMatrix4x4FTest, addAssignFloatReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorMessage = nullptr;

  ASSERT_EQ(Nrt_GeoMatrix4x4F_addAssignFloat(nullptr, 1.0f), NRT_FAILURE_NULLPTR_PROVIDED);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, addAssignFloatReturnsNaNFailureWhenGivenNanMatrixForLhs) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F nanInput = NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) };

  ASSERT_EQ(Nrt_GeoMatrix4x4F_addAssignFloat(&nanInput, 1.0f), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, addAssignFloatReturnsNaNFailureWhenGivenNanFloatForRhs) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F dummyInput = Nrt_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(Nrt_GeoMatrix4x4F_addAssignFloat(&dummyInput, NAN), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, addAssignFloatReturnsNaNFailureWhenGivenNanMatrixForBoth) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F nanInput = NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) };

  ASSERT_EQ(Nrt_GeoMatrix4x4F_addAssignFloat(&nanInput, NAN), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, subtractAssignFloatSubtractsMatrixAndFloatTogetherCorrectly) {
  NrtGeoMatrix4x4F inputMatrix {Nrt_GeoVector4F_one(), Nrt_GeoVector4F_one(), Nrt_GeoVector4F_one(), Nrt_GeoVector4F_one() };
  NrtGeoMatrix4x4F expectedMatrix = NrtGeoMatrix4x4F{ Nrt_GeoVector4F_zero(), Nrt_GeoVector4F_zero(), Nrt_GeoVector4F_zero(), Nrt_GeoVector4F_zero() };
  
  ASSERT_EQ(Nrt_GeoMatrix4x4F_subtractAssignFloat(&inputMatrix, 1.0f), NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoMatrix4x4F_equal(expectedMatrix, inputMatrix));
}

TEST(InteropGeoMatrix4x4FTest, subtractAssignFloatReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorMessage = nullptr;

  ASSERT_EQ(Nrt_GeoMatrix4x4F_subtractAssignFloat(nullptr, 1.0f), NRT_FAILURE_NULLPTR_PROVIDED);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, subtractAssignFloatReturnsNaNFailureWhenGivenNanMatrixForLhs) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F nanInput = NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) };

  ASSERT_EQ(Nrt_GeoMatrix4x4F_subtractAssignFloat(&nanInput, 1.0f), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, subtractAssignFloatReturnsNaNFailureWhenGivenNanFloatForRhs) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F dummyInput = Nrt_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(Nrt_GeoMatrix4x4F_subtractAssignFloat(&dummyInput, NAN), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, subtractAssignFloatReturnsNaNFailureWhenGivenNanValuesForBoth) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F nanInput = NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) };

  ASSERT_EQ(Nrt_GeoMatrix4x4F_subtractAssignFloat(&nanInput, NAN), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, multiplyAssignFloatMultipliesMatrixAndFloatTogetherCorrectly) {
  Maths::GeoMatrix4x4F inputMatrix = Maths::GeoMatrix4x4F(Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f), Maths::GeoVector4F::uniform(2.0f));
  Maths::GeoMatrix4x4F expectedMatrix = Maths::GeoMatrix4x4F(Maths::GeoVector4F::uniform(4.0f), Maths::GeoVector4F::uniform(4.0f), Maths::GeoVector4F::uniform(4.0f), Maths::GeoVector4F::uniform(4.0f));
  
  ASSERT_EQ(Nrt_GeoMatrix4x4F_multiplyAssignFloat(reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix), 2.0f), NRT_SUCCESS);
  EXPECT_TRUE(Nrt_GeoMatrix4x4F_equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix), *reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix)));
}

TEST(InteropGeoMatrix4x4FTest, multiplyAssignFloatReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorMessage = nullptr;

  ASSERT_EQ(Nrt_GeoMatrix4x4F_multiplyAssignFloat(nullptr, 1.0f), NRT_FAILURE_NULLPTR_PROVIDED);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, multiplyAssignFloatReturnsNaNFailureWhenGivenNanMatrixForLhs) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F nanInput = NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) };

  ASSERT_EQ(Nrt_GeoMatrix4x4F_multiplyAssignFloat(&nanInput, 1.0f), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, multiplyAssignFloatReturnsNaNFailureWhenGivenNanFloatForRhs) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F dummyInput = Nrt_GeoMatrix4x4F_getDefaultIdentity();

  ASSERT_EQ(Nrt_GeoMatrix4x4F_multiplyAssignFloat(&dummyInput, NAN), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}

TEST(InteropGeoMatrix4x4FTest, multiplyAssignFloatReturnsNaNFailureWhenGivenNanValuesForBoth) {
  const char* errorMessage = nullptr;
  NrtGeoMatrix4x4F nanInput = NrtGeoMatrix4x4F { Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN) };

  ASSERT_EQ(Nrt_GeoMatrix4x4F_multiplyAssignFloat(&nanInput, NAN), NRT_FAILURE_NOT_A_NUMBER);
  //EXPECT_EQ(Nrt_getErrMsgIsNaN(), errorMessage);  //TODO: fix this
}
