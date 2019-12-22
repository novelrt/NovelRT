// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include<NovelRT.h>

extern "C" {
NovelRunner_t* createRunner(int displayNumber) {
  return reinterpret_cast<NovelRunner_t*>(new NovelRT::NovelRunner(displayNumber));
}

void destroyRunner(NovelRunner_t* runner) {
  delete reinterpret_cast<NovelRT::NovelRunner*>(runner);
}

void runOnUpdate(NovelRunner_t* runner, NovelUpdateSubscriber subscriber) {
  return reinterpret_cast<NovelRT::NovelRunner*>(runner)->runOnUpdate(subscriber);
}

void stopRunningOnUpdate(NovelRunner_t* runner, NovelUpdateSubscriber subscriber) {
  return reinterpret_cast<NovelRT::NovelRunner*>(runner)->stopRunningOnUpdate(subscriber);
}

int runNovel(NovelRunner_t* runner) {
  return reinterpret_cast<NovelRT::NovelRunner*>(runner)->runNovel();
}
}
