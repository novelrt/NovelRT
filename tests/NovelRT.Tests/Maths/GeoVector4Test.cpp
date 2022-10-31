// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/NovelRT.h>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(GeoVector4Test, equalityOperatorEvaluatesCorrectly)
{
    EXPECT_EQ(GeoVector4F(0.0f, 0.0f, 0.0f, 0.0f), GeoVector4F(0.0f, 0.0f, 0.0f, 0.0f));
}

TEST(GeoVector4Test, inequalityOperatorEvaluatesCorrectly)
{
    EXPECT_NE(GeoVector4F(0.0f, 0.0f, 0.0f, 0.0f), GeoVector4F(1.0f, 0.0f, 0.0f, 0.0f));
}

TEST(GeoVector4Test, lessThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(GeoVector4F(0.0f, 0.0f, 0.0f, 0.0f) < GeoVector4F(1.0f, 1.0f, 1.0f, 1.0f));
}

TEST(GeoVector4Test, lessThanOrEqualToThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(GeoVector4F(0.0f, 0.0f, 0.0f, 0.0f) <= GeoVector4F(1.0f, 1.0f, 1.0f, 1.0f));
    EXPECT_TRUE(GeoVector4F(1.0f, 1.0f, 1.0f, 1.0f) <= GeoVector4F(1.0f, 1.0f, 1.0f, 1.0f));
}

TEST(GeoVector4Test, greaterThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(GeoVector4F(1.0f, 1.0f, 1.0f, 1.0f) > GeoVector4F(0.0f, 0.0f, 0.0f, 0.0f));
}

TEST(GeoVector4Test, greaterThanOrEqualToOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(GeoVector4F(1.0f, 1.0f, 1.0f, 1.0f) >= GeoVector4F(0.0f, 0.0f, 0.0f, 0.0f));
    EXPECT_TRUE(GeoVector4F(1.0f, 1.0f, 1.0f, 1.0f) >= GeoVector4F(1.0f, 1.0f, 1.0f, 1.0f));
}

TEST(GeoVector4Test, staticUniformCallReturnsGeoVector4WithUniformValues)
{
    EXPECT_EQ(GeoVector4F::Uniform(1.0f), GeoVector4F(1.0f, 1.0f, 1.0f, 1.0f));
}

TEST(GeoVector4Test, staticZeroCallReturnsGeoVector4Zero)
{
    EXPECT_EQ(GeoVector4F::Zero(), GeoVector4F(0.0f, 0.0f, 0.0f, 0.0f));
}

TEST(GeoVector4Test, staticOneCallReturnsGeoVector4One)
{
    EXPECT_EQ(GeoVector4F::One(), GeoVector4F(1.0f, 1.0f, 1.0f, 1.0f));
}

TEST(GeoVector4Test, addOperatorAddsCorrectlyForGeoVector4)
{
    auto result = GeoVector4F::One() + GeoVector4F::One();
    EXPECT_EQ(result, GeoVector4F::Uniform(2.0f));
}

TEST(GeoVector4Test, subtractOperatorSubtractsCorrectlyForGeoVector4)
{
    auto result = GeoVector4F::One() - GeoVector4F::One();
    EXPECT_EQ(result, GeoVector4F::Zero());
}

TEST(GeoVector4Test, multiplyOperatorMultipliesCorrectlyForGeoVector4)
{
    auto result = GeoVector4F::Uniform(2.0f) * GeoVector4F::Uniform(2.0f);
    EXPECT_EQ(result, GeoVector4F::Uniform(4.0f));
}

TEST(GeoVector4Test, multiplyOperatorMultipliesCorrectlyForTemplateTypeInverse)
{
    auto result = 2.0f * GeoVector4F::Uniform(2.0f);
    EXPECT_EQ(result, GeoVector4F::Uniform(4.0f));
}

TEST(GeoVector4Test, divideOperatorDividesCorrectlyForGeoVector4)
{
    auto result = GeoVector4F::Uniform(2.0f) / GeoVector4F::Uniform(2.0f);
    EXPECT_EQ(result, GeoVector4F::One());
}

TEST(GeoVector4Test, addOperatorAddsCorrectlyForTemplateType)
{
    auto result = GeoVector4F::One() + 1.0f;
    EXPECT_EQ(result, GeoVector4F::Uniform(2.0f));
}

TEST(GeoVector4Test, subtractOperatorSubtractsCorrectlyForTemplateType)
{
    auto result = GeoVector4F::One() - 1.0f;
    EXPECT_EQ(result, GeoVector4F::Zero());
}

TEST(GeoVector4Test, multiplyOperatorMultipliesCorrectlyForTemplateType)
{
    auto result = GeoVector4F::Uniform(2.0f) * 2.0f;
    EXPECT_EQ(result, GeoVector4F::Uniform(4.0f));
}

TEST(GeoVector4Test, divideOperatorDividesCorrectlyForTemplateType)
{
    auto result = GeoVector4F::Uniform(2.0f) / 2.0f;
    EXPECT_EQ(result, GeoVector4F::One());
}

TEST(GeoVector4Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector4)
{
    auto result = GeoVector4F::One();
    result += GeoVector4F::One();
    EXPECT_EQ(result, GeoVector4F::Uniform(2.0f));
}

