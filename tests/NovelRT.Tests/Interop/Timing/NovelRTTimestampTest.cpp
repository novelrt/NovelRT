#include <NovelRT.Interop/Timing/NovelRTTimestamp.h>
#include <NovelRT.h>
#include <gtest/gtest.h>

using namespace NovelRT;

class InteropTimestampTest : public testing::Test {
protected:
  NovelRTTimestamp _timestamp;

  void SetUp() override {
    _timestamp = NovelRT_Timestamp_create(Timing::TicksPerSecond);
  }
public:
  InteropTimestampTest() : _timestamp(NovelRT_Timestamp_create(0)) {}
};

TEST_F(InteropTimestampTest, GetTicksShouldReturnCorrectValue) {
  ASSERT_EQ(_timestamp, Timing::TicksPerSecond);
}

TEST_F(InteropTimestampTest, GetSecondsDoubleShouldReturnCorrectValue) {
  ASSERT_DOUBLE_EQ(NovelRT_Timestamp_getSecondsDouble(_timestamp), 1.0);
}

TEST_F(InteropTimestampTest, GetSecondsFloatShouldReturnCorrectValue) {
  ASSERT_FLOAT_EQ(NovelRT_Timestamp_getSecondsFloat(_timestamp), 1.0f);
}

TEST_F(InteropTimestampTest, AddOperatorAddsCorrectly) {
  NovelRTTimestamp result = NULL;
  NovelRT_Timestamp_addTimestamp(NovelRT_Timestamp_create(0), NovelRT_Timestamp_create(1), &result, nullptr);
  ASSERT_EQ(result, 1);
}

TEST_F(InteropTimestampTest, SubtractOperatorSubtractsCorrectly) {
  NovelRTTimestamp result = NULL;
  NovelRT_Timestamp_subtractTimestamp(NovelRT_Timestamp_create(1), NovelRT_Timestamp_create(1), &result, nullptr);
  ASSERT_EQ(result, 0);
}

TEST_F(InteropTimestampTest, MultiplyOperatorMultipliesCorrectly) {
  NovelRTTimestamp result = NULL;
  NovelRT_Timestamp_multiplyTimestamp(NovelRT_Timestamp_create(2), NovelRT_Timestamp_create(2), &result, nullptr);
  ASSERT_EQ(result, 4);
}

TEST_F(InteropTimestampTest, DivideOperatorDividesCorrectly) {
  NovelRTTimestamp result = NULL;
  NovelRT_Timestamp_divideTimestamp(NovelRT_Timestamp_create(2), NovelRT_Timestamp_create(2), &result, nullptr);
  ASSERT_EQ(result, 1);
}

TEST_F(InteropTimestampTest, AddAssignOperatorAddsAndAssignsCorrectly) {
  auto result = NovelRT_Timestamp_create(0);
  NovelRT_Timestamp_addAssignTimestamp(&result, NovelRT_Timestamp_create(1), nullptr);
  ASSERT_EQ(result, 1);
}

TEST_F(InteropTimestampTest, SubtractAssignOperatorSubtractsAndAssignsCorrectly) {
  auto result = NovelRT_Timestamp_create(1);
  NovelRT_Timestamp_subtractAssignTimestamp(&result, NovelRT_Timestamp_create(1), nullptr);
  ASSERT_EQ(result, 0);
}

TEST_F(InteropTimestampTest, MultiplyAssignOperatorMultipliesAndAssignsCorrectly) {
  auto result = NovelRT_Timestamp_create(2);
  NovelRT_Timestamp_multiplyAssignTimestamp(&result, NovelRT_Timestamp_create(2), nullptr);
  ASSERT_EQ(result, 4);
}

TEST_F(InteropTimestampTest, DivideAssignOperatorDividesAndAssignsCorrectly) {
  auto result = NovelRT_Timestamp_create(2);
  NovelRT_Timestamp_divideAssignTimestamp(&result, NovelRT_Timestamp_create(2), nullptr);
  ASSERT_EQ(result, 1);
}

TEST_F(InteropTimestampTest, EqualityOperatorEvaluatesCorrectly) {
  ASSERT_EQ(_timestamp, NovelRT_Timestamp_create(Timing::TicksPerSecond));
}

TEST_F(InteropTimestampTest, InequalityOperatorEvaluatesCorrectly) {
  ASSERT_NE(_timestamp, NovelRT_Timestamp_create(0));
}

