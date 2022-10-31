// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/NovelRT.h>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(GeoVector3Test, EqualityOperatorEvaluatesCorrectly)
{
    EXPECT_EQ(GeoVector3F(0.0f, 0.0f, 0.0f), GeoVector3F(0.0f, 0.0f, 0.0f));
}

TEST(GeoVector3Test, InequalityOperatorEvaluatesCorrectly)
{
    EXPECT_NE(GeoVector3F(0.0f, 0.0f, 0.0f), GeoVector3F(1.0f, 0.0f, 0.0f));
}

TEST(GeoVector3Test, LessThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(GeoVector3F(0.0f, 0.0f, 0.0f) < GeoVector3F(1.0f, 1.0f, 1.0f));
}

TEST(GeoVector3Test, LessOrEqualToThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(GeoVector3F(0.0f, 0.0f, 0.0f) <= GeoVector3F(1.0f, 1.0f, 1.0f));
    EXPECT_TRUE(GeoVector3F(1.0f, 1.0f, 1.0f) <= GeoVector3F(1.0f, 1.0f, 1.0f));
}

TEST(GeoVector3Test, GreaterThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(GeoVector3F(1.0f, 1.0f, 1.0f) > GeoVector3F(0.0f, 0.0f, 0.0f));
}

TEST(GeoVector3Test, GreaterThanOrEqualToOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(GeoVector3F(1.0f, 1.0f, 1.0f) >= GeoVector3F(0.0f, 0.0f, 0.0f));
    EXPECT_TRUE(GeoVector3F(1.0f, 1.0f, 1.0f) >= GeoVector3F(1.0f, 1.0f, 1.0f));
}

TEST(GeoVector3Test, StaticUniformCallReturnsGeoVector3WithUniformValues)
{
    EXPECT_EQ(GeoVector3F::Uniform(1.0f), GeoVector3F(1.0f, 1.0f, 1.0f));
}

TEST(GeoVector3Test, StaticZeroCallReturnsGeoVector3Zero)
{
    EXPECT_EQ(GeoVector3F::Zero(), GeoVector3F::Uniform(0.0f));
}

TEST(GeoVector3Test, StaticOneCallReturnsGeoVector3One)
{
    EXPECT_EQ(GeoVector3F::One(), GeoVector3F::Uniform(1.0f));
}

TEST(GeoVector3Test, AddOperatorAddsCorrectlyForGeoVector3)
{
    auto result = GeoVector3F::One() + GeoVector3F::One();
    EXPECT_EQ(result, GeoVector3F::Uniform(2.0f));
}

TEST(GeoVector3Test, SubtractOperatorSubtractsCorrectlyForGeoVector3)
{
    auto result = GeoVector3F::One() - GeoVector3F::One();
    EXPECT_EQ(result, GeoVector3F::Zero());
}

TEST(GeoVector3Test, MultiplyOperatorMultipliesCorrectlyForGeoVector3)
{
    auto result = GeoVector3F::Uniform(2.0f) * GeoVector3F::Uniform(2.0f);
    EXPECT_EQ(result, GeoVector3F::Uniform(4.0f));
}

TEST(GeoVector3Test, DivideOperatorDividesCorrectlyForGeoVector3)
{
    auto result = GeoVector3F::Uniform(2.0f) / GeoVector3F::Uniform(2.0f);
    EXPECT_EQ(result, GeoVector3F::One());
}

TEST(GeoVector3Test, AddOperatorAddsCorrectlyForTemplateType)
{
    auto result = GeoVector3F::One() + 1.0f;
    EXPECT_EQ(result, GeoVector3F::Uniform(2.0f));
}

TEST(GeoVector3Test, SubtractOperatorSubtractsCorrectlyForTemplateType)
{
    auto result = GeoVector3F::One() - 1.0f;
    EXPECT_EQ(result, GeoVector3F::Zero());
}

TEST(GeoVector3Test, MultiplyOperatorMultipliesCorrectlyForTemplateType)
{
    auto result = GeoVector3F::Uniform(2.0f) * 2.0f;
    EXPECT_EQ(result, GeoVector3F::Uniform(4.0f));
}

TEST(GeoVector3Test, multiplyOperatorMultipliesCorrectlyForTemplateTypeInverse)
{
    auto result = 2.0f * GeoVector3F::Uniform(2.0f);
    EXPECT_EQ(result, GeoVector3F::Uniform(4.0f));
}

TEST(GeoVector3Test, divideOperatorDividesCorrectlyForTemplateType)
{
    auto result = GeoVector3F::Uniform(2.0f) / 2.0f;
    EXPECT_EQ(result, GeoVector3F::One());
}

TEST(GeoVector3Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector3)
{
    auto result = GeoVector3F::One();
    result += GeoVector3F::One();
    EXPECT_EQ(result, GeoVector3F::Uniform(2.0f));
}

TEST(GeoVector3Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector3)
{
    auto result = GeoVector3F::One();
    result -= GeoVector3F::One();
    EXPECT_EQ(result, GeoVector3F::Zero());
}

