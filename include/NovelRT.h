// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_H
#define NOVELRT_H

//cstdlib
#include <cmath>
#include <cstdint>

//stdlib
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <vector>

//Freetype
#include <ft2build.h>
#include FT_FREETYPE_H

//glad
#include <glad.h>

//GLFW3
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

//OpenAL
#include <AL/al.h>
#include <AL/alc.h>

//LibSndfile
#include <sndfile.h>

//nethost
#include <coreclr_delegates.h>
#include <hostfxr.h>

//spdlog
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/async.h"

//libpng
#include "png.h"

namespace NovelRT {
  typedef void (*NovelUpdateSubscriber)(double deltaSeconds);
  typedef class DebugService DebugService;
  typedef class LoggingService LoggingService;
  typedef class NovelRunner NovelRunner;
}

namespace NovelRT::Audio {
  typedef std::vector<ALuint> SoundBank;
  typedef std::vector<ALuint> MusicBank;
  typedef class AudioService AudioService;
}

namespace NovelRT::DotNet {
  typedef class RuntimeService RuntimeService;
}

namespace NovelRT::Graphics {
  typedef class BasicFillRect BasicFillRect;
  typedef class Camera Camera;
  typedef class ImageRect ImageRect;
  typedef class RenderingService RenderingService;
  typedef class RenderObject RenderObject;
  typedef class TextRect TextRect;
}

namespace NovelRT::Input {
  typedef class BasicInteractionRect BasicInteractionRect;
  typedef class InteractionObject InteractionObject;
  typedef class InteractionService InteractionService;
}

namespace NovelRT::Timing {
  typedef class StepTimer StepTimer;
}

namespace NovelRT::Windowing {
  typedef class WindowingService WindowingService;
}

//enums
#include "NovelRT/Debug/MetricsLevel.h"
#include "NovelRT/Input/KeyCode.h"
#include "NovelRT/Input/KeyState.h"
#include "NovelRT/Graphics/CameraFrameState.h"

//value types
#include "NovelRT/Maths/GeoVector.h"
#include "NovelRT/Maths/GeoMatrix4.h"
#include "NovelRT/Maths/GeoBounds.h"
#include "NovelRT/Transform.h"
#include "NovelRT/Graphics/GraphicsCharacterRenderData.h"
#include "NovelRT/Graphics/ImageData.h"
#include "NovelRT/Graphics/ShaderProgram.h"
#include "NovelRT/Graphics/RGBAConfig.h"
#include "NovelRT/Utilities/Lazy.h"
#include "NovelRT/Utilities/Misc.h"

//base types
#include "NovelRT/LoggingService.h" //this isn't in the services section due to include order/dependencies.
#include "NovelRT/Timing/StepTimer.h"
#include "NovelRT/NovelRunner.h"
#include "NovelRT/WorldObject.h"

//Graphics types
#include "NovelRT/Graphics/Camera.h"
#include "NovelRT/Graphics/RenderObject.h"
#include "NovelRT/Graphics/BasicFillRect.h"
#include "NovelRT/Graphics/GraphicsCharacterRenderDataHelper.h"
#include "NovelRT/Graphics/ImageRect.h"
#include "NovelRT/Graphics/TextRect.h"

//Input types
#include "NovelRT/Input/InteractionObject.h"
#include "NovelRT/Input/BasicInteractionRect.h"

//Engine service types
#include "NovelRT/Audio/AudioService.h"
#include "NovelRT/DebugService.h"
#include "NovelRT/DotNet/RuntimeService.h"
#include "NovelRT/Input/InteractionService.h"
#include "NovelRT/Windowing/WindowingService.h"
#include "NovelRT/Graphics/RenderingService.h"

#endif //!NOVELRT_H
