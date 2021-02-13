// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(GeoVector3Test, equalityOperatorEvaluatesCorrectly)
{
    EXPECT_EQ(GeoVector3F(0.0f, 0.0f, 0.0f), GeoVector3F(0.0f, 0.0f, 0.0f));
}

TEST(GeoVector3Test, inequalityOperatorEvaluatesCorrectly)
{
    EXPECT_NE(GeoVector3F(0.0f, 0.0f, 0.0f), GeoVector3F(1.0f, 0.0f, 0.0f));
}

TEST(GeoVector3Test, lessThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(GeoVector3F(0.0f, 0.0f, 0.0f) < GeoVector3F(1.0f, 1.0f, 1.0f));
}

TEST(GeoVector3Test, lessOrEqualToThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(GeoVector3F(0.0f, 0.0f, 0.0f) <= GeoVector3F(1.0f, 1.0f, 1.0f));
    EXPECT_TRUE(GeoVector3F(1.0f, 1.0f, 1.0f) <= GeoVector3F(1.0f, 1.0f, 1.0f));
}

TEST(GeoVector3Test, greaterThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(GeoVector3F(1.0f, 1.0f, 1.0f) > GeoVector3F(0.0f, 0.0f, 0.0f));
}

TEST(GeoVector3Test, greaterThanOrEqualToOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(GeoVector3F(1.0f, 1.0f, 1.0f) >= GeoVector3F(0.0f, 0.0f, 0.0f));
    EXPECT_TRUE(GeoVector3F(1.0f, 1.0f, 1.0f) >= GeoVector3F(1.0f, 1.0f, 1.0f));
}

TEST(GeoVector3Test, staticUniformCallReturnsGeoVector3WithUniformValues)
{
    EXPECT_EQ(GeoVector3F::uniform(1.0f), GeoVector3F(1.0f, 1.0f, 1.0f));
}

TEST(GeoVector3Test, staticZeroCallReturnsGeoVector3Zero)
{
    EXPECT_EQ(GeoVector3F::zero(), GeoVector3F::uniform(0.0f));
}

TEST(GeoVector3Test, staticOneCallReturnsGeoVector3One)
{
    EXPECT_EQ(GeoVector3F::one(), GeoVector3F::uniform(1.0f));
}

TEST(GeoVector3Test, addOperatorAddsCorrectlyForGeoVector3)
{
    auto result = GeoVector3F::one() + GeoVector3F::one();
    EXPECT_EQ(result, GeoVector3F::uniform(2.0f));
}

TEST(GeoVector3Test, subtractOperatorSubtractsCorrectlyForGeoVector3)
{
    auto result = GeoVector3F::one() - GeoVector3F::one();
    EXPECT_EQ(result, GeoVector3F::zero());
}

TEST(GeoVector3Test, multiplyOperatorMultipliesCorrectlyForGeoVector3)
{
    auto result = GeoVector3F::uniform(2.0f) * GeoVector3F::uniform(2.0f);
    EXPECT_EQ(result, GeoVector3F::uniform(4.0f));
}

TEST(GeoVector3Test, divideOperatorDividesCorrectlyForGeoVector3)
{
    auto result = GeoVector3F::uniform(2.0f) / GeoVector3F::uniform(2.0f);
    EXPECT_EQ(result, GeoVector3F::one());
}

TEST(GeoVector3Test, addOperatorAddsCorrectlyForTemplateType)
{
    auto result = GeoVector3F::one() + 1.0f;
    EXPECT_EQ(result, GeoVector3F::uniform(2.0f));
}

TEST(GeoVector3Test, subtractOperatorSubtractsCorrectlyForTemplateType)
{
    auto result = GeoVector3F::one() - 1.0f;
    EXPECT_EQ(result, GeoVector3F::zero());
}

TEST(GeoVector3Test, multiplyOperatorMultipliesCorrectlyForTemplateType)
{
    auto result = GeoVector3F::uniform(2.0f) * 2.0f;
    EXPECT_EQ(result, GeoVector3F::uniform(4.0f));
}

TEST(GeoVector3Test, multiplyOperatorMultipliesCorrectlyForTemplateTypeInverse)
{
    auto result = 2.0f * GeoVector3F::uniform(2.0f);
    EXPECT_EQ(result, GeoVector3F::uniform(4.0f));
}

TEST(GeoVector3Test, divideOperatorDividesCorrectlyForTemplateType)
{
    auto result = GeoVector3F::uniform(2.0f) / 2.0f;
    EXPECT_EQ(result, GeoVector3F::one());
}

TEST(GeoVector3Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector3)
{
    auto result = GeoVector3F::one();
    result += GeoVector3F::one();
    EXPECT_EQ(result, GeoVector3F::uniform(2.0f));
}

TEST(GeoVector3Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector3)
{
    auto result = GeoVector3F::one();
    result -= GeoVector3F::one();
    EXPECT_EQ(result, GeoVector3F::zero());
}

TEST(GeoVector3Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector3)
{
    auto result = GeoVector3F::uniform(2.0f);
    result *= GeoVector3F::uniform(2.0f);
    EXPECT_EQ(result, GeoVector3F::uniform(4.0f));
}

TEST(GeoVector3Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector3)
{
    auto result = GeoVector3F::uniform(2.0f);
    result /= GeoVector3F::uniform(2.0f);
    EXPECT_EQ(result, GeoVector3F::one());
}

TEST(GeoVector3Test, addAssignOperatorAddsAndAssignsCorrectlyForTemplateType)
{
    auto result = GeoVector3F::one();
    result += 1.0f;
    EXPECT_EQ(result, GeoVector3F::uniform(2.0f));
}

TEST(GeoVector3Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForTemplateType)
{
    auto result = GeoVector3F::one();
    result -= 1.0f;
    EXPECT_EQ(result, GeoVector3F::zero());
}

TEST(GeoVector3Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForTemplateType)
{
    auto result = GeoVector3F::uniform(2.0f);
    result *= 2.0f;
    EXPECT_EQ(result, GeoVector3F::uniform(4.0f));
}

TEST(GeoVector3Test, divideAssignOperatorDividesAndAssignsCorrectlyForTemplateType)
{
    auto result = GeoVector3F::uniform(2.0f);
    result /= 2.0f;
    EXPECT_EQ(result, GeoVector3F::one());
}

TEST(GeoVector3Test, getNormalisedReturnsNormalisedGeoVector)
{
    auto vec = GeoVector3F::one().getNormalised();
    float normalisedTotal = sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2));
    EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(GeoVector3Test, getMagnitudeReturnsCorrectLength)
{
    auto vec = GeoVector3F::one().getNormalised();
    EXPECT_FLOAT_EQ(vec.getMagnitude(), sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2)));
}

TEST(GeoVector3Test, getLengthReturnsCorrectLength)
{
    auto vec = GeoVector3F::one().getNormalised();
    EXPECT_FLOAT_EQ(vec.getLength(), sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2)));
}

TEST(GeoVector3Test, rotateToAngleAroundPointRotatesCorrectAmount)
{
    auto vec = GeoVector3F(0.0f, 1.0f, 0.0f);
    vec.rotateToAngleAroundPoint(90.0f, GeoVector3F::zero());
    EXPECT_TRUE(vec.epsilonEquals(GeoVector3F(-1.0f, 0.0f, 0.0f), GeoVector3F::uniform(1e-7f)));
}

TEST(GeoVector3Test, geoVector2ConstructorReturnsCorrectGeoVector3)
{
    EXPECT_EQ(GeoVector3F(GeoVector2F::one()), GeoVector3F(1.0f, 1.0f, 0.0f));
}
