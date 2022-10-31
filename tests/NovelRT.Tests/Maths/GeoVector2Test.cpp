// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/NovelRT.h>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(GeoVector2Test, EqualityOperatorEvaluatesCorrectly)
{
    EXPECT_EQ(GeoVector2F(0.0f, 0.0f), GeoVector2F(0.0f, 0.0f));
}

TEST(GeoVector2Test, InequalityOperatorEvaluatesCorrectly)
{
    EXPECT_NE(GeoVector2F(0.0f, 0.0f), GeoVector2F(1.0f, 0.0f));
}

TEST(GeoVector2Test, LessThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(GeoVector2F(0.0f, 0.0f) < GeoVector2F(1.0f, 1.0f));
}

TEST(GeoVector2Test, LessOrEqualToThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(GeoVector2F(0.0f, 0.0f) <= GeoVector2F(1.0f, 1.0f));
    EXPECT_TRUE(GeoVector2F(1.0f, 1.0f) <= GeoVector2F(1.0f, 1.0f));
}

TEST(GeoVector2Test, GreaterThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(GeoVector2F(1.0f, 1.0f) > GeoVector2F(0.0f, 0.0f));
}

TEST(GeoVector2Test, GreaterThanOrEqualToOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(GeoVector2F(1.0f, 1.0f) >= GeoVector2F(0.0f, 0.0f));
    EXPECT_TRUE(GeoVector2F(1.0f, 1.0f) >= GeoVector2F(1.0f, 1.0f));
}

TEST(GeoVector2Test, StaticUniformCallReturnsGeoVector2WithUniformValues)
{
    EXPECT_EQ(GeoVector2F::Uniform(1.0f), GeoVector2F(1.0f, 1.0f));
}

TEST(GeoVector2Test, StaticZeroCallReturnsGeoVector2Zero)
{
    EXPECT_EQ(GeoVector2F::Zero(), GeoVector2F::Uniform(0.0f));
}

TEST(GeoVector2Test, StaticOneCallReturnsGeoVector2One)
{
    EXPECT_EQ(GeoVector2F::One(), GeoVector2F::Uniform(1.0f));
}

TEST(GeoVector2Test, AddOperatorAddsCorrectlyForGeoVector2)
{
    auto result = GeoVector2F::One() + GeoVector2F::One();
    EXPECT_EQ(result, GeoVector2F::Uniform(2.0f));
}

TEST(GeoVector2Test, SubtractOperatorSubtractsCorrectlyForGeoVector2)
{
    auto result = GeoVector2F::One() - GeoVector2F::One();
    EXPECT_EQ(result, GeoVector2F::Zero());
}

TEST(GeoVector2Test, MultiplyOperatorMultipliesCorrectlyForGeoVector2)
{
    auto result = GeoVector2F::Uniform(2.0f) * GeoVector2F::Uniform(2.0f);
    EXPECT_EQ(result, GeoVector2F::Uniform(4.0f));
}

TEST(GeoVector2Test, DivideOperatorDividesCorrectlyForGeoVector2)
{
    auto result = GeoVector2F::Uniform(2.0f) / GeoVector2F::Uniform(2.0f);
    EXPECT_EQ(result, GeoVector2F::One());
}

TEST(GeoVector2Test, AddOperatorAddsCorrectlyForTemplateType)
{
    auto result = GeoVector2F::One() + 1.0f;
    EXPECT_EQ(result, GeoVector2F::Uniform(2.0f));
}

TEST(GeoVector2Test, SubtractOperatorSubtractsCorrectlyForTemplateType)
{
    auto result = GeoVector2F::One() - 1.0f;
    EXPECT_EQ(result, GeoVector2F::Zero());
}

TEST(GeoVector2Test, MultiplyOperatorMultipliesCorrectlyForTemplateType)
{
    auto result = GeoVector2F::Uniform(2.0f) * 2.0f;
    EXPECT_EQ(result, GeoVector2F::Uniform(4.0f));
}

TEST(GeoVector2Test, MultiplyOperatorMultipliesCorrectlyForTemplateTypeInverse)
{
    auto result = 2.0f * GeoVector2F::Uniform(2.0f);
    EXPECT_EQ(result, GeoVector2F::Uniform(4.0f));
}

TEST(GeoVector2Test, DivideOperatorDividesCorrectlyForTemplateType)
{
    auto result = GeoVector2F::Uniform(2.0f) / 2.0f;
    EXPECT_EQ(result, GeoVector2F::One());
}

TEST(GeoVector2Test, AddAssignOperatorAddsAndAssignsCorrectlyForGeoVector2)
{
    auto result = GeoVector2F::One();
    result += GeoVector2F::One();
    EXPECT_EQ(result, GeoVector2F::Uniform(2.0f));
}

