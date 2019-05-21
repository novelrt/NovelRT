//
// Created by miron on 2/22/19.
//

#include "NovelRTAPI.h"
#include "NovelRunner.h"
#include "GeoVector.h"
#include "NovelImageRect.h"

extern "C" {
    WRGBAConfig* createRGBAConfig(const int r, const int g, const int b, const int a) {
        return reinterpret_cast<WRGBAConfig*>(new NovelRT::RGBAConfig(r, g, b, a));
    }

    void destroyRGBAConfig(WRGBAConfig* wrgbaConfig) {
        delete reinterpret_cast<NovelRT::RGBAConfig*>(wrgbaConfig);
    }

    const int getR(WRGBAConfig* wrgbaConfig) {
        return reinterpret_cast<NovelRT::RGBAConfig*>(wrgbaConfig)->getR();
    }

    void setR(WRGBAConfig* wrgbaConfig, const int r) {
        return reinterpret_cast<NovelRT::RGBAConfig*>(wrgbaConfig)->setR(r);
    }

    WNovelRunner* createRunner(int displayNumber) {
        return reinterpret_cast<WNovelRunner*>(new NovelRT::NovelRunner(displayNumber, new NovelRT::NovelLayeringService()));
    }

    void destroyRunner(WNovelRunner* runner) {
        delete reinterpret_cast<NovelRT::NovelRunner*>(runner);
    }

    void executeUpdateSubscriptions(WNovelRunner* runner, const float deltaTime) {
        return reinterpret_cast<NovelRT::NovelRunner*>(runner)->executeUpdateSubscriptions(deltaTime);
    }

    void runOnUpdate(WNovelRunner* runner, NovelSubscriber subscriber) {
        return reinterpret_cast<NovelRT::NovelRunner*>(runner)->runOnUpdate(subscriber);
    }

    void stopRunningOnUpdate(WNovelRunner* runner, NovelSubscriber subscriber) {
        return reinterpret_cast<NovelRT::NovelRunner*>(runner)->stopRunningOnUpdate(subscriber);
    }

    int runNovel(WNovelRunner* runner) {
        return reinterpret_cast<NovelRT::NovelRunner*>(runner)->runNovel();
    }

    WNovelRenderingService* getRenderer(WNovelRunner* runner) {
        return
        reinterpret_cast<WNovelRenderingService*>
        (reinterpret_cast<NovelRT::NovelRunner*>(runner)->getRenderer());
    }

    WGeoVector* createGeoVector(void* x, void* y) {
        return reinterpret_cast<WGeoVector*>(new NovelRT::GeoVector(x, y));
    }

    void destroyGeoVector(WGeoVector* geoVector) {
        delete reinterpret_cast<NovelRT::GeoVector<void*>*>(geoVector);
    }

    void* getX(WGeoVector* geoVector) {
        return reinterpret_cast<NovelRT::GeoVector<void*>*>(geoVector)->getX();
    }

    void setX(WGeoVector* geoVector, void* x) {
        return reinterpret_cast<NovelRT::GeoVector<void*>*>(geoVector)->setX(x);
    }

    void* getY(WGeoVector* geoVector) {
        return reinterpret_cast<NovelRT::GeoVector<void*>*>(geoVector)->getY();
    }

    void setY(WGeoVector* geoVector, void* y) {
        return reinterpret_cast<NovelRT::GeoVector<void*>*>(geoVector)->setY(y);
    }
}
WNovelImageRect* getImageRect(WNovelRenderingService* renderer, char* filePath, WNovelCommonArgs* args) {
  NovelRT::NovelCommonArgs coreArgs;
  coreArgs.layer = args->layer;
  coreArgs.orderInLayer = args->orderInLayer;
  coreArgs.startingRotation = args->startingRotation;
  WNovelImageRect* imageRect = nullptr;
  imageRect = reinterpret_cast<WNovelImageRect*>(reinterpret_cast<NovelRT::NovelRenderingService*>(renderer)->getImageRect(filePath, coreArgs));
  return imageRect;
}
