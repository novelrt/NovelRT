// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(GeoMatrix4Test, equalityOperatorEvaluatesCorrectly) {
  auto testMatOne = GeoMatrix4<float>(GeoVector4<float>(1.0f, 0.0f, 0.0f, 0.0f),
    GeoVector4<float>(0.0f, 1.0f, 0.0f, 0.0f),
    GeoVector4<float>(0.0f, 0.0f, 1.0f, 0.0f),
    GeoVector4<float>(0.0f, 0.0f, 0.0f, 1.0f));

  auto testMatTwo = GeoMatrix4<float>(GeoVector4<float>(1.0f, 0.0f, 0.0f, 0.0f),
    GeoVector4<float>(0.0f, 1.0f, 0.0f, 0.0f),
    GeoVector4<float>(0.0f, 0.0f, 1.0f, 0.0f),
    GeoVector4<float>(0.0f, 0.0f, 0.0f, 1.0f));

  ASSERT_EQ(testMatOne, testMatTwo);
}

TEST(GeoMatrix4Test, inequalityOperatorEvaluatesCorrectly) {
  auto testMatOne = GeoMatrix4<float>(GeoVector4<float>(1.0f, 1.0f, 0.0f, 0.0f),
    GeoVector4<float>(0.0f, 1.0f, 0.0f, 0.0f),
    GeoVector4<float>(0.0f, 0.0f, 1.0f, 0.0f),
    GeoVector4<float>(0.0f, 0.0f, 0.0f, 1.0f));

  auto testMatTwo = GeoMatrix4<float>(GeoVector4<float>(1.0f, 0.0f, 0.0f, 0.0f),
    GeoVector4<float>(0.0f, 1.0f, 0.0f, 0.0f),
    GeoVector4<float>(0.0f, 0.0f, 1.0f, 0.0f),
    GeoVector4<float>(0.0f, 0.0f, 0.0f, 1.0f));

  ASSERT_NE(testMatOne, testMatTwo);
}

TEST(GeoMatrix4Test, getDefaultIdentityReturnsIdentityMatrix) {
  auto testMat = GeoMatrix4<float>(GeoVector4<float>(1.0f, 0.0f, 0.0f, 0.0f),
    GeoVector4<float>(0.0f, 1.0f, 0.0f, 0.0f),
    GeoVector4<float>(0.0f, 0.0f, 1.0f, 0.0f),
    GeoVector4<float>(0.0f, 0.0f, 0.0f, 1.0f));

  ASSERT_EQ(GeoMatrix4<float>::getDefaultIdentity(), testMat);
}
