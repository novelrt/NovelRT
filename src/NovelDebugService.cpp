//
// Created by tagoo on 12/09/2019.
//

#include <limits>
#include "NovelDebugService.h"
#include "NovelRunner.h"

namespace NovelRT {
  NovelDebugService::NovelDebugService(NovelRunner* runner) :
    _runner(runner),
    _fpsCounter(nullptr),
    _framesPerSecond(0) {
  }

  bool NovelDebugService::getIsFpsCounterVisible() const {
    return (_fpsCounter != nullptr) && _fpsCounter->getActive();
  }

  void NovelDebugService::setIsFpsCounterVisible(bool value) {
    if (_fpsCounter == nullptr) {
      if (value) {
        auto yellow = RGBAConfig(255, 255, 0, 255);

        auto textArgs = NovelCommonArgs();
        textArgs.startingPosition = GeoVector<float>(0, 1080 - 16);
        textArgs.layer = std::numeric_limits<int32_t>::max();
        textArgs.orderInLayer = std::numeric_limits<int32_t>::max();

        _fpsCounter = _runner->getRenderer()->getTextRect(yellow, 16, "Gayathri-Regular.ttf", textArgs);
        updateFpsCounter();
      }
    }
    else {
      _fpsCounter->setActive(value);
    }
  }

  void NovelDebugService::setFramesPerSecond(uint32_t value) {
    if (_framesPerSecond != value) {
      _framesPerSecond = value;
      updateFpsCounter();
    }
  }

  void NovelDebugService::updateFpsCounter() {
    if (_fpsCounter != nullptr) {
      char fpsText[16];
      sprintf_s(fpsText, "%u fps", _framesPerSecond);
      _fpsCounter->setText(fpsText);
    }
  }
}
