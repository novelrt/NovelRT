// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/NovelRT.h>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(GeoVector2Test, equalityOperatorEvaluatesCorrectly)
{
    EXPECT_EQ(GeoVector2F(0.0f, 0.0f), GeoVector2F(0.0f, 0.0f));
}

TEST(GeoVector2Test, inequalityOperatorEvaluatesCorrectly)
{
    EXPECT_NE(GeoVector2F(0.0f, 0.0f), GeoVector2F(1.0f, 0.0f));
}

TEST(GeoVector2Test, lessThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(GeoVector2F(0.0f, 0.0f) < GeoVector2F(1.0f, 1.0f));
}

TEST(GeoVector2Test, lessOrEqualToThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(GeoVector2F(0.0f, 0.0f) <= GeoVector2F(1.0f, 1.0f));
    EXPECT_TRUE(GeoVector2F(1.0f, 1.0f) <= GeoVector2F(1.0f, 1.0f));
}

TEST(GeoVector2Test, greaterThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(GeoVector2F(1.0f, 1.0f) > GeoVector2F(0.0f, 0.0f));
}

TEST(GeoVector2Test, greaterThanOrEqualToOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(GeoVector2F(1.0f, 1.0f) >= GeoVector2F(0.0f, 0.0f));
    EXPECT_TRUE(GeoVector2F(1.0f, 1.0f) >= GeoVector2F(1.0f, 1.0f));
}

TEST(GeoVector2Test, staticUniformCallReturnsGeoVector2WithUniformValues)
{
    EXPECT_EQ(GeoVector2F::Uniform(1.0f), GeoVector2F(1.0f, 1.0f));
}

TEST(GeoVector2Test, staticZeroCallReturnsGeoVector2Zero)
{
    EXPECT_EQ(GeoVector2F::Zero(), GeoVector2F::Uniform(0.0f));
}

TEST(GeoVector2Test, staticOneCallReturnsGeoVector2One)
{
    EXPECT_EQ(GeoVector2F::One(), GeoVector2F::Uniform(1.0f));
}

TEST(GeoVector2Test, addOperatorAddsCorrectlyForGeoVector2)
{
    auto result = GeoVector2F::One() + GeoVector2F::One();
    EXPECT_EQ(result, GeoVector2F::Uniform(2.0f));
}

TEST(GeoVector2Test, subtractOperatorSubtractsCorrectlyForGeoVector2)
{
    auto result = GeoVector2F::One() - GeoVector2F::One();
    EXPECT_EQ(result, GeoVector2F::Zero());
}

TEST(GeoVector2Test, multiplyOperatorMultipliesCorrectlyForGeoVector2)
{
    auto result = GeoVector2F::Uniform(2.0f) * GeoVector2F::Uniform(2.0f);
    EXPECT_EQ(result, GeoVector2F::Uniform(4.0f));
}

TEST(GeoVector2Test, divideOperatorDividesCorrectlyForGeoVector2)
{
    auto result = GeoVector2F::Uniform(2.0f) / GeoVector2F::Uniform(2.0f);
    EXPECT_EQ(result, GeoVector2F::One());
}

TEST(GeoVector2Test, addOperatorAddsCorrectlyForTemplateType)
{
    auto result = GeoVector2F::One() + 1.0f;
    EXPECT_EQ(result, GeoVector2F::Uniform(2.0f));
}

TEST(GeoVector2Test, subtractOperatorSubtractsCorrectlyForTemplateType)
{
    auto result = GeoVector2F::One() - 1.0f;
    EXPECT_EQ(result, GeoVector2F::Zero());
}

TEST(GeoVector2Test, multiplyOperatorMultipliesCorrectlyForTemplateType)
{
    auto result = GeoVector2F::Uniform(2.0f) * 2.0f;
    EXPECT_EQ(result, GeoVector2F::Uniform(4.0f));
}

TEST(GeoVector2Test, multiplyOperatorMultipliesCorrectlyForTemplateTypeInverse)
{
    auto result = 2.0f * GeoVector2F::Uniform(2.0f);
    EXPECT_EQ(result, GeoVector2F::Uniform(4.0f));
}

TEST(GeoVector2Test, divideOperatorDividesCorrectlyForTemplateType)
{
    auto result = GeoVector2F::Uniform(2.0f) / 2.0f;
    EXPECT_EQ(result, GeoVector2F::One());
}

TEST(GeoVector2Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector2)
{
    auto result = GeoVector2F::One();
    result += GeoVector2F::One();
    EXPECT_EQ(result, GeoVector2F::Uniform(2.0f));
}

TEST(GeoVector2Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector2)
{
    auto result = GeoVector2F::One();
    result -= GeoVector2F::One();
    EXPECT_EQ(result, GeoVector2F::Zero());
}

TEST(GeoVector2Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector2)
{
    auto result = GeoVector2F::Uniform(2.0f);
    result *= GeoVector2F::Uniform(2.0f);
    EXPECT_EQ(result, GeoVector2F::Uniform(4.0f));
}

TEST(GeoVector2Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector2)
{
    auto result = GeoVector2F::Uniform(2.0f);
    result /= GeoVector2F::Uniform(2.0f);
    EXPECT_EQ(result, GeoVector2F::One());
}

TEST(GeoVector2Test, addAssignOperatorAddsAndAssignsCorrectlyForTemplateType)
{
    auto result = GeoVector2F::One();
    result += 1.0f;
    EXPECT_EQ(result, GeoVector2F::Uniform(2.0f));
}

TEST(GeoVector2Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForTemplateType)
{
    auto result = GeoVector2F::One();
    result -= 1.0f;
    EXPECT_EQ(result, GeoVector2F::Zero());
}

TEST(GeoVector2Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForTemplateType)
{
    auto result = GeoVector2F::Uniform(2.0f);
    result *= 2.0f;
    EXPECT_EQ(result, GeoVector2F::Uniform(4.0f));
}

TEST(GeoVector2Test, divideAssignOperatorDividesAndAssignsCorrectlyForTemplateType)
{
    auto result = GeoVector2F::Uniform(2.0f);
    result /= 2.0f;
    EXPECT_EQ(result, GeoVector2F::One());
}

TEST(GeoVector2Test, getNormalisedReturnsNormalisedGeoVector)
{
    auto vec = GeoVector2F::One().GetNormalised();
    float normalisedTotal = sqrtf(powf(vec.x, 2) + powf(vec.y, 2));
    EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(GeoVector2Test, getMagnitudeReturnsCorrectLength)
{
    auto vec = GeoVector2F::One().GetNormalised();
    EXPECT_FLOAT_EQ(vec.GetMagnitude(), sqrtf(powf(vec.x, 2) + powf(vec.y, 2)));
}

TEST(GeoVector2Test, getLengthReturnsCorrectLength)
{
    auto vec = GeoVector2F::One().GetNormalised();
    EXPECT_FLOAT_EQ(vec.GetLength(), sqrtf(powf(vec.x, 2) + powf(vec.y, 2)));
}

TEST(GeoVector2Test, rotateToAngleAroundPointRotatesCorrectAmount)
{
    auto vec = GeoVector2F(0.0f, 1.0f);
    vec.RotateToAngleAroundPoint(90.0f, GeoVector2F::Zero());
    EXPECT_TRUE(vec.EpsilonEquals(GeoVector2F(-1.0f, 0.0f), GeoVector2F::Uniform(1e-7f)));
}
