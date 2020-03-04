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
  TimestampTest::TimestampTest() : _timeStamp(Timestamp(0)) {}
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
