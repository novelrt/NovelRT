// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

class GeoMatrix4x4Test : public testing::Test {
protected:
  GeoMatrix4x4<float> _dummyMatrix;

  void SetUp() override {
    _dummyMatrix = GeoMatrix4x4<float>(GeoVector4<float>(1.0f, 0.0f, 0.0f, 0.0f),
      GeoVector4<float>(0.0f, 1.0f, 0.0f, 0.0f),
      GeoVector4<float>(0.0f, 0.0f, 1.0f, 0.0f),
      GeoVector4<float>(0.0f, 0.0f, 0.0f, 1.0f));
  }
};

TEST_F(GeoMatrix4x4Test, equalityOperatorEvaluatesCorrectly) {
  auto testMatOne = GeoMatrix4x4<float>(GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one());

  auto testMatTwo = GeoMatrix4x4<float>(GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one());

  ASSERT_EQ(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, inequalityOperatorEvaluatesCorrectly) {
  auto testMatOne = GeoMatrix4x4<float>(GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one());

  auto testMatTwo = GeoMatrix4x4<float>(GeoVector4<float>::zero(), GeoVector4<float>::zero(), GeoVector4<float>::zero(), GeoVector4<float>::zero());

  ASSERT_NE(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, getDefaultIdentityReturnsIdentityMatrix) {
  ASSERT_EQ(GeoMatrix4x4<float>::getDefaultIdentity(), _dummyMatrix);
}

TEST_F(GeoMatrix4x4Test, getXReturnsExpectedGeoVector4) {
  ASSERT_EQ(GeoVector4<float>(1.0f, 0.0f, 0.0f, 0.0f), _dummyMatrix.getX());
}

TEST_F(GeoMatrix4x4Test, setXSetsExpectedGeoVector4) {
  _dummyMatrix.setX(GeoVector4<float>::one());
  ASSERT_EQ(GeoVector4<float>::one(), _dummyMatrix.getX());
}

TEST_F(GeoMatrix4x4Test, getYReturnsExpectedGeoVector4) {
  ASSERT_EQ(GeoVector4<float>(0.0f, 1.0f, 0.0f, 0.0f), _dummyMatrix.getY());
}

TEST_F(GeoMatrix4x4Test, setYSetsExpectedGeoVector4) {
  _dummyMatrix.setY(GeoVector4<float>::one());
  ASSERT_EQ(GeoVector4<float>::one(), _dummyMatrix.getY());
}

TEST_F(GeoMatrix4x4Test, getZReturnsExpectedGeoVector4) {
  ASSERT_EQ(GeoVector4<float>(0.0f, 0.0f, 1.0f, 0.0f), _dummyMatrix.getZ());
}

TEST_F(GeoMatrix4x4Test, setZSetsExpectedGeoVector4) {
  _dummyMatrix.setZ(GeoVector4<float>::one());
  ASSERT_EQ(GeoVector4<float>::one(), _dummyMatrix.getZ());
}

TEST_F(GeoMatrix4x4Test, getWReturnsExpectedGeoVector4) {
  ASSERT_EQ(GeoVector4<float>(0.0f, 0.0f, 0.0f, 1.0f), _dummyMatrix.getW());
}

TEST_F(GeoMatrix4x4Test, setWSetsExpectedGeoVector4) {
  _dummyMatrix.setW(GeoVector4<float>::one());
  ASSERT_EQ(GeoVector4<float>::one(), _dummyMatrix.getW());
}

TEST_F(GeoMatrix4x4Test, addOperatorAddsCorrectlyForGeoMatrix4x4) {
  auto testMatOne = GeoMatrix4x4<float>(GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one());
  auto testMatTwo = GeoMatrix4x4<float>(GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f));
  auto result = testMatOne + testMatOne;
  EXPECT_EQ(result, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, subtractOperatorSubtractsCorrectlyForGeoMatrix4x4) {
  auto testMatOne = GeoMatrix4x4<float>(GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one());
  auto testMatTwo = GeoMatrix4x4<float>(GeoVector4<float>::zero(), GeoVector4<float>::zero(), GeoVector4<float>::zero(), GeoVector4<float>::zero());
  auto result = testMatOne - testMatOne;
  EXPECT_EQ(result, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, multiplyOperatorMultipliesCorrectlyForGeoMatrix4x4) {
  auto testMatOne = GeoMatrix4x4<float>(GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f));
  auto testMatTwo = GeoMatrix4x4<float>(GeoVector4<float>::uniform(16.0f), GeoVector4<float>::uniform(16.0f), GeoVector4<float>::uniform(16.0f), GeoVector4<float>::uniform(16.0f));
  auto result = testMatOne * testMatOne;
  EXPECT_EQ(result, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, addAssignOperatorAddsCorrectlyForGeoMatrix4x4) {
  auto testMatOne = GeoMatrix4x4<float>(GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one());
  auto testMatTwo = GeoMatrix4x4<float>(GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f));
  auto testMatThree = testMatOne;
  testMatOne += testMatThree;
  EXPECT_EQ(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, subtractAssignOperatorSubtractsCorrectlyForGeoMatrix4x4) {
  auto testMatOne = GeoMatrix4x4<float>(GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one());
  auto testMatTwo = GeoMatrix4x4<float>(GeoVector4<float>::zero(), GeoVector4<float>::zero(), GeoVector4<float>::zero(), GeoVector4<float>::zero());
  auto testMatThree = testMatOne;
  testMatOne -= testMatThree;
  EXPECT_EQ(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, multiplyAssignOperatorMultipliesCorrectlyForGeoMatrix4x4) {
  auto testMatOne = GeoMatrix4x4<float>(GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f));
  auto testMatTwo = GeoMatrix4x4<float>(GeoVector4<float>::uniform(16.0f), GeoVector4<float>::uniform(16.0f), GeoVector4<float>::uniform(16.0f), GeoVector4<float>::uniform(16.0f));
  auto testMatThree = testMatOne;
  testMatOne *= testMatThree;
  EXPECT_EQ(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, addOperatorAddsCorrectlyForTemplateType) {
  auto testMatOne = GeoMatrix4x4<float>(GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one());
  auto testMatTwo = GeoMatrix4x4<float>(GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f));
  auto result = testMatOne + 1.0f;
  EXPECT_EQ(result, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, subtractOperatorSubtractsCorrectlyForTemplateType) {
  auto testMatOne = GeoMatrix4x4<float>(GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one());
  auto testMatTwo = GeoMatrix4x4<float>(GeoVector4<float>::zero(), GeoVector4<float>::zero(), GeoVector4<float>::zero(), GeoVector4<float>::zero());
  auto result = testMatOne - 1.0f;
  EXPECT_EQ(result, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, multiplyOperatorMultipliesCorrectlyForTemplateType) {
  auto testMatOne = GeoMatrix4x4<float>(GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f));
  auto testMatTwo = GeoMatrix4x4<float>(GeoVector4<float>::uniform(4.0f), GeoVector4<float>::uniform(4.0f), GeoVector4<float>::uniform(4.0f), GeoVector4<float>::uniform(4.0f));
  auto result = testMatOne * 2.0f;
  EXPECT_EQ(result, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, addAssignOperatorAddsCorrectlyForTemplateType) {
  auto testMatOne = GeoMatrix4x4<float>(GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one());
  auto testMatTwo = GeoMatrix4x4<float>(GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f));
  testMatOne += 1.0f;
  EXPECT_EQ(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, subtractAssignOperatorSubtractsCorrectlyForTemplateType) {
  auto testMatOne = GeoMatrix4x4<float>(GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one());
  auto testMatTwo = GeoMatrix4x4<float>(GeoVector4<float>::zero(), GeoVector4<float>::zero(), GeoVector4<float>::zero(), GeoVector4<float>::zero());
  testMatOne -= 1.0f;
  EXPECT_EQ(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, multiplyAssignOperatorMultipliesCorrectlyForTemplateType) {
  auto testMatOne = GeoMatrix4x4<float>(GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f));
  auto testMatTwo = GeoMatrix4x4<float>(GeoVector4<float>::uniform(4.0f), GeoVector4<float>::uniform(4.0f), GeoVector4<float>::uniform(4.0f), GeoVector4<float>::uniform(4.0f));
  testMatOne *= 2.0f;
  EXPECT_EQ(testMatOne, testMatTwo);
}
