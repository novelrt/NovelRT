// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/NovelRT.h>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

class GeoMatrix4x4Test : public testing::Test
{
protected:
    GeoMatrix4x4F _dummyMatrix;

    void SetUp() override
    {
        _dummyMatrix = GeoMatrix4x4F(GeoVector4F(1.0f, 0.0f, 0.0f, 0.0f), GeoVector4F(0.0f, 1.0f, 0.0f, 0.0f),
                                     GeoVector4F(0.0f, 0.0f, 1.0f, 0.0f), GeoVector4F(0.0f, 0.0f, 0.0f, 1.0f));
    }
};

TEST_F(GeoMatrix4x4Test, equalityOperatorEvaluatesCorrectly)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::one(), GeoVector4F::one(), GeoVector4F::one(), GeoVector4F::one());

    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::one(), GeoVector4F::one(), GeoVector4F::one(), GeoVector4F::one());

    ASSERT_EQ(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, inequalityOperatorEvaluatesCorrectly)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::one(), GeoVector4F::one(), GeoVector4F::one(), GeoVector4F::one());

    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::zero(), GeoVector4F::zero(), GeoVector4F::zero(), GeoVector4F::zero());

    ASSERT_NE(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, getDefaultIdentityReturnsIdentityMatrix)
{
    ASSERT_EQ(GeoMatrix4x4F::getDefaultIdentity(), _dummyMatrix);
}

TEST_F(GeoMatrix4x4Test, addOperatorAddsCorrectlyForGeoMatrix4x4)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::one(), GeoVector4F::one(), GeoVector4F::one(), GeoVector4F::one());
    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::uniform(2.0f), GeoVector4F::uniform(2.0f), GeoVector4F::uniform(2.0f),
                                    GeoVector4F::uniform(2.0f));
    auto result = testMatOne + testMatOne;
    EXPECT_EQ(result, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, subtractOperatorSubtractsCorrectlyForGeoMatrix4x4)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::one(), GeoVector4F::one(), GeoVector4F::one(), GeoVector4F::one());
    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::zero(), GeoVector4F::zero(), GeoVector4F::zero(), GeoVector4F::zero());
    auto result = testMatOne - testMatOne;
    EXPECT_EQ(result, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, multiplyOperatorMultipliesCorrectlyForGeoMatrix4x4)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::uniform(2.0f), GeoVector4F::uniform(2.0f), GeoVector4F::uniform(2.0f),
                                    GeoVector4F::uniform(2.0f));
    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::uniform(16.0f), GeoVector4F::uniform(16.0f),
                                    GeoVector4F::uniform(16.0f), GeoVector4F::uniform(16.0f));
    auto result = testMatOne * testMatOne;
    EXPECT_EQ(result, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, addAssignOperatorAddsCorrectlyForGeoMatrix4x4)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::one(), GeoVector4F::one(), GeoVector4F::one(), GeoVector4F::one());
    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::uniform(2.0f), GeoVector4F::uniform(2.0f), GeoVector4F::uniform(2.0f),
                                    GeoVector4F::uniform(2.0f));
    auto testMatThree = testMatOne;
    testMatOne += testMatThree;
    EXPECT_EQ(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, subtractAssignOperatorSubtractsCorrectlyForGeoMatrix4x4)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::one(), GeoVector4F::one(), GeoVector4F::one(), GeoVector4F::one());
    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::zero(), GeoVector4F::zero(), GeoVector4F::zero(), GeoVector4F::zero());
    auto testMatThree = testMatOne;
    testMatOne -= testMatThree;
    EXPECT_EQ(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, multiplyAssignOperatorMultipliesCorrectlyForGeoMatrix4x4)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::uniform(2.0f), GeoVector4F::uniform(2.0f), GeoVector4F::uniform(2.0f),
                                    GeoVector4F::uniform(2.0f));
    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::uniform(16.0f), GeoVector4F::uniform(16.0f),
                                    GeoVector4F::uniform(16.0f), GeoVector4F::uniform(16.0f));
    auto testMatThree = testMatOne;
    testMatOne *= testMatThree;
    EXPECT_EQ(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, addOperatorAddsCorrectlyForTemplateType)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::one(), GeoVector4F::one(), GeoVector4F::one(), GeoVector4F::one());
    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::uniform(2.0f), GeoVector4F::uniform(2.0f), GeoVector4F::uniform(2.0f),
                                    GeoVector4F::uniform(2.0f));
    auto result = testMatOne + 1.0f;
    EXPECT_EQ(result, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, subtractOperatorSubtractsCorrectlyForTemplateType)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::one(), GeoVector4F::one(), GeoVector4F::one(), GeoVector4F::one());
    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::zero(), GeoVector4F::zero(), GeoVector4F::zero(), GeoVector4F::zero());
    auto result = testMatOne - 1.0f;
    EXPECT_EQ(result, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, multiplyOperatorMultipliesCorrectlyForTemplateType)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::uniform(2.0f), GeoVector4F::uniform(2.0f), GeoVector4F::uniform(2.0f),
                                    GeoVector4F::uniform(2.0f));
    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::uniform(4.0f), GeoVector4F::uniform(4.0f), GeoVector4F::uniform(4.0f),
                                    GeoVector4F::uniform(4.0f));
    auto result = testMatOne * 2.0f;
    EXPECT_EQ(result, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, addAssignOperatorAddsCorrectlyForTemplateType)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::one(), GeoVector4F::one(), GeoVector4F::one(), GeoVector4F::one());
    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::uniform(2.0f), GeoVector4F::uniform(2.0f), GeoVector4F::uniform(2.0f),
                                    GeoVector4F::uniform(2.0f));
    testMatOne += 1.0f;
    EXPECT_EQ(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, subtractAssignOperatorSubtractsCorrectlyForTemplateType)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::one(), GeoVector4F::one(), GeoVector4F::one(), GeoVector4F::one());
    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::zero(), GeoVector4F::zero(), GeoVector4F::zero(), GeoVector4F::zero());
    testMatOne -= 1.0f;
    EXPECT_EQ(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, multiplyAssignOperatorMultipliesCorrectlyForTemplateType)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::uniform(2.0f), GeoVector4F::uniform(2.0f), GeoVector4F::uniform(2.0f),
                                    GeoVector4F::uniform(2.0f));
    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::uniform(4.0f), GeoVector4F::uniform(4.0f), GeoVector4F::uniform(4.0f),
                                    GeoVector4F::uniform(4.0f));
    testMatOne *= 2.0f;
    EXPECT_EQ(testMatOne, testMatTwo);
}