TEST(GeoVector2Test, SubtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector2)
{
    auto result = GeoVector2F::One();
    result -= GeoVector2F::One();
    EXPECT_EQ(result, GeoVector2F::Zero());
}

TEST(GeoVector2Test, MultiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector2)
{
    auto result = GeoVector2F::Uniform(2.0f);
    result *= GeoVector2F::Uniform(2.0f);
    EXPECT_EQ(result, GeoVector2F::Uniform(4.0f));
}

TEST(GeoVector2Test, DivideAssignOperatorDividesAndAssignsCorrectlyForGeoVector2)
{
    auto result = GeoVector2F::Uniform(2.0f);
    result /= GeoVector2F::Uniform(2.0f);
    EXPECT_EQ(result, GeoVector2F::One());
}

TEST(GeoVector2Test, AddAssignOperatorAddsAndAssignsCorrectlyForTemplateType)
{
    auto result = GeoVector2F::One();
    result += 1.0f;
    EXPECT_EQ(result, GeoVector2F::Uniform(2.0f));
}

TEST(GeoVector2Test, SubtractAssignOperatorSubtractsAndAssignsCorrectlyForTemplateType)
{
    auto result = GeoVector2F::One();
    result -= 1.0f;
    EXPECT_EQ(result, GeoVector2F::Zero());
}

TEST(GeoVector2Test, MultiplyAssignOperatorMultipliesAndAssignsCorrectlyForTemplateType)
{
    auto result = GeoVector2F::Uniform(2.0f);
    result *= 2.0f;
    EXPECT_EQ(result, GeoVector2F::Uniform(4.0f));
}

TEST(GeoVector2Test, DivideAssignOperatorDividesAndAssignsCorrectlyForTemplateType)
{
    auto result = GeoVector2F::Uniform(2.0f);
    result /= 2.0f;
    EXPECT_EQ(result, GeoVector2F::One());
}

TEST(GeoVector2Test, GetNormalisedReturnsNormalisedGeoVector)
{
    auto vec = GeoVector2F::One().GetNormalised();
    float normalisedTotal = sqrtf(powf(vec.x, 2) + powf(vec.y, 2));
    EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(GeoVector2Test, GetMagnitudeReturnsCorrectLength)
{
    auto vec = GeoVector2F::One().GetNormalised();
    EXPECT_FLOAT_EQ(vec.GetMagnitude(), sqrtf(powf(vec.x, 2) + powf(vec.y, 2)));
}

TEST(GeoVector2Test, GetLengthReturnsCorrectLength)
{
    auto vec = GeoVector2F::One().GetNormalised();
    EXPECT_FLOAT_EQ(vec.GetLength(), sqrtf(powf(vec.x, 2) + powf(vec.y, 2)));
}

TEST(GeoVector2Test, GetSquaredMagnitudeReturnsCorrectLength)
{
    auto vec = GeoVector2F::One().GetNormalised();
    EXPECT_FLOAT_EQ(vec.GetSquaredMagnitude(), powf(vec.x, 2) + powf(vec.y, 2));
}

TEST(GeoVector2Test, GetSquaredLengthReturnsCorrectLength)
{
    auto vec = GeoVector2F::One().GetNormalised();
    EXPECT_FLOAT_EQ(vec.GetSquaredLength(), powf(vec.x, 2) + powf(vec.y, 2));
}

TEST(GeoVector2Test, DotReturnsCorrectValue)
{
    auto vecA = GeoVector2F::Zero();
    auto vecB = GeoVector2F::One();
    EXPECT_FLOAT_EQ(vecA.Dot(vecB), (vecA.x * vecB.x) + (vecA.y * vecB.y));
}

TEST(GeoVector2Test, DistanceReturnsCorrectValue)
{
    auto vecA = GeoVector2F::Zero();
    auto vecB = GeoVector2F::One();
    EXPECT_FLOAT_EQ(vecA.Distance(vecB), sqrtf(powf(vecA.x - vecB.x, 2) + powf(vecA.y - vecB.y, 2)));
}

TEST(GeoVector2Test, SquaredDistanceReturnsCorrectValue)
{
    auto vecA = GeoVector2F::Zero();
    auto vecB = GeoVector2F::One();
    EXPECT_FLOAT_EQ(vecA.SquaredDistance(vecB), powf(vecA.x - vecB.x, 2) + powf(vecA.y - vecB.y, 2));
}

TEST(GeoVector2Test, RotateToAngleAroundPointDegRotatesCorrectAmount)
{
    auto vec = GeoVector2F(0.0f, 1.0f);
    vec.RotateToAngleAroundPointDeg(90.0f, GeoVector2F::Zero());
    EXPECT_TRUE(vec.EpsilonEquals(GeoVector2F(-1.0f, 0.0f), GeoVector2F::Uniform(1e-7f)));
}
