// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Timing/NrtTimestamp.h>
#include <NovelRT/NovelRT.h>

#include <gtest/gtest.h>

using namespace NovelRT;

class InteropTimestampTest : public testing::Test
{
protected:
    NrtTimestamp _timestamp;

    void SetUp() override
    {
        _timestamp = Nrt_Timestamp_Create(Timing::TicksPerSecond);
    }

public:
    InteropTimestampTest() : _timestamp(Nrt_Timestamp_Create(0))
    {
    }
};

TEST_F(InteropTimestampTest, GetTicksShouldReturnCorrectValue)
{
    ASSERT_EQ(_timestamp, Timing::TicksPerSecond);
}

TEST_F(InteropTimestampTest, GetSecondsDoubleShouldReturnCorrectValue)
{
    ASSERT_DOUBLE_EQ(Nrt_Timestamp_GetSecondsDouble(_timestamp), 1.0);
}

TEST_F(InteropTimestampTest, GetSecondsFloatShouldReturnCorrectValue)
{
    ASSERT_FLOAT_EQ(Nrt_Timestamp_GetSecondsFloat(_timestamp), 1.0f);
}

TEST_F(InteropTimestampTest, AddOperatorAddsCorrectly)
{
    NrtTimestamp result = Nrt_Timestamp_AddTimestamp(Nrt_Timestamp_Create(0), Nrt_Timestamp_Create(1));
    ASSERT_EQ(result, 1);
}

TEST_F(InteropTimestampTest, SubtractOperatorSubtractsCorrectly)
{
    NrtTimestamp result = Nrt_Timestamp_SubtractTimestamp(Nrt_Timestamp_Create(1), Nrt_Timestamp_Create(1));
    ASSERT_EQ(result, 0);
}

TEST_F(InteropTimestampTest, MultiplyOperatorMultipliesCorrectly)
{
    NrtTimestamp result = Nrt_Timestamp_MultiplyTimestamp(Nrt_Timestamp_Create(2), Nrt_Timestamp_Create(2));
    ASSERT_EQ(result, 4);
}

TEST_F(InteropTimestampTest, DivideOperatorDividesCorrectly)
{
    NrtTimestamp result = Nrt_Timestamp_DivideTimestamp(Nrt_Timestamp_Create(2), Nrt_Timestamp_Create(2));
    ASSERT_EQ(result, 1);
}

TEST_F(InteropTimestampTest, AddAssignOperatorAddsAndAssignsCorrectly)
{
    NrtTimestamp result = Nrt_Timestamp_Create(0);
    Nrt_Timestamp_AddAssignTimestamp(&result, Nrt_Timestamp_Create(1));
    ASSERT_EQ(result, 1);
}

TEST_F(InteropTimestampTest, SubtractAssignOperatorSubtractsAndAssignsCorrectly)
{
    NrtTimestamp result = Nrt_Timestamp_Create(1);
    Nrt_Timestamp_SubtractAssignTimestamp(&result, Nrt_Timestamp_Create(1));
    ASSERT_EQ(result, 0);
}

TEST_F(InteropTimestampTest, MultiplyAssignOperatorMultipliesAndAssignsCorrectly)
{
    NrtTimestamp result = Nrt_Timestamp_Create(2);
    Nrt_Timestamp_MultiplyAssignTimestamp(&result, Nrt_Timestamp_Create(2));
    ASSERT_EQ(result, 4);
}

TEST_F(InteropTimestampTest, DivideAssignOperatorDividesAndAssignsCorrectly)
{
    NrtTimestamp result = Nrt_Timestamp_Create(2);
    Nrt_Timestamp_DivideAssignTimestamp(&result, Nrt_Timestamp_Create(2));
    ASSERT_EQ(result, 1);
}

TEST_F(InteropTimestampTest, EqualityOperatorEvaluatesCorrectly)
{
    ASSERT_EQ(_timestamp, Nrt_Timestamp_Create(Timing::TicksPerSecond));
}

TEST_F(InteropTimestampTest, InequalityOperatorEvaluatesCorrectly)
{
    ASSERT_NE(_timestamp, Nrt_Timestamp_Create(0));
}