TEST(GeoVector4Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector4)
{
    auto result = GeoVector4F::One();
    result -= GeoVector4F::One();
    EXPECT_EQ(result, GeoVector4F::Zero());
}

TEST(GeoVector4Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector4)
{
    auto result = GeoVector4F::Uniform(2.0f);
    result *= GeoVector4F::Uniform(2.0f);
    EXPECT_EQ(result, GeoVector4F::Uniform(4.0f));
}

TEST(GeoVector4Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector4)
{
    auto result = GeoVector4F::Uniform(2.0f);
    result /= GeoVector4F::Uniform(2.0f);
    EXPECT_EQ(result, GeoVector4F::One());
}

TEST(GeoVector4Test, addAssignOperatorAddsAndAssignsCorrectlyForTemplateType)
{
    auto result = GeoVector4F::One();
    result += 1.0f;
    EXPECT_EQ(result, GeoVector4F::Uniform(2.0f));
}

TEST(GeoVector4Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForTemplateType)
{
    auto result = GeoVector4F::One();
    result -= 1.0f;
    EXPECT_EQ(result, GeoVector4F::Zero());
}

TEST(GeoVector4Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForTemplateType)
{
    auto result = GeoVector4F::Uniform(2.0f);
    result *= 2.0f;
    EXPECT_EQ(result, GeoVector4F::Uniform(4.0f));
}

TEST(GeoVector4Test, divideAssignOperatorDividesAndAssignsCorrectlyForTemplateType)
{
    auto result = GeoVector4F::Uniform(2.0f);
    result /= 2.0f;
    EXPECT_EQ(result, GeoVector4F::One());
}

TEST(GeoVector4Test, getNormalisedReturnsNormalisedGeoVector)
{
    auto vec = GeoVector4F::One().GetNormalised();
    float normalisedTotal = sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2) + powf(vec.w, 2));
    EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(GeoVector4Test, getMagnitudeReturnsCorrectLength)
{
    auto vec = GeoVector4F::One().GetNormalised();
    EXPECT_FLOAT_EQ(vec.GetMagnitude(), sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2) + powf(vec.w, 2)));
}

TEST(GeoVector4Test, getLengthReturnsCorrectLength)
{
    auto vec = GeoVector4F::One().GetNormalised();
    EXPECT_FLOAT_EQ(vec.GetLength(), sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2) + powf(vec.w, 2)));
}

TEST(GeoVector4Test, rotateToAngleAroundPointRotatesCorrectAmount)
{
    auto vec = GeoVector4F(0.0f, 1.0f, 0.0f, 0.0f);
    vec.RotateToAngleAroundPoint(90.0f, GeoVector4F::Zero());
    EXPECT_TRUE(vec.EpsilonEquals(GeoVector4F(-1.0f, 0.0f, 0.0f, 0.0f), GeoVector4F::Uniform(1e-7f)));
}

TEST(GeoVector4Test, GetSquaredMagnitudeReturnsCorrectLength)
{
    auto vec = GeoVector4F::One().GetNormalised();
    EXPECT_FLOAT_EQ(vec.GetSquaredMagnitude(), powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2) + powf(vec.w, 2));
}

TEST(GeoVector4Test, GetSquaredLengthReturnsCorrectLength)
{
    auto vec = GeoVector4F::One().GetNormalised();
    EXPECT_FLOAT_EQ(vec.GetSquaredLength(), powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2) + powf(vec.w, 2));
}

TEST(GeoVector4Test, DotReturnsCorrectValue)
{
    auto vecA = GeoVector4F::Zero();
    auto vecB = GeoVector4F::One();
    EXPECT_FLOAT_EQ(vecA.Dot(vecB), (vecA.x * vecB.x) + (vecA.y * vecB.y) + (vecA.z * vecB.z) + (vecA.w * vecB.w));
}

TEST(GeoVector4Test, DistanceReturnsCorrectValue)
{
    auto vecA = GeoVector4F::Zero();
    auto vecB = GeoVector4F::One();
    EXPECT_FLOAT_EQ(vecA.Distance(vecB), sqrtf(powf(vecA.x - vecB.x, 2) + powf(vecA.y - vecB.y, 2) + powf(vecA.z - vecB.z, 2) + powf(vecA.w - vecB.w, 2)));
}

TEST(GeoVector4Test, SquaredDistanceReturnsCorrectValue)
{
    auto vecA = GeoVector4F::Zero();
    auto vecB = GeoVector4F::One();
    EXPECT_FLOAT_EQ(vecA.SquaredDistance(vecB), powf(vecA.x - vecB.x, 2) + powf(vecA.y - vecB.y, 2) + powf(vecA.z - vecB.z, 2) + powf(vecA.w - vecB.w, 2));
}

TEST(GeoVector4Test, geoVector2ConstructorReturnsCorrectGeoVector4)
{
    EXPECT_EQ(GeoVector4F(GeoVector2F::One()), GeoVector4F(1.0f, 1.0f, 0.0f, 0.0f));
}

TEST(GeoVector4Test, geoVector3ConstructorReturnsCorrectGeoVector4)
{
    EXPECT_EQ(GeoVector4F(GeoVector3F::One()), GeoVector4F(1.0f, 1.0f, 1.0f, 0.0f));
}
