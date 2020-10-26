// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.Interop/Animation/NovelRTSpriteAnimatorState.h"
#include <NovelRT.h>

using namespace NovelRT;
using namespace NovelRT::Maths;
using namespace NovelRT::Animation;

class InteropSpriteAnimatorStateTest : public testing::Test {
protected:
  std::vector<NovelRTSpriteAnimatorState> _states;

  void SetUp() override {
    _states = std::vector<NovelRTSpriteAnimatorState>{
      NovelRT_SpriteAnimatorState_create(),
      NovelRT_SpriteAnimatorState_create(),
      NovelRT_SpriteAnimatorState_create(),
      NovelRT_SpriteAnimatorState_create(),
      NovelRT_SpriteAnimatorState_create(),
    };
  }
};

 void interopSetUpRelationships(std::vector<NovelRTSpriteAnimatorState> targets, std::vector<std::function<bool()>> conditions = std::vector<std::function<bool()>>()) {
   for (size_t i = 0; i < targets.size(); i++) {
     auto nextTarget = (i + 1 >= targets.size()) ? 0 : i + 1;
     std::vector<std::function<bool()>>* conditionsPtr = new std::vector<std::function<bool()>>();
     *conditionsPtr = conditions;
      NovelRTSpriteAnimatorStateConditionFunctions cond = reinterpret_cast<NovelRTSpriteAnimatorStateConditionFunctions>(conditionsPtr);
      NovelRT_SpriteAnimatorState_insertNewState(targets.at(i), targets.at(nextTarget), cond, nullptr);
   }
 }

TEST_F(InteropSpriteAnimatorStateTest, tryFindValidTransitionReturnsNullptrWhenNoRelationships) {
  NovelRTSpriteAnimatorState mockState = NovelRT_SpriteAnimatorState_create();
  int32_t res = 0;
  res = NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(0), &mockState, nullptr);
  EXPECT_EQ(mockState, nullptr);
}

TEST_F(InteropSpriteAnimatorStateTest, tryFindValidTransitionReturnsSpriteAnimatorStateWhenNoConditions) {
  interopSetUpRelationships(_states);

  NovelRTSpriteAnimatorState mockStateOne = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateTwo = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateThree = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateFour = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateFive = NovelRT_SpriteAnimatorState_create();

  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(0), &mockStateOne, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(1), &mockStateTwo, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(2), &mockStateThree, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(3), &mockStateFour, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(4), &mockStateFive, nullptr);
  
  EXPECT_EQ(mockStateOne, _states.at(1));
  EXPECT_EQ(mockStateTwo, _states.at(2));
  EXPECT_EQ(mockStateThree, _states.at(3));
  EXPECT_EQ(mockStateFour, _states.at(4));
  EXPECT_EQ(mockStateFive, _states.at(0));
}

TEST_F(InteropSpriteAnimatorStateTest, tryFindValidTransitionReturnsSpriteAnimatorStateWhenAllConditionsTrue) {
  interopSetUpRelationships(_states, std::vector<std::function<bool()>>{[] { return true; }});

  NovelRTSpriteAnimatorState mockStateOne = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateTwo = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateThree = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateFour = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateFive = NovelRT_SpriteAnimatorState_create();

  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(0), &mockStateOne, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(1), &mockStateTwo, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(2), &mockStateThree, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(3), &mockStateFour, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(4), &mockStateFive, nullptr);
  
  EXPECT_EQ(mockStateOne, _states.at(1));
  EXPECT_EQ(mockStateTwo, _states.at(2));
  EXPECT_EQ(mockStateThree, _states.at(3));
  EXPECT_EQ(mockStateFour, _states.at(4));
  EXPECT_EQ(mockStateFive, _states.at(0));
}

 TEST_F(InteropSpriteAnimatorStateTest, tryFindValidTransitionReturnsNullptrWhenAllConditionsFalse) {
   interopSetUpRelationships(_states, std::vector<std::function<bool()>>{[] { return false; }});

  NovelRTSpriteAnimatorState mockStateOne = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateTwo = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateThree = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateFour = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateFive = NovelRT_SpriteAnimatorState_create();

  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(0), &mockStateOne, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(1), &mockStateTwo, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(2), &mockStateThree, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(3), &mockStateFour, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(4), &mockStateFive, nullptr);
  
  EXPECT_EQ(mockStateOne, nullptr);
  EXPECT_EQ(mockStateTwo, nullptr);
  EXPECT_EQ(mockStateThree, nullptr);
  EXPECT_EQ(mockStateFour, nullptr);
  EXPECT_EQ(mockStateFive, nullptr);
 }

