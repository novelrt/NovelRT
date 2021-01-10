// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_H
#define NOVELRT_H

#if defined(NDEBUG)
#define unused(x)  (void)(x)
#else
#define unused(x)  (void)(0)
#endif

//stdlib
#define __STDC_WANT_LIB_EXT1__ 1
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <tuple>
#include <typeinfo>
#include <type_traits>
#include <vector>

#if defined(_WIN32) || defined(_WIN64)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

//Freetype
#include <ft2build.h>
#include FT_FREETYPE_H

//glad
#include <glad/glad.h>

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
#include "NovelRT/DotNet/coreclr_delegates.h"
#include "NovelRT/DotNet/hostfxr.h"

//spdlog
#if defined(_MSC_VER)
  #pragma warning(push)
  #pragma warning(disable:4275)
#endif

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/async.h>

#if defined(_MSC_VER)
  #pragma warning(pop)
#endif

//libpng
#include <png.h>

/**
 * @brief NovelRT is a cross-platform, flexible Visual Novel and 2D game engine.
 * It is aimed at designers and developers alike, however many of the designer tools and features we have on our roadmap have yet to be implemented.
 */
namespace NovelRT {
  typedef class Atom Atom;
  typedef class DebugService DebugService;
  typedef class LoggingService LoggingService;
  typedef class NovelRunner NovelRunner;
}
/**
 * @brief Contains animation features.
 */
namespace NovelRT::Animation {
  typedef class SpriteAnimator SpriteAnimator;
}
/***
 * @brief Contains audio features, such as playing audio, and managing audio resources.
 */
namespace NovelRT::Audio {
  typedef std::vector<ALuint> SoundBank;
  typedef std::vector<ALuint> MusicBank;
  typedef class AudioService AudioService;
}
/**
 * @brief Contains features to interop with the .NET Core runtime.
 */
namespace NovelRT::DotNet {
  typedef class RuntimeService RuntimeService;
}
/**
 * @brief Contains graphics features, such as rendering, textures, cameras, etc.
 */
namespace NovelRT::Graphics {
  typedef class Texture Texture;
  typedef class BasicFillRect BasicFillRect;
  typedef class Camera Camera;
  typedef class ImageRect ImageRect;
  typedef class RenderingService RenderingService;
  typedef class RenderObject RenderObject;
  typedef class TextRect TextRect;
}
/**
 * @brief Contains bindings for Ink.
 */
namespace NovelRT::Ink {
  typedef class InkService InkService;
  typedef class Story Story;
}
/**
 * @brief Contains input features, such as keyboard and mouse interactivity.
 */
namespace NovelRT::Input {
  typedef class BasicInteractionRect BasicInteractionRect;
  typedef class InteractionObject InteractionObject;
  typedef class InteractionService InteractionService;
}
/**
 * @brief Contains scene graph features.
 */
namespace NovelRT::SceneGraph {
  typedef class QuadTreeNode QuadTreeNode;
  typedef class QuadTreeScenePoint QuadTreeScenePoint;
  typedef class RenderObjectNode RenderObjectNode;
  typedef class Scene Scene;
  typedef class SceneNode SceneNode;
}
/**
 * @brief Contains timing features, such as timers.
 */
namespace NovelRT::Timing {
  typedef class StepTimer StepTimer;
}
/**
 * @brief Contains windowing features.
 */
namespace NovelRT::Windowing {
  typedef class WindowingService WindowingService;
}

//enums
#include "NovelRT/Input/KeyCode.h"
#include "NovelRT/Input/KeyState.h"
#include "NovelRT/Graphics/CameraFrameState.h"

//value types
#include "NovelRT/Atom.h"
#include "NovelRT/Timing/Timestamp.h"
#include "NovelRT/Utilities/Event.h" //these have to exist up here due to include order issues
#include "NovelRT/Utilities/Lazy.h"
#include "NovelRT/Utilities/Misc.h"

#include "NovelRT/Animation/AnimatorPlayState.h"
#include "NovelRT/Animation/SpriteAnimatorFrame.h"
#include "NovelRT/Maths/GeoVector2F.h"
#include "NovelRT/Maths/GeoVector3F.h"
#include "NovelRT/Maths/GeoVector4F.h"
#include "NovelRT/Maths/GeoMatrix4x4F.h"
#include "NovelRT/Maths/GeoBounds.h"
#include "NovelRT/Maths/QuadTreePoint.h"
#include "NovelRT/Maths/QuadTree.h"
#include "NovelRT/Transform.h"
#include "NovelRT/Graphics/GraphicsCharacterRenderData.h"
#include "NovelRT/Graphics/ImageData.h"
#include "NovelRT/Graphics/ShaderProgram.h"
#include "NovelRT/Graphics/RGBAConfig.h"

//base types
#include "NovelRT/LoggingService.h" //this isn't in the services section due to include order/dependencies.
#include "NovelRT/Timing/StepTimer.h"
#include "NovelRT/NovelRunner.h"
#include "NovelRT/WorldObject.h"

//Animation types
#include "NovelRT/Animation/SpriteAnimatorState.h"
#include "NovelRT/Animation/SpriteAnimator.h"

//ECS types
#include "NovelRT/Ecs/Ecs.h"

// Exception types
#include "NovelRT/Exceptions/Exceptions.h"

//Graphics types
#include "NovelRT/Graphics/Camera.h"
#include "NovelRT/Graphics/Texture.h"
#include "NovelRT/Graphics/FontSet.h"
#include "NovelRT/Graphics/RenderObject.h"
#include "NovelRT/Graphics/BasicFillRect.h"
#include "NovelRT/Graphics/GraphicsCharacterRenderDataHelper.h"
#include "NovelRT/Graphics/ImageRect.h"
#include "NovelRT/Graphics/TextRect.h"

//Ink types
#include "NovelRT/Ink/Story.h"
#include "NovelRT/Ink/InkService.h"

//Input types
#include "NovelRT/Input/InteractionObject.h"
#include "NovelRT/Input/BasicInteractionRect.h"
#include "NovelRT/Input/KeyStateFrameChangeLog.h"

//Engine service types
#include "NovelRT/Audio/AudioService.h"
#include "NovelRT/DebugService.h"
#include "NovelRT/DotNet/RuntimeService.h"
#include "NovelRT/Input/InteractionService.h"
#include "NovelRT/Windowing/WindowingService.h"
#include "NovelRT/Graphics/RenderingService.h"

// Scene Graph types
#include "NovelRT/SceneGraph/SceneNode.h"
#include "NovelRT/SceneGraph/RenderObjectNode.h"
#include "NovelRT/SceneGraph/QuadTreeScenePoint.h"
#include "NovelRT/SceneGraph/QuadTreeNode.h"
#include "NovelRT/SceneGraph/Scene.h"

#endif //!NOVELRT_H
