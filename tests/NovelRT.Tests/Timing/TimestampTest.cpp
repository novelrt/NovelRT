// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>

using namespace NovelRT;
using namespace NovelRT::Timing;

class TimestampTest : public testing::Test {
protected:
  Timestamp _timeStamp;

  void SetUp() override {
    _timeStamp = Timestamp(TicksPerSecond);
  }
public:
  TimestampTest() : _timeStamp(Timestamp(0ULL)) {}
};

TEST_F(TimestampTest, GetTicksShouldReturnCorrectValue) {
  ASSERT_EQ(_timeStamp.getTicks(), TicksPerSecond);
}

TEST_F(TimestampTest, GetSecondsDoubleShouldReturnCorrectValue) {
  ASSERT_DOUBLE_EQ(_timeStamp.getSecondsDouble(), 1.0);
}

TEST_F(TimestampTest, GetSecondsFloatShouldReturnCorrectValue) {
  ASSERT_FLOAT_EQ(_timeStamp.getSecondsFloat(), 1.0f);
}

TEST_F(TimestampTest, AddOperatorAddsCorrectly) {
  auto result = Timestamp(0ULL) + Timestamp(1ULL);
  ASSERT_EQ(result.getTicks(), 1ULL);
}

TEST_F(TimestampTest, SubtractOperatorSubtractsCorrectly) {
  auto result = Timestamp(1ULL) - Timestamp(1ULL);
  ASSERT_EQ(result.getTicks(), 0ULL);
}

TEST_F(TimestampTest, MultiplyOperatorMultipliesCorrectly) {
  auto result = Timestamp(2ULL) * Timestamp(2ULL);
  ASSERT_EQ(result.getTicks(), 4ULL);
}

TEST_F(TimestampTest, DivideOperatorDividesCorrectly) {
  auto result = Timestamp(2ULL) / Timestamp(2ULL);
  ASSERT_EQ(result.getTicks(), 1ULL);
}

TEST_F(TimestampTest, AddAssignOperatorAddsAndAssignsCorrectly) {
  auto result = Timestamp(0ULL);
  result += Timestamp(1ULL);
  ASSERT_EQ(result.getTicks(), 1ULL);
}

TEST_F(TimestampTest, SubtractAssignOperatorSubtractsAndAssignsCorrectly) {
  auto result = Timestamp(1ULL);
  result -= Timestamp(1ULL);
  ASSERT_EQ(result.getTicks(), 0ULL);
}

TEST_F(TimestampTest, MultiplyAssignOperatorMultipliesAndAssignsCorrectly) {
  auto result = Timestamp(2ULL);
  result *= Timestamp(2ULL);
  ASSERT_EQ(result.getTicks(), 4ULL);
}

TEST_F(TimestampTest, DivideAssignOperatorDividesAndAssignsCorrectly) {
  auto result = Timestamp(2ULL);
  result /= Timestamp(2ULL);
  ASSERT_EQ(result.getTicks(), 1ULL);
}
