//
// Created by miron on 2/22/19.
//

#ifndef NOVELRT_NOVELRTAPI_H
#define NOVELRT_NOVELRTAPI_H

#ifdef __cplusplus
extern "C" {
#endif
typedef void (*NovelSubscriber)(const float);

typedef struct WGeoVector WGeoVector;

WGeoVector* createGeoVector(void*, void*);
void destroyGeoVector(WGeoVector*);

void* getX(WGeoVector*);
void setX(WGeoVector*, void*);
void* getY(WGeoVector*);
void setY(WGeoVector*, void*);

typedef struct WNovelCommonArgs {
  WGeoVector* startingPosition;
  float startingRotation;
  WGeoVector* startingScale;
  int layer;
  int orderInLayer;
} WNovelCommonArgs;

typedef struct WRGBAConfig WRGBAConfig;

WRGBAConfig *createRGBAConfig(const int, const int, const int, const int);
void destroyRGBAConfig(WRGBAConfig*);

const int getR(WRGBAConfig*);
void setR(WRGBAConfig*, const int);

const int getG(WRGBAConfig*);
void setG(WRGBAConfig*, const int);

const int getB(WRGBAConfig*);
void setB(WRGBAConfig*, const int);

const int getA(WRGBAConfig*);
void setA(WRGBAConfig*, const int);

typedef struct WNovelImageRect WNovelImageRect;

typedef struct WNovelBasicFillRect WNovelBasicFillRect;

typedef struct WNovelRunner WNovelRunner;

WNovelRunner *createRunner(int);
void destroyRunner(WNovelRunner*);

void runOnUpdate(WNovelRunner*, NovelSubscriber);
void stopRunningOnUpdate(WNovelRunner*, NovelSubscriber);
void executeUpdateSubscriptions(WNovelRunner*, const float);
int runNovel(WNovelRunner*);

typedef struct WNovelRenderingService WNovelRenderingService;

WNovelImageRect *getImageRect(WNovelRenderingService*, char*, WNovelCommonArgs*);

WNovelRenderingService* getRenderer(WNovelRunner*);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_NOVELRTAPI_H