TEST_F(InteropSpriteAnimatorStateTest, tryFindValidTransitionReturnsSpriteAnimatorStateWhenAllMultipleConditionsTrue) {
  interopSetUpRelationships(_states, std::vector<std::function<bool()>>{[] { return true; }, [] { return true; }});

  NovelRTSpriteAnimatorState mockStateOne = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateTwo = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateThree = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateFour = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateFive = NovelRT_SpriteAnimatorState_create();

  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(0), &mockStateOne, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(1), &mockStateTwo, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(2), &mockStateThree, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(3), &mockStateFour, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(4), &mockStateFive, nullptr);
  
  EXPECT_EQ(mockStateOne, _states.at(1));
  EXPECT_EQ(mockStateTwo, _states.at(2));
  EXPECT_EQ(mockStateThree, _states.at(3));
  EXPECT_EQ(mockStateFour, _states.at(4));
  EXPECT_EQ(mockStateFive, _states.at(0));
}
  
TEST_F(InteropSpriteAnimatorStateTest, tryFindValidTransitionReturnsNullptrWhenAllMultipleConditionsFalse) {
  interopSetUpRelationships(_states, std::vector<std::function<bool()>>{[] { return false; }, [] { return false; }});

  NovelRTSpriteAnimatorState mockStateOne = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateTwo = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateThree = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateFour = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateFive = NovelRT_SpriteAnimatorState_create();

  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(0), &mockStateOne, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(1), &mockStateTwo, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(2), &mockStateThree, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(3), &mockStateFour, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(4), &mockStateFive, nullptr);
  
  EXPECT_EQ(mockStateOne, nullptr);
  EXPECT_EQ(mockStateTwo, nullptr);
  EXPECT_EQ(mockStateThree, nullptr);
  EXPECT_EQ(mockStateFour, nullptr);
  EXPECT_EQ(mockStateFive, nullptr);
}

TEST_F(InteropSpriteAnimatorStateTest, tryFindValidTransitionReturnsNullptrWhenOneTrueOneFalse) {
  interopSetUpRelationships(_states, std::vector<std::function<bool()>>{[] { return true; }, [] { return false; }});

  NovelRTSpriteAnimatorState mockStateOne = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateTwo = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateThree = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateFour = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateFive = NovelRT_SpriteAnimatorState_create();

  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(0), &mockStateOne, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(1), &mockStateTwo, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(2), &mockStateThree, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(3), &mockStateFour, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(4), &mockStateFive, nullptr);
  
  EXPECT_EQ(mockStateOne, nullptr);
  EXPECT_EQ(mockStateTwo, nullptr);
  EXPECT_EQ(mockStateThree, nullptr);
  EXPECT_EQ(mockStateFour, nullptr);
  EXPECT_EQ(mockStateFive, nullptr);
}

TEST_F(InteropSpriteAnimatorStateTest, insertNewStateWithNullStateCausesNoStateToBeAdded) {

  Animation::SpriteAnimatorState* cppNullState = nullptr;
  NovelRTSpriteAnimatorState mockNullState = reinterpret_cast<NovelRTSpriteAnimatorState>(cppNullState);
  
  std::vector<std::function<bool()>>* conditionsPtr = new std::vector<std::function<bool()>>();
  *conditionsPtr = std::vector<std::function<bool()>>();
  NovelRTSpriteAnimatorStateConditionFunctions cond = reinterpret_cast<NovelRTSpriteAnimatorStateConditionFunctions>(conditionsPtr);
  
  NovelRT_SpriteAnimatorState_insertNewState(_states.at(0), mockNullState, cond, nullptr);
  NovelRTSpriteAnimatorState mockStateOne = NovelRT_SpriteAnimatorState_create();
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(0), &mockStateOne, nullptr);

  EXPECT_EQ(mockStateOne, nullptr);
}

TEST_F(InteropSpriteAnimatorStateTest, insertNewStateWithNullFunctionCausesNullFunctionSafetyRemoval) {
  interopSetUpRelationships(_states, std::vector<std::function<bool()>>{nullptr});
  
  NovelRTSpriteAnimatorState mockStateOne = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateTwo = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateThree = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateFour = NovelRT_SpriteAnimatorState_create();
  NovelRTSpriteAnimatorState mockStateFive = NovelRT_SpriteAnimatorState_create();

  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(0), &mockStateOne, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(1), &mockStateTwo, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(2), &mockStateThree, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(3), &mockStateFour, nullptr);
  NovelRT_SpriteAnimatorState_tryFindValidTransition(_states.at(4), &mockStateFive, nullptr);
  
  EXPECT_EQ(mockStateOne, _states.at(1));
  EXPECT_EQ(mockStateTwo, _states.at(2));
  EXPECT_EQ(mockStateThree, _states.at(3));
  EXPECT_EQ(mockStateFour, _states.at(4));
  EXPECT_EQ(mockStateFive, _states.at(0));
}
