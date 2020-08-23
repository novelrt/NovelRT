
// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include <NovelRT.Interop/Maths/NovelRTGeoMatrix4x4F.h>
#include <cmath>

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(IntertopGeoMatrix4x4FTest, isNaNReturnsTrueWhenGivenNaNMatrix) {
    EXPECT_TRUE(NovelRT_GeoMatrix4x4F_isNaN(NovelRTGeoMatrix4x4F {NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN), NovelRT_GeoVector4F_uniform(NAN)}));
}

TEST(InteropGeoMatrix4xFTest, getDefaultIdentityReturnsCorrectIdentityMatrix) {
    auto mat4 = NovelRT_GeoMatrix4x4F_getDefaultIdentity();
    EXPECT_EQ(Maths::GeoMatrix4x4<float>::getDefaultIdentity(), reinterpret_cast<Maths::GeoMatrix4x4<float>&>(mat4));
}