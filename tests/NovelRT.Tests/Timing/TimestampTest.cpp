// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>

using namespace NovelRT;
using namespace NovelRT::Timing;

class TimestampTest : public testing::Test {
protected:
  Timestamp _timestamp;

  void SetUp() override {
    _timestamp = Timestamp(TicksPerSecond);
  }
public:
  TimestampTest() : _timestamp(Timestamp(0)) {}
};

TEST_F(TimestampTest, GetTicksShouldReturnCorrectValue) {
  ASSERT_EQ(_timestamp.ticks, TicksPerSecond);
}

TEST_F(TimestampTest, GetSecondsDoubleShouldReturnCorrectValue) {
  ASSERT_DOUBLE_EQ(_timestamp.getSecondsDouble(), 1.0);
}

TEST_F(TimestampTest, GetSecondsFloatShouldReturnCorrectValue) {
  ASSERT_FLOAT_EQ(_timestamp.getSecondsFloat(), 1.0f);
}

TEST_F(TimestampTest, AddOperatorAddsCorrectly) {
  auto result = Timestamp(0) + Timestamp(1);
  ASSERT_EQ(result.ticks, 1);
}

TEST_F(TimestampTest, SubtractOperatorSubtractsCorrectly) {
  auto result = Timestamp(1) - Timestamp(1);
  ASSERT_EQ(result.ticks, 0);
}

TEST_F(TimestampTest, MultiplyOperatorMultipliesCorrectly) {
  auto result = Timestamp(2) * Timestamp(2);
  ASSERT_EQ(result.ticks, 4);
}

TEST_F(TimestampTest, DivideOperatorDividesCorrectly) {
  auto result = Timestamp(2) / Timestamp(2);
  ASSERT_EQ(result.ticks, 1);
}

TEST_F(TimestampTest, AddAssignOperatorAddsAndAssignsCorrectly) {
  auto result = Timestamp(0);
  result += Timestamp(1);
  ASSERT_EQ(result.ticks, 1);
}

TEST_F(TimestampTest, SubtractAssignOperatorSubtractsAndAssignsCorrectly) {
  auto result = Timestamp(1);
  result -= Timestamp(1);
  ASSERT_EQ(result.ticks, 0);
}

TEST_F(TimestampTest, MultiplyAssignOperatorMultipliesAndAssignsCorrectly) {
  auto result = Timestamp(2);
  result *= Timestamp(2);
  ASSERT_EQ(result.ticks, 4);
}

TEST_F(TimestampTest, DivideAssignOperatorDividesAndAssignsCorrectly) {
  auto result = Timestamp(2);
  result /= Timestamp(2);
  ASSERT_EQ(result.ticks, 1);
}

TEST_F(TimestampTest, EqualityOperatorEvaluatesCorrectly) {
  ASSERT_EQ(_timestamp, Timestamp(TicksPerSecond));
}

TEST_F(TimestampTest, InequalityOperatorEvaluatesCorrectly) {
  ASSERT_NE(_timestamp, Timestamp(0));
}
