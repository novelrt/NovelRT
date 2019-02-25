//
// Created by miron on 2/22/19.
//

#ifndef NOVELRT_NOVELRTAPI_H
#define NOVELRT_NOVELRTAPI_H

#ifdef __cplusplus
extern "C" {
#endif
typedef void (*NovelSubscriber)(const float);

typedef struct NovelCommonArgsWrapper {
  float startingRotation;
  int layer;
  int orderInLayer;
} NovelCommonArgsWrapper;

typedef struct NovelImageRectWrapper NovelImageRectWrapper;

typedef struct NovelRenderingServiceWrapper NovelRenderingServiceWrapper;

NovelImageRectWrapper* getImageRect(NovelRenderingServiceWrapper*, char*, NovelCommonArgsWrapper*);

typedef struct NovelRunnerWrapper NovelRunnerWrapper;

NovelRunnerWrapper *createRunner(int);
void destroyRunner(NovelRunnerWrapper*);

void runOnUpdate(NovelRunnerWrapper*, NovelSubscriber);
void stopRunningOnUpdate(NovelRunnerWrapper*, NovelSubscriber);
void executeUpdateSubscriptions(NovelRunnerWrapper*, const float);
int runNovel(NovelRunnerWrapper*);
NovelRenderingServiceWrapper* getRenderer(NovelRunnerWrapper*);


typedef struct GeoVectorWrapper GeoVectorWrapper;

GeoVectorWrapper* createGeoVector(void*, void*);
void destroyGeoVector(GeoVectorWrapper*);

void* getX(GeoVectorWrapper*);
void setX(GeoVectorWrapper*, void*);
void* getY(GeoVectorWrapper*);
void setY(GeoVectorWrapper*, void*);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_NOVELRTAPI_H
