// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_H
#define NOVELRT_H

// clang-format off

#if defined(NDEBUG)
#define unused(x)  (void)(x)
#else
#define unused(x)  (void)(0)
#endif

// stdlib
#if defined(__cplusplus) && !defined(NOVELRT_C_API)
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
#endif

#if defined(_WIN32) || defined(_WIN64)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

// Freetype
#include <ft2build.h>
#include FT_FREETYPE_H

// glad
#include <glad/glad.h>

// GLFW3
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

// OpenAL
#include <AL/al.h>
#include <AL/alc.h>

// LibSndfile
#include <sndfile.h>

// nethost
#include "NovelRT/DotNet/coreclr_delegates.h"
#include "NovelRT/DotNet/hostfxr.h"

// spdlog
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

// libpng
#include <png.h>

#if defined(__cplusplus) && !defined(NOVELRT_C_API)
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
#endif // __cplusplus

#if defined(__cplusplus) && !defined(NOVELRT_C_API)
  /**
   * @brief Contains animation features.
   */
  namespace NovelRT::Animation {
    typedef class SpriteAnimator SpriteAnimator;
  }
#else // !__cplusplus
  #include "NovelRT.Interop/Animation/NrtAnimationTypedefs.h"
#endif // __cplusplus

#if defined(__cplusplus) && !defined(NOVELRT_C_API)
  /***
   * @brief Contains audio features, such as playing audio, and managing audio resources.
   */
  namespace NovelRT::Audio {
    typedef std::vector<ALuint> SoundBank;
    typedef std::vector<ALuint> MusicBank;
    typedef class AudioService AudioService;
  }
#endif // __cplusplus

#if defined(__cplusplus) && !defined(NOVELRT_C_API)
  /**
   * @brief Contains features to interop with the .NET Core runtime.
   */
  namespace NovelRT::DotNet {
    typedef class RuntimeService RuntimeService;
  }
#else // !__cplusplus
  #include "NovelRT.Interop/DotNet/NrtRuntimeTypedefs.h"
#endif // __cplusplus

#if defined(__cplusplus) && !defined(NOVELRT_C_API)
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
#else // !__cplusplus
  #include "NovelRT.Interop/Graphics/NrtGraphicsTypedefs.h"
#endif // __cplusplus

#if defined(__cplusplus) && !defined(NOVELRT_C_API)
  /**
   * @brief Contains bindings for Ink.
   */
  namespace NovelRT::Ink {
    typedef class InkService InkService;
    typedef class Story Story;
  }
#endif // __cplusplus

#if defined(__cplusplus) && !defined(NOVELRT_C_API)
  /**
   * @brief Contains input features, such as keyboard and mouse interactivity.
   */
  namespace NovelRT::Input {
    typedef class BasicInteractionRect BasicInteractionRect;
    typedef class InteractionObject InteractionObject;
    typedef class InteractionService InteractionService;
  }
#endif // __cplusplus

#if defined(__cplusplus) && !defined(NOVELRT_C_API)
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
#else // !__cplusplus
  #include "NovelRT.Interop/SceneGraph/NrtSceneGraphTypedefs.h"
#endif // __cplusplus

#if defined(__cplusplus) && !defined(NOVELRT_C_API)
  /**
   * @brief Contains timing features, such as timers.
   */
  namespace NovelRT::Timing {
    typedef class StepTimer StepTimer;
  }
#endif // __cplusplus

#if defined(__cplusplus) && !defined(NOVELRT_C_API)
  /**
   * @brief Contains windowing features.
   */
  namespace NovelRT::Windowing {
    typedef class WindowingService WindowingService;
  }
#endif // __cplusplus

//enums
#if defined(__cplusplus) && !defined(NOVELRT_C_API)
  #include "NovelRT/Input/KeyCode.h"
  #include "NovelRT/Input/KeyState.h"
  #include "NovelRT/Graphics/CameraFrameState.h"
  #include "NovelRT/Windowing/WindowMode.h"
#else // !__cplusplus
  #include "NovelRT.Interop/NrtLogLevel.h"
  #include "NovelRT.Interop/Input/NrtKeyCode.h"
  #include "NovelRT.Interop/Input/NrtKeyState.h"
  #include "NovelRT.Interop/Graphics/NrtCameraFrameState.h"
#endif // __cplusplus

// Value types
#if defined(__cplusplus) && !defined(NOVELRT_C_API)
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
#else // !__cplusplus
  #include "NovelRT.Interop/NrtInteropUtils.h"
  #include "NovelRT.Interop/Timing/NrtTimestamp.h"
  #include "NovelRT.Interop/Utilities/NrtCommonEvents.h"
  #include "NovelRT.Interop/Utilities/NrtMisc.h"

  #include "NovelRT.Interop/Animation/NrtAnimatorPlayState.h"
  #include "NovelRT.Interop/Animation/NrtSpriteAnimatorFrame.h"
  #include "NovelRT.Interop/Maths/NrtGeoVector2F.h"
  #include "NovelRT.Interop/Maths/NrtGeoVector3F.h"
  #include "NovelRT.Interop/Maths/NrtGeoVector4F.h"
  #include "NovelRT.Interop/Maths/NrtGeoMatrix4x4F.h"
  #include "NovelRT.Interop/Maths/NrtGeoBounds.h"
  #include "NovelRT.Interop/Maths/NrtQuadTreePoint.h"
  #include "NovelRT.Interop/Maths/NrtQuadTree.h"
  #include "NovelRT.Interop/NrtTransform.h"
  #include "NovelRT.Interop/Graphics/NrtRGBAConfig.h"
#endif // __cplusplus

