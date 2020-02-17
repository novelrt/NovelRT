#include <gtest/gtest.h>
#include <NovelRT.h>

using namespace NovelRT;
using namespace NovelRT::Utilities;

TEST(EventTest, createHasZeroSize)
{
  auto event = Event<>();
  EXPECT_EQ(0, event.getHandlerCount());
}

TEST(EventTest, subscribeAddsOne)
{
  auto event = Event<>();
  event += [](){};
  EXPECT_EQ(1, event.getHandlerCount());
}

TEST(EventTest, unsubscribeNonexistingRemovesZero)
{
  auto event = Event<>();
  event += [](){};

  EventHandler<> OnEvent = std::function<void()>([](){});
  event -= OnEvent;

  EXPECT_EQ(1, event.getHandlerCount());
}

TEST(EventTest, subscribeTwiceAddsTwo)
{
  auto event = Event<>();

  EventHandler<> OnEvent = std::function<void()>([](){});
  event += OnEvent;
  event += OnEvent;

  EXPECT_EQ(2, event.getHandlerCount());
}

TEST(EventTest, unsubscribeExistingRemovesOne)
{
  auto event = Event<>();

  EventHandler<> OnEvent = std::function<void()>([](){});
  event += OnEvent;
  event += OnEvent;

  event -= OnEvent;
  EXPECT_EQ(1, event.getHandlerCount());
}

TEST(EventTest, unsubscribeRemovesMatchingVersion1)
{
  auto event = Event<>();

  int counter = 0;

  EventHandler<> OnEvent1 = std::function<void()>([&counter]() { counter = 1; });
  event += OnEvent1;

  EventHandler<> OnEvent2 = std::function<void()>([&counter]() { counter = 2; });
  event += OnEvent2;

  event -= OnEvent2;
  event();

  EXPECT_EQ(1, counter);
}

TEST(EventTest, unsubscribeRemovesMatchingVersion2)
{
  auto event = Event<>();

  int counter = 0;

  EventHandler<> OnEvent1 = std::function<void()>([&counter]() { counter = 1; });
  event += OnEvent1;

  EventHandler<> OnEvent2 = std::function<void()>([&counter]() { counter = 2; });
  event += OnEvent2;

  event -= OnEvent1;
  event();

  EXPECT_EQ(2, counter);
}

