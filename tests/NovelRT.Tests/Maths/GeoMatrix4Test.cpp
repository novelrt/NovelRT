// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

class GeoMatrix4Test : public testing::Test {
protected:
  GeoMatrix4<float> _dummyMatrix;

  void SetUp() override {
    _dummyMatrix = GeoMatrix4<float>(GeoVector4<float>(1.0f, 0.0f, 0.0f, 0.0f),
      GeoVector4<float>(0.0f, 1.0f, 0.0f, 0.0f),
      GeoVector4<float>(0.0f, 0.0f, 1.0f, 0.0f),
      GeoVector4<float>(0.0f, 0.0f, 0.0f, 1.0f));
  }
};

TEST_F(GeoMatrix4Test, equalityOperatorEvaluatesCorrectly) {
  auto testMatOne = GeoMatrix4<float>(GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one());

  auto testMatTwo = GeoMatrix4<float>(GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one());

  ASSERT_EQ(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4Test, inequalityOperatorEvaluatesCorrectly) {
  auto testMatOne = GeoMatrix4<float>(GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one());

  auto testMatTwo = GeoMatrix4<float>(GeoVector4<float>::zero(), GeoVector4<float>::zero(), GeoVector4<float>::zero(), GeoVector4<float>::zero());

  ASSERT_NE(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4Test, getDefaultIdentityReturnsIdentityMatrix) {
  ASSERT_EQ(GeoMatrix4<float>::getDefaultIdentity(), _dummyMatrix);
}

TEST_F(GeoMatrix4Test, getXReturnsExpectedGeoVector4) {
  ASSERT_EQ(GeoVector4<float>(1.0f, 0.0f, 0.0f, 0.0f), _dummyMatrix.getX());
}

TEST_F(GeoMatrix4Test, setXSetsExpectedGeoVector4) {
  _dummyMatrix.setX(GeoVector4<float>::one());
  ASSERT_EQ(GeoVector4<float>::one(), _dummyMatrix.getX());
}

TEST_F(GeoMatrix4Test, getYReturnsExpectedGeoVector4) {
  ASSERT_EQ(GeoVector4<float>(0.0f, 1.0f, 0.0f, 0.0f), _dummyMatrix.getY());
}

TEST_F(GeoMatrix4Test, setYSetsExpectedGeoVector4) {
  _dummyMatrix.setY(GeoVector4<float>::one());
  ASSERT_EQ(GeoVector4<float>::one(), _dummyMatrix.getY());
}

TEST_F(GeoMatrix4Test, getZReturnsExpectedGeoVector4) {
  ASSERT_EQ(GeoVector4<float>(0.0f, 0.0f, 1.0f, 0.0f), _dummyMatrix.getZ());
}

TEST_F(GeoMatrix4Test, setZSetsExpectedGeoVector4) {
  _dummyMatrix.setZ(GeoVector4<float>::one());
  ASSERT_EQ(GeoVector4<float>::one(), _dummyMatrix.getZ());
}

TEST_F(GeoMatrix4Test, getWReturnsExpectedGeoVector4) {
  ASSERT_EQ(GeoVector4<float>(0.0f, 0.0f, 0.0f, 1.0f), _dummyMatrix.getW());
}

TEST_F(GeoMatrix4Test, setWSetsExpectedGeoVector4) {
  _dummyMatrix.setW(GeoVector4<float>::one());
  ASSERT_EQ(GeoVector4<float>::one(), _dummyMatrix.getW());
}

TEST_F(GeoMatrix4Test, addOperatorAddsCorrectlyForGeoMatrix4) {
  auto testMatOne = GeoMatrix4<float>(GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one());
  auto testMatTwo = GeoMatrix4<float>(GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f));
  auto result = testMatOne + testMatOne;
  EXPECT_EQ(result, testMatTwo);
}

TEST_F(GeoMatrix4Test, subtractOperatorSubtractsCorrectlyForGeoMatrix4) {
  auto testMatOne = GeoMatrix4<float>(GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one());
  auto testMatTwo = GeoMatrix4<float>(GeoVector4<float>::zero(), GeoVector4<float>::zero(), GeoVector4<float>::zero(), GeoVector4<float>::zero());
  auto result = testMatOne - testMatOne;
  EXPECT_EQ(result, testMatTwo);
}

TEST_F(GeoMatrix4Test, multiplyOperatorMultipliesCorrectlyForGeoMatrix4) {
  auto testMatOne = GeoMatrix4<float>(GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f));
  auto testMatTwo = GeoMatrix4<float>(GeoVector4<float>::uniform(16.0f), GeoVector4<float>::uniform(16.0f), GeoVector4<float>::uniform(16.0f), GeoVector4<float>::uniform(16.0f));
  auto result = testMatOne * testMatOne;
  EXPECT_EQ(result, testMatTwo);
}

