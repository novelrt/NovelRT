//
// Created by miron on 2/22/19.
//

#include "NovelRTAPI.h"
#include "NovelRunner.h"
#include "GeoVector.h"
#include "NovelImageRect.h"

extern "C" {
    NovelRunnerWrapper* createRunner(int displayNumber) {
        return reinterpret_cast<NovelRunnerWrapper*>(new NovelRT::NovelRunner(displayNumber));
    }

    void destroyRunner(NovelRunnerWrapper* runner) {
        delete reinterpret_cast<NovelRT::NovelRunner*>(runner);
    }

    void executeUpdateSubscriptions(NovelRunnerWrapper* runner, const float deltaTime) {
        return reinterpret_cast<NovelRT::NovelRunner*>(runner)->executeUpdateSubscriptions(deltaTime);
    }

    void runOnUpdate(NovelRunnerWrapper* runner, NovelSubscriber subscriber) {
        return reinterpret_cast<NovelRT::NovelRunner*>(runner)->runOnUpdate(subscriber);
    }

    void stopRunningOnUpdate(NovelRunnerWrapper* runner, NovelSubscriber subscriber) {
        return reinterpret_cast<NovelRT::NovelRunner*>(runner)->stopRunningOnUpdate(subscriber);
    }

    int runNovel(NovelRunnerWrapper* runner) {
        return reinterpret_cast<NovelRT::NovelRunner*>(runner)->runNovel();
    }

    NovelRenderingServiceWrapper *getRenderer(NovelRunnerWrapper* runner) {
        return
        reinterpret_cast<NovelRenderingServiceWrapper*>
        (reinterpret_cast<NovelRT::NovelRunner*>(runner)->getRenderer());
    }

    GeoVectorWrapper* createGeoVector(void* x, void* y) {
        return reinterpret_cast<GeoVectorWrapper*>(new NovelRT::GeoVector(x, y));
    }

    void destroyGeoVector(GeoVectorWrapper* geoVector) {
        delete reinterpret_cast<NovelRT::GeoVector<void*>*>(geoVector);
    }

    void* getX(GeoVectorWrapper* geoVector) {
        return reinterpret_cast<NovelRT::GeoVector<void*>*>(geoVector)->getX();
    }

    void setX(GeoVectorWrapper* geoVector, void* x) {
        return reinterpret_cast<NovelRT::GeoVector<void*>*>(geoVector)->setX(x);
    }

    void* getY(GeoVectorWrapper* geoVector) {
        return reinterpret_cast<NovelRT::GeoVector<void*>*>(geoVector)->getY();
    }

    void setY(GeoVectorWrapper* geoVector, void* y) {
        return reinterpret_cast<NovelRT::GeoVector<void*>*>(geoVector)->setY(y);
    }
}
NovelImageRectWrapper* getImageRect(NovelRenderingServiceWrapper* renderer, char* filePath, NovelCommonArgsWrapper* args) {
  NovelRT::NovelCommonArgs coreArgs;
  coreArgs.layer = args->layer;
  coreArgs.orderInLayer = args->orderInLayer;
  coreArgs.startingRotation = args->startingRotation;
  NovelRT::NovelImageRect* imageRect = nullptr;
  imageRect = &reinterpret_cast<NovelRT::NovelRenderingService*>(renderer)->getImageRect(filePath, coreArgs);
}
