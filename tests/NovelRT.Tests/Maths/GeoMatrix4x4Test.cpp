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

TEST_F(GeoMatrix4x4Test, EqualityOperatorEvaluatesCorrectly)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::One(), GeoVector4F::One(), GeoVector4F::One(), GeoVector4F::One());

    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::One(), GeoVector4F::One(), GeoVector4F::One(), GeoVector4F::One());

    ASSERT_EQ(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, InequalityOperatorEvaluatesCorrectly)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::One(), GeoVector4F::One(), GeoVector4F::One(), GeoVector4F::One());

    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::Zero(), GeoVector4F::Zero(), GeoVector4F::Zero(), GeoVector4F::Zero());

    ASSERT_NE(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, GetDefaultIdentityReturnsIdentityMatrix)
{
    ASSERT_EQ(GeoMatrix4x4F::GetDefaultIdentity(), _dummyMatrix);
}

TEST_F(GeoMatrix4x4Test, AddOperatorAddsCorrectlyForGeoMatrix4x4)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::One(), GeoVector4F::One(), GeoVector4F::One(), GeoVector4F::One());
    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::Uniform(2.0f), GeoVector4F::Uniform(2.0f), GeoVector4F::Uniform(2.0f),
                                    GeoVector4F::Uniform(2.0f));
    auto result = testMatOne + testMatOne;
    EXPECT_EQ(result, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, SubtractOperatorSubtractsCorrectlyForGeoMatrix4x4)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::One(), GeoVector4F::One(), GeoVector4F::One(), GeoVector4F::One());
    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::Zero(), GeoVector4F::Zero(), GeoVector4F::Zero(), GeoVector4F::Zero());
    auto result = testMatOne - testMatOne;
    EXPECT_EQ(result, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, MultiplyOperatorMultipliesCorrectlyForGeoMatrix4x4)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::Uniform(2.0f), GeoVector4F::Uniform(2.0f), GeoVector4F::Uniform(2.0f),
                                    GeoVector4F::Uniform(2.0f));
    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::Uniform(16.0f), GeoVector4F::Uniform(16.0f),
                                    GeoVector4F::Uniform(16.0f), GeoVector4F::Uniform(16.0f));
    auto result = testMatOne * testMatOne;
    EXPECT_EQ(result, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, AddAssignOperatorAddsCorrectlyForGeoMatrix4x4)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::One(), GeoVector4F::One(), GeoVector4F::One(), GeoVector4F::One());
    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::Uniform(2.0f), GeoVector4F::Uniform(2.0f), GeoVector4F::Uniform(2.0f),
                                    GeoVector4F::Uniform(2.0f));
    auto testMatThree = testMatOne;
    testMatOne += testMatThree;
    EXPECT_EQ(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, SubtractAssignOperatorSubtractsCorrectlyForGeoMatrix4x4)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::One(), GeoVector4F::One(), GeoVector4F::One(), GeoVector4F::One());
    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::Zero(), GeoVector4F::Zero(), GeoVector4F::Zero(), GeoVector4F::Zero());
    auto testMatThree = testMatOne;
    testMatOne -= testMatThree;
    EXPECT_EQ(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, MultiplyAssignOperatorMultipliesCorrectlyForGeoMatrix4x4)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::Uniform(2.0f), GeoVector4F::Uniform(2.0f), GeoVector4F::Uniform(2.0f),
                                    GeoVector4F::Uniform(2.0f));
    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::Uniform(16.0f), GeoVector4F::Uniform(16.0f),
                                    GeoVector4F::Uniform(16.0f), GeoVector4F::Uniform(16.0f));
    auto testMatThree = testMatOne;
    testMatOne *= testMatThree;
    EXPECT_EQ(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, AddOperatorAddsCorrectlyForTemplateType)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::One(), GeoVector4F::One(), GeoVector4F::One(), GeoVector4F::One());
    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::Uniform(2.0f), GeoVector4F::Uniform(2.0f), GeoVector4F::Uniform(2.0f),
                                    GeoVector4F::Uniform(2.0f));
    auto result = testMatOne + 1.0f;
    EXPECT_EQ(result, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, SubtractOperatorSubtractsCorrectlyForTemplateType)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::One(), GeoVector4F::One(), GeoVector4F::One(), GeoVector4F::One());
    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::Zero(), GeoVector4F::Zero(), GeoVector4F::Zero(), GeoVector4F::Zero());
    auto result = testMatOne - 1.0f;
    EXPECT_EQ(result, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, MultiplyOperatorMultipliesCorrectlyForTemplateType)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::Uniform(2.0f), GeoVector4F::Uniform(2.0f), GeoVector4F::Uniform(2.0f),
                                    GeoVector4F::Uniform(2.0f));
    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::Uniform(4.0f), GeoVector4F::Uniform(4.0f), GeoVector4F::Uniform(4.0f),
                                    GeoVector4F::Uniform(4.0f));
    auto result = testMatOne * 2.0f;
    EXPECT_EQ(result, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, AddAssignOperatorAddsCorrectlyForTemplateType)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::One(), GeoVector4F::One(), GeoVector4F::One(), GeoVector4F::One());
    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::Uniform(2.0f), GeoVector4F::Uniform(2.0f), GeoVector4F::Uniform(2.0f),
                                    GeoVector4F::Uniform(2.0f));
    testMatOne += 1.0f;
    EXPECT_EQ(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, SubtractAssignOperatorSubtractsCorrectlyForTemplateType)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::One(), GeoVector4F::One(), GeoVector4F::One(), GeoVector4F::One());
    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::Zero(), GeoVector4F::Zero(), GeoVector4F::Zero(), GeoVector4F::Zero());
    testMatOne -= 1.0f;
    EXPECT_EQ(testMatOne, testMatTwo);
}

TEST_F(GeoMatrix4x4Test, MultiplyAssignOperatorMultipliesCorrectlyForTemplateType)
{
    auto testMatOne = GeoMatrix4x4F(GeoVector4F::Uniform(2.0f), GeoVector4F::Uniform(2.0f), GeoVector4F::Uniform(2.0f),
                                    GeoVector4F::Uniform(2.0f));
    auto testMatTwo = GeoMatrix4x4F(GeoVector4F::Uniform(4.0f), GeoVector4F::Uniform(4.0f), GeoVector4F::Uniform(4.0f),
                                    GeoVector4F::Uniform(4.0f));
    testMatOne *= 2.0f;
    EXPECT_EQ(testMatOne, testMatTwo);
}