// Base Types
#if defined(__cplusplus) && !defined(NOVELRT_C_API)
  #include "NovelRT/LoggingService.h" // this isn't in the services section due to include order/dependencies.
  #include "NovelRT/Timing/StepTimer.h"
  #include "NovelRT/NovelRunner.h"
  #include "NovelRT/WorldObject.h"
#else // !__cplusplus
  #include "NovelRT.Interop/NrtLoggingService.h" // this isn't in the services section due to include order/dependencies.
  #include "NovelRT.Interop/Timing/NrtStepTimer.h"
  #include "NovelRT.Interop/NrtNovelRunner.h"
#endif // __cplusplus

// Animation types
#if defined(__cplusplus) && !defined(NOVELRT_C_API)
  #include "NovelRT/Animation/SpriteAnimatorState.h"
  #include "NovelRT/Animation/SpriteAnimator.h"
#else // !__cplusplus
  #include "NovelRT.Interop/Animation/NrtSpriteAnimatorState.h"
  #include "NovelRT.Interop/Animation/NrtSpriteAnimator.h"
#endif // __cplusplus

// ECS types
#if defined(__cplusplus) && !defined(NOVELRT_C_API)
  #include "NovelRT/Ecs/Ecs.h"
#else // !__cplusplus
  #include "NovelRT.Interop/Ecs/NrtEcs.h"
#endif // __cplusplus

// Exception types
#if defined(__cplusplus) && !defined(NOVELRT_C_API)
  #include "NovelRT/Exceptions/Exceptions.h"
#endif // __cplusplus

// Graphics types
#if defined(__cplusplus) && !defined(NOVELRT_C_API)
  #include "NovelRT/Graphics/Camera.h"
  #include "NovelRT/Graphics/Texture.h"
  #include "NovelRT/Graphics/FontSet.h"
  #include "NovelRT/Graphics/RenderObject.h"
  #include "NovelRT/Graphics/BasicFillRect.h"
  #include "NovelRT/Graphics/GraphicsCharacterRenderDataHelper.h"
  #include "NovelRT/Graphics/ImageRect.h"
  #include "NovelRT/Graphics/TextRect.h"
#else // !__cplusplus
  #include "NovelRT.Interop/Graphics/NrtCamera.h"
  #include "NovelRT.Interop/Graphics/NrtTexture.h"
  #include "NovelRT.Interop/Graphics/NrtFontSet.h"
  #include "NovelRT.Interop/Graphics/NrtBasicFillRect.h"
  #include "NovelRT.Interop/Graphics/NrtImageRect.h"
  #include "NovelRT.Interop/Graphics/NrtTextRect.h"
#endif // __cplusplus

// Ink types
#if defined(__cplusplus) && !defined(NOVELRT_C_API)
  #include "NovelRT/Ink/Story.h"
  #include "NovelRT/Ink/InkService.h"
#else // !__cplusplus
  #include "NovelRT.Interop/Ink/NrtStory.h"
  #include "NovelRT.Interop/Ink/NrtInkService.h"
#endif // __cplusplus

// Input types
#if defined(__cplusplus) && !defined(NOVELRT_C_API)
  #include "NovelRT/Input/InteractionObject.h"
  #include "NovelRT/Input/BasicInteractionRect.h"
  #include "NovelRT/Input/KeyStateFrameChangeLog.h"
#else // !__cplusplus
  #include "NovelRT.Interop/Input/NrtBasicInteractionRect.h"
  #include "NovelRT.Interop/Input/NrtKeyStateFrameChangeLog.h"
#endif // __cplusplus

// Engine service types
#if defined(__cplusplus) && !defined(NOVELRT_C_API)
  #include "NovelRT/Audio/AudioService.h"
  #include "NovelRT/DebugService.h"
  #include "NovelRT/DotNet/RuntimeService.h"
  #include "NovelRT/Input/InteractionService.h"
  #include "NovelRT/Windowing/WindowingService.h"
  #include "NovelRT/Graphics/RenderingService.h"
#else // !__cplusplus
  #include "NovelRT.Interop/Audio/NrtAudioService.h"
  #include "NovelRT.Interop/NrtDebugService.h"
  #include "NovelRT.Interop/DotNet/NrtRuntimeService.h"
  #include "NovelRT.Interop/Input/NrtInteractionService.h"
  #include "NovelRT.Interop/Windowing/NrtWindowingService.h"
  #include "NovelRT.Interop/Graphics/NrtRenderingService.h"
#endif // __cplusplus

// Scene Graph types
#if defined(__cplusplus) && !defined(NOVELRT_C_API)
  #include "NovelRT/SceneGraph/SceneNode.h"
  #include "NovelRT/SceneGraph/RenderObjectNode.h"
  #include "NovelRT/SceneGraph/QuadTreeScenePoint.h"
  #include "NovelRT/SceneGraph/QuadTreeNode.h"
  #include "NovelRT/SceneGraph/Scene.h"
#else // !__cplusplus
  #include "NovelRT.Interop/SceneGraph/NrtSceneNode.h"
  #include "NovelRT.Interop/SceneGraph/NrtSceneNodeBreadthFirstIterator.h"
  #include "NovelRT.Interop/SceneGraph/NrtSceneNodeDepthFirstIterator.h"
  #include "NovelRT.Interop/SceneGraph/NrtRenderObjectNode.h"
  #include "NovelRT.Interop/SceneGraph/NrtQuadTreeScenePoint.h"
  #include "NovelRT.Interop/SceneGraph/NrtQuadTreeNode.h"
  #include "NovelRT.Interop/SceneGraph/NrtScene.h"
#endif // __cplusplus

// clang-format on

#endif // !NOVELRT_H
