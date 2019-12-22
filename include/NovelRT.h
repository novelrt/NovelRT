#ifndef NOVELRT_H
#define NOVELRT_H

template<typename T>
class NovelRT::Maths::GeoVector;
template<typename T>
class NovelRT::Maths::GeoMatrix4;
template<typename T>
class NovelRT::Utilities::Lazy;

typedef NovelRT::DebugService DebugService;
typedef NovelRT::LayeringService LayeringService;
typedef NovelRT::LoggingService LoggingService;
typedef NovelRT::NovelRunner NovelRunner;
typedef NovelRT::Transform Transform;
typedef NovelRT::TransformSortComparison TransformSortComparison;

typedef NovelRT::Audio::AudioService AudioService;

typedef NovelRT::Graphics::BasicFillRect BasicFillRect;
typedef NovelRT::Graphics::Camera Camera;
typedef NovelRT::Graphics::CameraBlock CameraBlock;
typedef NovelRT::Graphics::CameraViewChangedEventArgs CameraViewChangedEventArgs;
typedef NovelRT::Graphics::GraphicsCharacterRenderData GraphicsCharacterRenderData;
typedef NovelRT::Graphics::ImageRect ImageRect;
typedef NovelRT::Graphics::RenderingSerivce RenderingService;
typedef NovelRT::Graphics::RenderObject RenderObject;
typedef NovelRT::Graphics::RGBAConfig RGBAConfig;
typedef NovelRT::Graphics::ShaderProgram ShaderProgram;
typedef NovelRT::Graphics::TextRect TextRect;

typedef NovelRT::Input::BasicInteractionRect BasicInteractionRect;
typedef NovelRT::Input::InteractionObject InteractionObject;
typedef NovelRT::Input::InteractionService InteractionService;
typedef NovelRT::Input::KeyCode KeyCode;
typedef NovelRT::Input::KeyState KeyState;

typedef NovelRT::Maths::GeoBounds GeoBounds;

typedef NovelRT::Timing::StepTimer StepTimer;

typedef NovelRT::Utilities::CommonArgs CommonArgs;
typedef NovelRT::Utilities::Misc Misc;

typedef NovelRT::Windowing::WindowingService WindowingService;



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
