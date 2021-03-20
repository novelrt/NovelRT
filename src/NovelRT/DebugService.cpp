// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

// TODO: Resolve older solution for this if possible.
// DO NOT DELETE THIS, MOVE THIS TO DEBUG SERVICE WHEN IT EXISTS
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

namespace NovelRT
{
    DebugService::DebugService(Utilities::Event<>& sceneConstructionEvent,
                               std::shared_ptr<Graphics::RenderingService> renderingService) noexcept
        : _renderingService(renderingService),
          _fpsCounter(nullptr),
          _shaderCounter(nullptr),
          _logging(LoggingService(Utilities::Misc::CONSOLE_LOG_STATS)),
          _framesPerSecond(0)
    {
        renderingService->debugService = this;
        sceneConstructionEvent += std::bind(&DebugService::onSceneConstruction, this);
    }

    bool DebugService::getIsFpsCounterVisible() const
    {
        return (_fpsCounter != nullptr) && _fpsCounter->getActive();
    }

    void DebugService::setIsFpsCounterVisible(bool value)
    {
        if (_fpsCounter == nullptr)
        {
            if (value)
            {
                auto yellow = Graphics::RGBAConfig(255, 255, 0, 255);

                auto transform = Transform(Maths::GeoVector2F(16, 1080 - 16), 0, Maths::GeoVector2F(1.0f, 1.0f));

                std::filesystem::path executableDirPath = NovelRT::Utilities::Misc::getExecutableDirPath();
                std::filesystem::path fontsDirPath = executableDirPath / "Resources" / "Fonts";

                std::string fontPath = (fontsDirPath / "Gayathri-Regular.ttf").string();

                _fpsCounter = _renderingService->createTextRect(transform, 0, yellow, 16, fontPath);
                updateFpsCounter();
            }
        }
        else
        {
            _fpsCounter->setActive(value);
        }
    }

    void DebugService::setFramesPerSecond(uint32_t framesPerSecond)
    {
        if (_framesPerSecond != framesPerSecond)
        {
            _framesPerSecond = framesPerSecond;
            if (_minFramesPerSecond > _framesPerSecond)
            {
                _minFramesPerSecond = _framesPerSecond;
            }
            if (_maxFramesPerSecond < _framesPerSecond)
            {
                _maxFramesPerSecond = _framesPerSecond;
            }
        }
        updateFpsCounter();
    }

    void DebugService::accumulateStatistics(uint32_t framesPerSecond, uint32_t totalSeconds, uint32_t totalFrames)
    {
        _totalSeconds = totalSeconds;
        _totalFrames = totalFrames;
        setFramesPerSecond(framesPerSecond);
    }

    void DebugService::updateFpsCounter()
    {
        if (_fpsCounter != nullptr && _totalSeconds > 0 && _totalFrames > 0)
        {
            char fpsText[64];
            snprintf(fpsText, 64, "%u fps %u avg %u min %u max %u total", _framesPerSecond,
                     _totalFrames / _totalSeconds, _minFramesPerSecond, _maxFramesPerSecond, _totalFrames);
            _fpsCounter->setText(fpsText);

            if (_totalSeconds - _lastTimeFpsDiagnosticsLogged > 1)
            {
                _lastTimeFpsDiagnosticsLogged = _totalSeconds;
                _logging.logInfo(fpsText);
            }
        }
    }

    void DebugService::onSceneConstruction()
    {
        if (_fpsCounter != nullptr)
             _fpsCounter->executeObjectBehaviour();
        if (_shaderCounter != nullptr)
            _shaderCounter->executeObjectBehaviour();
    }

    bool DebugService::getIsShaderCounterVisible() const
    {
        return (_shaderCounter != nullptr) && _shaderCounter->getActive();
    }

    void DebugService::setIsShaderCounterVisible(bool value)
    {
        if (_shaderCounter == nullptr)
        {
            if (value)
            {
                auto whiteRgbaConfig = Graphics::RGBAConfig(255, 255, 255, 255);

                auto transform = Transform(Maths::GeoVector2F(16, 1080 - 32), 0, Maths::GeoVector2F(1.0f, 1.0f));

                std::filesystem::path executableDirPath = NovelRT::Utilities::Misc::getExecutableDirPath();
                std::filesystem::path fontsDirPath = executableDirPath / "Resources" / "Fonts";

                std::string fontPath = (fontsDirPath / "Gayathri-Regular.ttf").string();

                _shaderCounter = _renderingService->createTextRect(transform, 0, whiteRgbaConfig, 16, fontPath);
                updateShaderCounter();
            }
        }
        else
        {
            _shaderCounter->setActive(value);
        }
    }

    void DebugService::increaseLoadedShaderCount(bool isVertexShader)
    {
        if (isVertexShader)
            _vertexShadersLoaded++;
        else
            _fragmentShadersLoaded++;

        updateShaderCounter();
    }

    void DebugService::updateShaderCounter()
    {
        if (_shaderCounter != nullptr)
        {
            char shaderText[128];
            snprintf(shaderText, 128, "%u vertexShaders, %u fragmentShaders loaded into the RenderingService",
              _vertexShadersLoaded, _fragmentShadersLoaded);
            _shaderCounter->setText(shaderText);
            _logging.logDebugLine(shaderText);
        }
    }
} // namespace NovelRT
