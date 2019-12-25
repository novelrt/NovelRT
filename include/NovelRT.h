// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_H
#define NOVELRT_H

#include <type_traits>
#include <map>
#include <string>
#include <glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

namespace NovelRT {
  typedef void (*NovelUpdateSubscriber)(double deltaSeconds);
  typedef class DebugService DebugService;
  typedef class LoggingService LoggingService;
  typedef class NovelRunner NovelRunner;
}

namespace NovelRT::Audio {
  typedef std::map<std::string, Mix_Chunk*> SoundBank;
  typedef std::map<std::string, Mix_Music*> MusicBank;
  typedef std::map<std::string, int> ChannelMap;
  typedef class AudioService AudioService;
}

namespace NovelRT::Graphics {
  typedef std::conditional<sizeof(signed long) <= 4, GLuint, GLuint64>::type AdvanceInteger;
  typedef class BasicFillRect BasicFillRect;
  typedef class Camera Camera;
  typedef class CameraViewChangedEventArgs CameraViewChangedEventArgs;
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
#include "NovelRT/Input/KeyCode.h"
#include "NovelRT/Input/KeyState.h"

//value types
#include "NovelRT/Maths/GeoVector.h"
#include "NovelRT/Maths/GeoMatrix4.h"
#include "NovelRT/Maths/GeoBounds.h"
#include "NovelRT/Transform.h"
#include "NovelRT/Graphics/CameraBlock.h"
#include "NovelRT/Graphics/GraphicsCharacterRenderData.h"
#include "NovelRT/Graphics/ShaderProgram.h"
#include "NovelRT/Graphics/RGBAConfig.h"
#include "NovelRT/Utilities/Lazy.h"
#include "NovelRT/Utilities/Misc.h"

#include "NovelRT/LoggingService.h"
#include "NovelRT/Timing/StepTimer.h"
#include "NovelRT/NovelRunner.h"
#include "NovelRT/WorldObject.h"

#include "NovelRT/Graphics/CameraViewChangedEventArgs.h"
#include "NovelRT/Graphics/Camera.h"
#include "NovelRT/Graphics/RenderObject.h"
#include "NovelRT/Graphics/BasicFillRect.h"
#include "NovelRT/Graphics/ImageRect.h"
#include "NovelRT/Graphics/TextRect.h"

#include "NovelRT/Input/InteractionObject.h"
#include "NovelRT/Input/BasicInteractionRect.h"

#include "NovelRT/Audio/AudioService.h"
#include "NovelRT/DebugService.h"
#include "NovelRT/Input/InteractionService.h"
#include "NovelRT/Windowing/WindowingService.h"
#include "NovelRT/Graphics/RenderingService.h"

#endif //!NOVELRT_H
