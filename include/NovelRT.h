#ifndef NOVELRT_H
#define NOVELRT_H

template<typename T>
class NovelRT::Maths::GeoVector;
template<typename T>
class NovelRT::Maths::GeoMatrix4;
template<typename T>
class NovelRT::Utilities::Lazy;

typedef class NovelRT::DebugService DebugService;
typedef class NovelRT::LayeringService LayeringService;
typedef class NovelRT::LoggingService LoggingService;
typedef class NovelRT::NovelRunner NovelRunner;
typedef class NovelRT::Transform Transform;
typedef class NovelRT::TransformSortComparison TransformSortComparison;

typedef class NovelRT::Audio::AudioService AudioService;

typedef class NovelRT::Graphics::BasicFillRect BasicFillRect;
typedef class NovelRT::Graphics::Camera Camera;
typedef class NovelRT::Graphics::CameraBlock CameraBlock;
typedef class NovelRT::Graphics::CameraViewChangedEventArgs CameraViewChangedEventArgs;
typedef class NovelRT::Graphics::GraphicsCharacterRenderData GraphicsCharacterRenderData;
typedef class NovelRT::Graphics::ImageRect ImageRect;
typedef class NovelRT::Graphics::RenderingSerivce RenderingService;
typedef class NovelRT::Graphics::RenderObject RenderObject;
typedef class NovelRT::Graphics::RGBAConfig RGBAConfig;
typedef class NovelRT::Graphics::ShaderProgram ShaderProgram;
typedef class NovelRT::Graphics::TextRect TextRect;

typedef class NovelRT::Input::BasicInteractionRect BasicInteractionRect;
typedef class NovelRT::Input::InteractionObject InteractionObject;
typedef class NovelRT::Input::InteractionService InteractionService;
typedef enum class NovelRT::Input::KeyCode KeyCode;
typedef enum class NovelRT::Input::KeyState KeyState;

typedef class NovelRT::Maths::GeoBounds GeoBounds;

typedef class NovelRT::Timing::StepTimer StepTimer;

typedef class NovelRT::Utilities::CommonArgs CommonArgs;
typedef class NovelRT::Utilities::Misc Misc;

typedef class NovelRT::Windowing::WindowingService WindowingService;



#include "NovelRT/Transform.h"
#include "NovelRT/Graphics/CameraBlock.h"
#include "NovelRT/Graphics/CameraViewChangedEventArgs.h"
#include "NovelRT/Maths/GeoBounds.h"
#include "NovelRT/Maths/GeoMatrix4.h"
#include "NovelRT/Maths/GeoVector.h"
#include "NovelRT/Graphics/GraphicsCharacterRenderData.h"
#include "NovelRT/Input/KeyCode.h"
#include "NovelRT/Input/KeyState.h"
#include "NovelRT/Utilities/Lazy.h"
#include "NovelRT/Audio/AudioService.h"
#include "NovelRT/Graphics/BasicFillRect.h"
#include "NovelRT/Input/BasicInteractionRect.h"
#include "NovelRT/Graphics/Camera.h"
#include "NovelRT/Utilities/CommonArgs.h"
#include "NovelRT/DebugService.h"
#include "NovelRT/Graphics/ImageRect.h"
#include "NovelRT/Input/InteractionObject.h"
#include "NovelRT/Input/InteractionService.h"
#include "NovelRT/LayeringService.h"
#include "NovelRT/LoggingService.h"
#include "NovelRT/TransformSortComparison.h"
#include "NovelRT/Graphics/RenderingService.h"
#include "NovelRT/Graphics/RenderObject.h"
#include "NovelRT/NovelRunner.h"
#include "NovelRT/NovelRT-C/NovelRunner_C.h"
#include "NovelRT/Timing/StepTimer.h"
#include "NovelRT/Graphics/TextRect.h"
#include "NovelRT/Utilities/Misc.h"
#include "NovelRT/Windowing/WindowingService.h"
#include "NovelRT/Graphics/RGBAConfig.h"
#include "NovelRT/Graphics/ShaderProgram.h"


#endif //!NOVELRT_H