TEST_F(GeoMatrix4Test, addAssignOperatorAddsCorrectlyForGeoMatrix4) {
  auto testMatOne = GeoMatrix4<float>(GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one());
  auto testMatTwo = GeoMatrix4<float>(GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f));
  auto testMatThree = testMatOne;
  testMatOne += testMatThree;
  EXPECT_EQ(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4Test, subtractAssignOperatorSubtractsCorrectlyForGeoMatrix4) {
  auto testMatOne = GeoMatrix4<float>(GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one());
  auto testMatTwo = GeoMatrix4<float>(GeoVector4<float>::zero(), GeoVector4<float>::zero(), GeoVector4<float>::zero(), GeoVector4<float>::zero());
  auto testMatThree = testMatOne;
  testMatOne -= testMatThree;
  EXPECT_EQ(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4Test, multiplyAssignOperatorMultipliesCorrectlyForGeoMatrix4) {
  auto testMatOne = GeoMatrix4<float>(GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f));
  auto testMatTwo = GeoMatrix4<float>(GeoVector4<float>::uniform(16.0f), GeoVector4<float>::uniform(16.0f), GeoVector4<float>::uniform(16.0f), GeoVector4<float>::uniform(16.0f));
  auto testMatThree = testMatOne;
  testMatOne *= testMatThree;
  EXPECT_EQ(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4Test, addOperatorAddsCorrectlyForTemplateType) {
  auto testMatOne = GeoMatrix4<float>(GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one());
  auto testMatTwo = GeoMatrix4<float>(GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f));
  auto result = testMatOne + 1.0f;
  EXPECT_EQ(result, testMatTwo);
}

TEST_F(GeoMatrix4Test, subtractOperatorSubtractsCorrectlyForTemplateType) {
  auto testMatOne = GeoMatrix4<float>(GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one());
  auto testMatTwo = GeoMatrix4<float>(GeoVector4<float>::zero(), GeoVector4<float>::zero(), GeoVector4<float>::zero(), GeoVector4<float>::zero());
  auto result = testMatOne - 1.0f;
  EXPECT_EQ(result, testMatTwo);
}

TEST_F(GeoMatrix4Test, multiplyOperatorMultipliesCorrectlyForTemplateType) {
  auto testMatOne = GeoMatrix4<float>(GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f));
  auto testMatTwo = GeoMatrix4<float>(GeoVector4<float>::uniform(4.0f), GeoVector4<float>::uniform(4.0f), GeoVector4<float>::uniform(4.0f), GeoVector4<float>::uniform(4.0f));
  auto result = testMatOne * 2.0f;
  EXPECT_EQ(result, testMatTwo);
}

TEST_F(GeoMatrix4Test, addAssignOperatorAddsCorrectlyForTemplateType) {
  auto testMatOne = GeoMatrix4<float>(GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one());
  auto testMatTwo = GeoMatrix4<float>(GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f));
  testMatOne += 1.0f;
  EXPECT_EQ(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4Test, subtractAssignOperatorSubtractsCorrectlyForTemplateType) {
  auto testMatOne = GeoMatrix4<float>(GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one(), GeoVector4<float>::one());
  auto testMatTwo = GeoMatrix4<float>(GeoVector4<float>::zero(), GeoVector4<float>::zero(), GeoVector4<float>::zero(), GeoVector4<float>::zero());
  testMatOne -= 1.0f;
  EXPECT_EQ(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4Test, multiplyAssignOperatorMultipliesCorrectlyForTemplateType) {
  auto testMatOne = GeoMatrix4<float>(GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f), GeoVector4<float>::uniform(2.0f));
  auto testMatTwo = GeoMatrix4<float>(GeoVector4<float>::uniform(4.0f), GeoVector4<float>::uniform(4.0f), GeoVector4<float>::uniform(4.0f), GeoVector4<float>::uniform(4.0f));
  testMatOne *= 2.0f;
  EXPECT_EQ(testMatOne, testMatTwo);
}
