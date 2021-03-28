// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Timing/NrtTimestamp.h>
#include <NovelRT.h>

#include <gtest/gtest.h>

using namespace NovelRT;

class InteropTimestampTest : public testing::Test
{
protected:
    NrtTimestamp _timestamp;

    void SetUp() override
    {
        _timestamp = Nrt_Timestamp_create(Timing::TicksPerSecond);
    }

public:
    InteropTimestampTest() : _timestamp(Nrt_Timestamp_create(0))
    {
    }
};

TEST_F(InteropTimestampTest, GetTicksShouldReturnCorrectValue)
{
    ASSERT_EQ(_timestamp, Timing::TicksPerSecond);
}

TEST_F(InteropTimestampTest, GetSecondsDoubleShouldReturnCorrectValue)
{
    ASSERT_DOUBLE_EQ(Nrt_Timestamp_getSecondsDouble(_timestamp), 1.0);
}

TEST_F(InteropTimestampTest, GetSecondsFloatShouldReturnCorrectValue)
{
    ASSERT_FLOAT_EQ(Nrt_Timestamp_getSecondsFloat(_timestamp), 1.0f);
}

TEST_F(InteropTimestampTest, AddOperatorAddsCorrectly)
{
    NrtTimestamp result = Nrt_Timestamp_addTimestamp(Nrt_Timestamp_create(0), Nrt_Timestamp_create(1));
    ASSERT_EQ(result, 1);
}

TEST_F(InteropTimestampTest, SubtractOperatorSubtractsCorrectly)
{
    NrtTimestamp result = Nrt_Timestamp_subtractTimestamp(Nrt_Timestamp_create(1), Nrt_Timestamp_create(1));
    ASSERT_EQ(result, 0);
}

TEST_F(InteropTimestampTest, MultiplyOperatorMultipliesCorrectly)
{
    NrtTimestamp result = Nrt_Timestamp_multiplyTimestamp(Nrt_Timestamp_create(2), Nrt_Timestamp_create(2));
    ASSERT_EQ(result, 4);
}

TEST_F(InteropTimestampTest, DivideOperatorDividesCorrectly)
{
    NrtTimestamp result = Nrt_Timestamp_divideTimestamp(Nrt_Timestamp_create(2), Nrt_Timestamp_create(2));
    ASSERT_EQ(result, 1);
}

TEST_F(InteropTimestampTest, AddAssignOperatorAddsAndAssignsCorrectly)
{
    NrtTimestamp result = Nrt_Timestamp_create(0);
    Nrt_Timestamp_addAssignTimestamp(&result, Nrt_Timestamp_create(1));
    ASSERT_EQ(result, 1);
}

TEST_F(InteropTimestampTest, SubtractAssignOperatorSubtractsAndAssignsCorrectly)
{
    NrtTimestamp result = Nrt_Timestamp_create(1);
    Nrt_Timestamp_subtractAssignTimestamp(&result, Nrt_Timestamp_create(1));
    ASSERT_EQ(result, 0);
}

TEST_F(InteropTimestampTest, MultiplyAssignOperatorMultipliesAndAssignsCorrectly)
{
    NrtTimestamp result = Nrt_Timestamp_create(2);
    Nrt_Timestamp_multiplyAssignTimestamp(&result, Nrt_Timestamp_create(2));
    ASSERT_EQ(result, 4);
}

TEST_F(InteropTimestampTest, DivideAssignOperatorDividesAndAssignsCorrectly)
{
    NrtTimestamp result = Nrt_Timestamp_create(2);
    Nrt_Timestamp_divideAssignTimestamp(&result, Nrt_Timestamp_create(2));
    ASSERT_EQ(result, 1);
}

TEST_F(InteropTimestampTest, EqualityOperatorEvaluatesCorrectly)
{
    ASSERT_EQ(_timestamp, Nrt_Timestamp_create(Timing::TicksPerSecond));
}

TEST_F(InteropTimestampTest, InequalityOperatorEvaluatesCorrectly)
{
    ASSERT_NE(_timestamp, Nrt_Timestamp_create(0));
}
