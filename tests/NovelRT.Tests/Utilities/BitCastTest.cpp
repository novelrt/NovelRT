// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/NovelRT.h>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Utilities;
using namespace NovelRT::Maths;

TEST(BitCastTest, CastGlmVec2ToNovelRTGeoVector2F)
{
    float x = 1.0f, y = 2.0f;
    glm::vec2 glmVec2 = glm::vec2{x, y};
    GeoVector2F nrtVec2 = Misc::BitCast<GeoVector2F>(glmVec2);

    EXPECT_FLOAT_EQ(nrtVec2.x, x);
    EXPECT_FLOAT_EQ(nrtVec2.y, y);
}

TEST(BitCastTest, CastGlmVec3ToNovelRTGeoVector3F)
{
    float x = 1.0f, y = 2.0f, z = 3.0f;
    glm::vec3 glmVec3 = glm::vec3{x, y, z};
    GeoVector3F nrtVec3 = Misc::BitCast<GeoVector3F>(glmVec3);

    EXPECT_FLOAT_EQ(nrtVec3.x, x);
    EXPECT_FLOAT_EQ(nrtVec3.y, y);
    EXPECT_FLOAT_EQ(nrtVec3.z, z);
}

TEST(BitCastTest, CastGlmVec4ToNovelRTGeoVector4F)
{
    float x = 1.0f, y = 2.0f, z = 3.0f, w = 4.0f;
    glm::vec4 glmVec4 = glm::vec4{x, y, z, w};
    GeoVector4F nrtVec4 = Misc::BitCast<GeoVector4F>(glmVec4);

    EXPECT_FLOAT_EQ(nrtVec4.x, x);
    EXPECT_FLOAT_EQ(nrtVec4.y, y);
    EXPECT_FLOAT_EQ(nrtVec4.z, z);
    EXPECT_FLOAT_EQ(nrtVec4.w, w);
}

TEST(BitCastTest, CastGlmMat4ToNovelRTGeoMatrix4x4)
{
    float x1 = 1.0f, y1 = 0.0f, z1 = 0.0f, w1 = 0.0f;
    float x2 = 0.0f, y2 = 1.0f, z2 = 0.0f, w2 = 0.0f;
    float x3 = 0.0f, y3 = 0.0f, z3 = 1.0f, w3 = 0.0f;
    float x4 = 0.0f, y4 = 0.0f, z4 = 0.0f, w4 = 1.0f;
    glm::mat4 glmMat4 = glm::mat4{x1, y1, z1, w1, x2, y2, z2, w2, x3, y3, z3, w3, x4, y4, z4, w4};
    GeoMatrix4x4F nrtMat4x4 = Misc::BitCast<GeoMatrix4x4F>(glmMat4);

    EXPECT_FLOAT_EQ(nrtMat4x4.x.x, x1);
    EXPECT_FLOAT_EQ(nrtMat4x4.x.y, y1);
    EXPECT_FLOAT_EQ(nrtMat4x4.x.z, z1);
    EXPECT_FLOAT_EQ(nrtMat4x4.x.w, w1);

    EXPECT_FLOAT_EQ(nrtMat4x4.y.x, x2);
    EXPECT_FLOAT_EQ(nrtMat4x4.y.y, y2);
    EXPECT_FLOAT_EQ(nrtMat4x4.y.z, z2);
    EXPECT_FLOAT_EQ(nrtMat4x4.y.w, w2);

    EXPECT_FLOAT_EQ(nrtMat4x4.z.x, x3);
    EXPECT_FLOAT_EQ(nrtMat4x4.z.y, y3);
    EXPECT_FLOAT_EQ(nrtMat4x4.z.z, z3);
    EXPECT_FLOAT_EQ(nrtMat4x4.z.w, w3);

    EXPECT_FLOAT_EQ(nrtMat4x4.w.x, x4);
    EXPECT_FLOAT_EQ(nrtMat4x4.w.y, y4);
    EXPECT_FLOAT_EQ(nrtMat4x4.w.z, z4);
    EXPECT_FLOAT_EQ(nrtMat4x4.w.w, w4);
}