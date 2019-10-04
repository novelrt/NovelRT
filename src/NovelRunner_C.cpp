// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See License.md in the repository root for more information.

#include "NovelRunner.h"
#include "NovelRunner_C.h"

extern "C" {
NovelRunner_t* createRunner(int displayNumber) {
  return reinterpret_cast<NovelRunner_t*>(new NovelRT::NovelRunner(displayNumber, new NovelRT::NovelLayeringService()));
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
