// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELRUNNER_C_H
#define NOVELRT_NOVELRUNNER_C_H

#ifdef __cplusplus
extern "C" {
#endif
typedef void (* NovelUpdateSubscriber)(double);

struct NovelRunner_C;
typedef struct NovelRunner_C NovelRunner_t;

NovelRunner_t* createRunner(int);
void destroyRunner(NovelRunner_t*);

void runOnUpdate(NovelRunner_t*, NovelUpdateSubscriber);
void stopRunningOnUpdate(NovelRunner_t*, NovelUpdateSubscriber);
int runNovel(NovelRunner_t*);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_NOVELRUNNER_C_H
