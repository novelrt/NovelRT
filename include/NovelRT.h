#ifndef NOVELRT_H
#define NOVELRT_H


namespace NovelRT::Maths {
  template<typename T>
  class GeoVector;

  template<typename T>
  class GeoMatrix4;

  typedef class GeoBounds GeoBounds;
}

namespace NovelRT {
  typedef void (*NovelUpdateSubscriber)(double);
  typedef class Transform Transform;
  typedef struct TransformSortComparison TransformSortComparison;
  typedef class DebugService DebugService;
  typedef class LoggingService LoggingService;
  typedef class NovelRunner NovelRunner;
}

namespace NovelRT::Audio {
  typedef class AudioService AudioService;
}

namespace NovelRT::Graphics {
  typedef class BasicFillRect BasicFillRect;
  typedef class Camera Camera;
  typedef struct CameraBlock CameraBlock;
  typedef class CameraViewChangedEventArgs CameraViewChangedEventArgs;
  typedef struct GraphicsCharacterRenderData GraphicsCharacterRenderData;
  typedef class ImageRect ImageRect;
  typedef class RenderingService RenderingService;
  typedef class RenderObject RenderObject;
  typedef class RGBAConfig RGBAConfig;
  typedef struct ShaderProgram ShaderProgram;
  typedef class TextRect TextRect;
}

namespace NovelRT::Input {
  typedef class BasicInteractionRect BasicInteractionRect;
  typedef class InteractionObject InteractionObject;
  typedef class InteractionService InteractionService;
  typedef enum class KeyCode KeyCode;
  typedef enum class KeyState KeyState;
}

namespace NovelRT::Timing {
  typedef class StepTimer StepTimer;
}

namespace NovelRT::Utilities {
  template<typename T>
  class Lazy;

  typedef struct CommonArgs CommonArgs;
  typedef class Misc Misc;
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
#include "NovelRT/Utilities/CommonArgs.h"
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
