// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

//TODO: Resolve older solution for this if possible.
//DO NOT DELETE THIS, MOVE THIS TO DEBUG SERVICE WHEN IT EXISTS
/*void GLAPIENTRY
messageCallback(GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei length,
                const GLchar* message,
                const void* userParam ) {
    if (severity < GL_DEBUG_SEVERITY_HIGH) {
        return;
    }

    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
             ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
             type, severity, message );
}*/

// During init, enable debug output
/*    glEnable( GL_DEBUG_OUTPUT );
  glDebugMessageCallback(messageCallback, 0);*/

#include <NovelRT.h>

namespace NovelRT {
  DebugService::DebugService(NovelRunner* runner) :
    _runner(runner),
    _fpsCounter(nullptr),
    _framesPerSecond(0) {
  }

  bool DebugService::getIsFpsCounterVisible() const {
    return (_fpsCounter != nullptr) && _fpsCounter->getActive();
  }

  void DebugService::setIsFpsCounterVisible(bool value) {
    if (_fpsCounter == nullptr) {
      if (value) {
        auto yellow = Graphics::RGBAConfig(255, 255, 0, 255);

        auto transform = Transform(Maths::GeoVector<float>(0, 1080 - 16), 0, Maths::GeoVector<float>(1.0f, 1.0f));

        _fpsCounter = _runner->getRenderer()->getTextRect(yellow, 16, "Gayathri-Regular.ttf", transform);
        updateFpsCounter();
      }
    }
    else {
      _fpsCounter->setActive(value);
    }
  }

  void DebugService::setFramesPerSecond(uint32_t value) {
    if (_framesPerSecond != value) {
      _framesPerSecond = value;
      updateFpsCounter();
    }
  }

  void DebugService::updateFpsCounter() {
    if (_fpsCounter != nullptr) {
      char fpsText[16];
      snprintf(fpsText, 16, "%u fps", _framesPerSecond);
      _fpsCounter->setText(fpsText);
    }
  }
}
