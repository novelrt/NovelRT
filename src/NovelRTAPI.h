//
// Created by miron on 2/22/19.
//

#ifndef NOVELRT_NOVELRTAPI_H
#define NOVELRT_NOVELRTAPI_H

#ifdef __cplusplus
extern "C" {
#endif
typedef void (*NovelSubscriber)(const float);

typedef struct NovelRunnerWrapper NovelRunnerWrapper;

NovelRunnerWrapper *createRunner(int);
void destroyRunner(NovelRunnerWrapper*);

void runOnUpdate(NovelRunnerWrapper*, NovelSubscriber);
void stopRunningOnUpdate(NovelRunnerWrapper*, NovelSubscriber);
void executeUpdateSubscriptions(NovelRunnerWrapper*, const float);
int runNovel(NovelRunnerWrapper*);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_NOVELRTAPI_H
