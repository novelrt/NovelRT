//
// Created by miron on 2/20/19.
//

#ifndef NOVELRT_NOVELRUNNER_C_H
#define NOVELRT_NOVELRUNNER_C_H

#ifdef __cplusplus
extern "C" {
#endif
typedef void (* NovelUpdateSubscriber)(const double);

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
