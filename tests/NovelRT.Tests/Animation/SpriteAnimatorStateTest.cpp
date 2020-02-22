// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>

using namespace NovelRT;
using namespace NovelRT::Maths;
using namespace NovelRT::Animation;

class SpriteAnimatorStateTest : public testing::Test {
protected:
  std::vector<std::shared_ptr<SpriteAnimatorState>> _states;

  void SetUp() override {
    _states = std::vector<std::shared_ptr<SpriteAnimatorState>>{
      std::make_shared<SpriteAnimatorState>(),
      std::make_shared<SpriteAnimatorState>(),
      std::make_shared<SpriteAnimatorState>(),
      std::make_shared<SpriteAnimatorState>(),
      std::make_shared<SpriteAnimatorState>(),
    };
  }
};

void setUpRelationships(std::vector<std::shared_ptr<SpriteAnimatorState>> targets, std::vector<std::function<bool()>> conditions = std::vector<std::function<bool()>>()) {
  for (size_t i = 0; i < targets.size(); i++) {
    auto nextTarget = (i + 1 >= targets.size()) ? 0 : i + 1;
    targets.at(i)->insertNewState(targets.at(nextTarget), conditions);
  }
}

TEST_F(SpriteAnimatorStateTest, tryFindValidTransitionReturnsNullptrWhenNoRelationships) {
  EXPECT_EQ(_states.at(0)->tryFindValidTransition(), nullptr);
}

TEST_F(SpriteAnimatorStateTest, tryFindValidTransitionReturnsSpriteAnimatorStateWhenNoConditions) {
  setUpRelationships(_states);

  EXPECT_EQ(_states.at(0)->tryFindValidTransition(), _states.at(1));
  EXPECT_EQ(_states.at(1)->tryFindValidTransition(), _states.at(2));
  EXPECT_EQ(_states.at(2)->tryFindValidTransition(), _states.at(3));
  EXPECT_EQ(_states.at(3)->tryFindValidTransition(), _states.at(4));
  EXPECT_EQ(_states.at(4)->tryFindValidTransition(), _states.at(0));
}

TEST_F(SpriteAnimatorStateTest, tryFindValidTransitionReturnsSpriteAnimatorStateWhenAllConditionsTrue) {
  setUpRelationships(_states, std::vector<std::function<bool()>>{[] { return true; }});

  EXPECT_EQ(_states.at(0)->tryFindValidTransition(), _states.at(1));
  EXPECT_EQ(_states.at(1)->tryFindValidTransition(), _states.at(2));
  EXPECT_EQ(_states.at(2)->tryFindValidTransition(), _states.at(3));
  EXPECT_EQ(_states.at(3)->tryFindValidTransition(), _states.at(4));
  EXPECT_EQ(_states.at(4)->tryFindValidTransition(), _states.at(0));
}

TEST_F(SpriteAnimatorStateTest, tryFindValidTransitionReturnsNullptrWhenAllConditionsFalse) {
  setUpRelationships(_states, std::vector<std::function<bool()>>{[] { return false; }});

  EXPECT_EQ(_states.at(0)->tryFindValidTransition(), nullptr);
  EXPECT_EQ(_states.at(1)->tryFindValidTransition(), nullptr);
  EXPECT_EQ(_states.at(2)->tryFindValidTransition(), nullptr);
  EXPECT_EQ(_states.at(3)->tryFindValidTransition(), nullptr);
  EXPECT_EQ(_states.at(4)->tryFindValidTransition(), nullptr);
}

TEST_F(SpriteAnimatorStateTest, tryFindValidTransitionReturnsSpriteAnimatorStateWhenAllMultipleConditionsTrue) {
  setUpRelationships(_states, std::vector<std::function<bool()>>{[] { return true; }, [] { return true; }});

  EXPECT_EQ(_states.at(0)->tryFindValidTransition(), _states.at(1));
  EXPECT_EQ(_states.at(1)->tryFindValidTransition(), _states.at(2));
  EXPECT_EQ(_states.at(2)->tryFindValidTransition(), _states.at(3));
  EXPECT_EQ(_states.at(3)->tryFindValidTransition(), _states.at(4));
  EXPECT_EQ(_states.at(4)->tryFindValidTransition(), _states.at(0));
}

TEST_F(SpriteAnimatorStateTest, tryFindValidTransitionReturnsNullptrWhenAllMultipleConditionsFalse) {
  setUpRelationships(_states, std::vector<std::function<bool()>>{[] { return false; }, [] { return false; }});

  EXPECT_EQ(_states.at(0)->tryFindValidTransition(), nullptr);
  EXPECT_EQ(_states.at(1)->tryFindValidTransition(), nullptr);
  EXPECT_EQ(_states.at(2)->tryFindValidTransition(), nullptr);
  EXPECT_EQ(_states.at(3)->tryFindValidTransition(), nullptr);
  EXPECT_EQ(_states.at(4)->tryFindValidTransition(), nullptr);
}

TEST_F(SpriteAnimatorStateTest, tryFindValidTransitionReturnsNullptrWhenOneTrueOneFalse) {
  setUpRelationships(_states, std::vector<std::function<bool()>>{[] { return true; }, [] { return false; }});

  EXPECT_EQ(_states.at(0)->tryFindValidTransition(), nullptr);
  EXPECT_EQ(_states.at(1)->tryFindValidTransition(), nullptr);
  EXPECT_EQ(_states.at(2)->tryFindValidTransition(), nullptr);
  EXPECT_EQ(_states.at(3)->tryFindValidTransition(), nullptr);
  EXPECT_EQ(_states.at(4)->tryFindValidTransition(), nullptr);
}

TEST_F(SpriteAnimatorStateTest, insertNewStateWithNullStateCausesNoStateToBeAdded) {
  _states.at(0)->insertNewState(nullptr, std::vector<std::function<bool()>>());

  EXPECT_EQ(_states.at(0)->tryFindValidTransition(), nullptr);
}

TEST_F(SpriteAnimatorStateTest, insertNewStateWithNullFunctionCausesNullFunctionSafetyRemoval) {
  setUpRelationships(_states, std::vector<std::function<bool()>>{nullptr});

  EXPECT_EQ(_states.at(0)->tryFindValidTransition(), _states.at(1));
  EXPECT_EQ(_states.at(1)->tryFindValidTransition(), _states.at(2));
  EXPECT_EQ(_states.at(2)->tryFindValidTransition(), _states.at(3));
  EXPECT_EQ(_states.at(3)->tryFindValidTransition(), _states.at(4));
  EXPECT_EQ(_states.at(4)->tryFindValidTransition(), _states.at(0));
}