TEST(GeoVector3Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector3)
{
    auto result = GeoVector3F::Uniform(2.0f);
    result *= GeoVector3F::Uniform(2.0f);
    EXPECT_EQ(result, GeoVector3F::Uniform(4.0f));
}

TEST(GeoVector3Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector3)
{
    auto result = GeoVector3F::Uniform(2.0f);
    result /= GeoVector3F::Uniform(2.0f);
    EXPECT_EQ(result, GeoVector3F::One());
}

TEST(GeoVector3Test, addAssignOperatorAddsAndAssignsCorrectlyForTemplateType)
{
    auto result = GeoVector3F::One();
    result += 1.0f;
    EXPECT_EQ(result, GeoVector3F::Uniform(2.0f));
}

TEST(GeoVector3Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForTemplateType)
{
    auto result = GeoVector3F::One();
    result -= 1.0f;
    EXPECT_EQ(result, GeoVector3F::Zero());
}

TEST(GeoVector3Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForTemplateType)
{
    auto result = GeoVector3F::Uniform(2.0f);
    result *= 2.0f;
    EXPECT_EQ(result, GeoVector3F::Uniform(4.0f));
}

TEST(GeoVector3Test, divideAssignOperatorDividesAndAssignsCorrectlyForTemplateType)
{
    auto result = GeoVector3F::Uniform(2.0f);
    result /= 2.0f;
    EXPECT_EQ(result, GeoVector3F::One());
}

TEST(GeoVector3Test, getNormalisedReturnsNormalisedGeoVector)
{
    auto vec = GeoVector3F::One().GetNormalised();
    float normalisedTotal = sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2));
    EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(GeoVector3Test, getMagnitudeReturnsCorrectLength)
{
    auto vec = GeoVector3F::One().GetNormalised();
    EXPECT_FLOAT_EQ(vec.GetMagnitude(), sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2)));
}

TEST(GeoVector3Test, getLengthReturnsCorrectLength)
{
    auto vec = GeoVector3F::One().GetNormalised();
    EXPECT_FLOAT_EQ(vec.GetLength(), sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2)));
}

TEST(GeoVector3Test, GetSquaredMagnitudeReturnsCorrectLength)
{
    auto vec = GeoVector3F::One().GetNormalised();
    EXPECT_FLOAT_EQ(vec.GetSquaredMagnitude(), powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2));
}

TEST(GeoVector3Test, GetSquaredLengthReturnsCorrectLength)
{
    auto vec = GeoVector3F::One().GetNormalised();
    EXPECT_FLOAT_EQ(vec.GetSquaredLength(), powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2));
}

TEST(GeoVector3Test, DotReturnsCorrectValue)
{
    auto vecA = GeoVector3F::Zero();
    auto vecB = GeoVector3F::One();
    EXPECT_FLOAT_EQ(vecA.Dot(vecB), (vecA.x * vecB.x) + (vecA.y * vecB.y) + (vecA.z * vecB.z));
}

TEST(GeoVector3Test, CrossReturnsCorrectValue)
{
    auto vecA = GeoVector3F(1,2,3);
    auto vecB = GeoVector3F(4,5,6);
    EXPECT_EQ(vecA.Cross(vecB), GeoVector3F((vecA.y * vecB.z) - (vecA.z * vecB.y), (vecA.z * vecB.x) - (vecA.x * vecB.z),  (vecA.x * vecB.y) - (vecA.y * vecB.x)));
}

TEST(GeoVector3Test, DistanceReturnsCorrectValue)
{
    auto vecA = GeoVector3F::Zero();
    auto vecB = GeoVector3F::One();
    EXPECT_FLOAT_EQ(vecA.Distance(vecB), sqrtf(powf(vecA.x - vecB.x, 2) + powf(vecA.y - vecB.y, 2) + powf(vecA.z - vecB.z, 2)));
}

TEST(GeoVector3Test, SquaredDistanceReturnsCorrectValue)
{
    auto vecA = GeoVector3F::Zero();
    auto vecB = GeoVector3F::One();
    EXPECT_FLOAT_EQ(vecA.SquaredDistance(vecB), powf(vecA.x - vecB.x, 2) + powf(vecA.y - vecB.y, 2) + powf(vecA.z - vecB.z, 2));
}

TEST(GeoVector3Test, RotateToAngleAroundPointDegRotatesCorrectAmount)
{
    auto vec = GeoVector3F(0.0f, 1.0f, 0.0f);
    vec.RotateToAngleAroundPointDeg(90.0f, GeoVector3F::Zero());
    EXPECT_TRUE(vec.EpsilonEquals(GeoVector3F(-1.0f, 0.0f, 0.0f), GeoVector3F::Uniform(1e-7f)));
}

TEST(GeoVector3Test, GeoVector2ConstructorReturnsCorrectGeoVector3)
{
    EXPECT_EQ(GeoVector3F(GeoVector2F::One()), GeoVector3F(1.0f, 1.0f, 0.0f));
}
