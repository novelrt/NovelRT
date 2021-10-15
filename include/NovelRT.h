// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_H
#define NOVELRT_H

// clang-format off

#if !defined(__cplusplus)
  #define NOVELRT_C_API 1
#endif // !__cplusplus

#if defined(_WIN32) || defined(_WIN64)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#if defined(__cplusplus) && !defined(NOVELRT_C_API)
#define __STDC_WANT_LIB_EXT1__ 1

// stdlib
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

// Freetype
#include <ft2build.h>
#include FT_FREETYPE_H

// glad
#include <glad/glad.h>

// GLFW3
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

// OpenAL
#include <AL/al.h>
#include <AL/alc.h>

// LibSndfile
#include <sndfile.h>

#ifdef NOVELRT_INK
// nethost
#include "NovelRT/DotNet/coreclr_delegates.h"
#include "NovelRT/DotNet/hostfxr.h"
#endif

// libpng
#include <png.h>
#endif // __cplusplus

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
#ifdef NOVELRT_INK
  /**
   * @brief Contains features to interop with the .NET Core runtime.
   */
  namespace NovelRT::DotNet {
    typedef class RuntimeService RuntimeService;
  }
#endif
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
#ifdef NOVELRT_INK
  /**
   * @brief Contains bindings for Ink.
   */
  namespace NovelRT::Ink {
    typedef class InkService InkService;
    typedef class Story Story;
  }
#endif
  /**
   * @brief Contains input features, such as keyboard and mouse interactivity.
   */
  namespace NovelRT::Input {
    typedef class BasicInteractionRect BasicInteractionRect;
    typedef class InteractionObject InteractionObject;
    typedef class InteractionService InteractionService;
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

  //generic experimental files in root namespace
  #include "NovelRT/Experimental/EngineConfig.h"

  //enums
  #include "NovelRT/Input/KeyCode.h"
  #include "NovelRT/Input/KeyState.h"
  #include "NovelRT/Graphics/CameraFrameState.h"
  #include "NovelRT/Windowing/WindowMode.h"

  // Value types
  #include "NovelRT/Atom.h"
  #include "NovelRT/Timing/Timestamp.h"
  #include "NovelRT/Utilities/Event.h" //these have to exist up here due to include order issues
  #include "NovelRT/Utilities/Lazy.h"
  #include "NovelRT/Utilities/Misc.h"

  #include "NovelRT/Transform.h"

  #include "NovelRT/Animation/AnimatorPlayState.h"
  #include "NovelRT/Animation/SpriteAnimatorFrame.h"

  #include "NovelRT/Graphics/GraphicsCharacterRenderData.h"
  #include "NovelRT/Graphics/ImageData.h"
  #include "NovelRT/Graphics/ShaderProgram.h"
  #include "NovelRT/Graphics/RGBAColour.h"

  //Maths types
  #include "NovelRT/Maths/Maths.h"

  // Base Types
  #include "NovelRT/LoggingService.h" // this isn't in the services section due to include order/dependencies.
  #include "NovelRT/Timing/StepTimer.h"
  #include "NovelRT/NovelRunner.h"
  #include "NovelRT/WorldObject.h"

  // Animation types
  #include "NovelRT/Animation/SpriteAnimatorState.h"
  #include "NovelRT/Animation/SpriteAnimator.h"

  // ECS types
  #include "NovelRT/Ecs/Ecs.h"

  // Exception types
  #include "NovelRT/Exceptions/Exceptions.h"

  // Graphics types
  #include "NovelRT/Graphics/GraphicsCharacterRenderDataHelper.h"
  #include "NovelRT/Graphics/Camera.h"
  #include "NovelRT/Graphics/Texture.h"
  #include "NovelRT/Graphics/FontSet.h"
  #include "NovelRT/Graphics/RenderObject.h"
  #include "NovelRT/Graphics/BasicFillRect.h"
  #include "NovelRT/Graphics/ImageRect.h"
  #include "NovelRT/Graphics/TextRect.h"

  // Experimental types
  #include "NovelRT/Experimental/Graphics/Graphics.h"
  #include "NovelRT/Experimental/Graphics/Vulkan/Graphics.Vulkan.h"
  #include "NovelRT/Experimental/Threading/Threading.h"
  #include "NovelRT/Experimental/Windowing/Windowing.h"
  #include "NovelRT/Experimental/Windowing/Glfw/Windowing.Glfw.h"

#ifdef NOVELRT_INK
  // Ink types
  #include "NovelRT/Ink/Story.h"
  #include "NovelRT/Ink/InkService.h"
#endif

  // Input types
  #include "NovelRT/Input/InteractionObject.h"
  #include "NovelRT/Input/BasicInteractionRect.h"
  #include "NovelRT/Input/KeyStateFrameChangeLog.h"

  // Plugin Management types
  #include "NovelRT/PluginManagement/PluginManagement.h"

 // ResourceManagement types
  #include "NovelRT/ResourceManagement/ResourceManagement.h"
  #include "NovelRT/ResourceManagement/Desktop/ResourceManagement.Desktop.h"

  // Engine service types
  #include "NovelRT/Audio/AudioService.h"
  #include "NovelRT/DebugService.h"
#ifdef NOVELRT_INK
  #include "NovelRT/DotNet/RuntimeService.h"
#endif
  #include "NovelRT/Input/InteractionService.h"
  #include "NovelRT/Windowing/WindowingService.h"
  #include "NovelRT/Graphics/RenderingService.h"

  // Scene Graph types
  #include "NovelRT/SceneGraph/SceneGraph.h"
#endif // __cplusplus

#if defined(NOVELRT_C_API)
  #include "NovelRT.Interop/NrtTypedefs.h"

  // Core
  #include "NovelRT.Interop/NrtDebugService.h"
  #include "NovelRT.Interop/NrtErrorHandling.h"
  #include "NovelRT.Interop/NrtLoggingService.h"
  #include "NovelRT.Interop/NrtNovelRunner.h"
  #include "NovelRT.Interop/NrtTransform.h"

  // Animation
  #include "NovelRT.Interop/Animation/NrtSpriteAnimator.h"
  #include "NovelRT.Interop/Animation/NrtSpriteAnimatorFrame.h"
  #include "NovelRT.Interop/Animation/NrtSpriteAnimatorState.h"

  // Audio
  #include "NovelRT.Interop/Audio/NrtAudioService.h"

#ifdef NOVELRT_INK
  // DotNet
  #include "NovelRT.Interop/DotNet/NrtRuntimeService.h"
#endif

  // Ecs
  #include "NovelRT.Interop/Ecs/NrtCatalogue.h"
  #include "NovelRT.Interop/Ecs/NrtComponentBufferMemoryContainer.h"
  #include "NovelRT.Interop/Ecs/NrtComponentCache.h"
  #include "NovelRT.Interop/Ecs/NrtEntityCache.h"
  #include "NovelRT.Interop/Ecs/NrtEntityIdVector.h"
  #include "NovelRT.Interop/Ecs/NrtSparseSetMemoryContainer.h"
  #include "NovelRT.Interop/Ecs/NrtSystemScheduler.h"
  #include "NovelRT.Interop/Ecs/NrtUnsafeComponentView.h"

  // Graphics
  #include "NovelRT.Interop/Graphics/NrtBasicFillRect.h"
  #include "NovelRT.Interop/Graphics/NrtCamera.h"
  #include "NovelRT.Interop/Graphics/NrtFontSet.h"
  #include "NovelRT.Interop/Graphics/NrtImageRect.h"
  #include "NovelRT.Interop/Graphics/NrtRenderingService.h"
  #include "NovelRT.Interop/Graphics/NrtRGBAColour.h"
  #include "NovelRT.Interop/Graphics/NrtTextRect.h"
  #include "NovelRT.Interop/Graphics/NrtTexture.h"

#ifdef NOVELRT_INK
  // Ink
  #include "NovelRT.Interop/Ink/NrtInkService.h"
  #include "NovelRT.Interop/Ink/NrtStory.h"
#endif

  // Input
  #include "NovelRT.Interop/Input/NrtBasicInteractionRect.h"
  #include "NovelRT.Interop/Input/NrtInteractionService.h"
  #include "NovelRT.Interop/Input/NrtKeyStateFrameChangeLog.h"

  // Maths
  #include "NovelRT.Interop/Maths/NrtGeoBounds.h"
  #include "NovelRT.Interop/Maths/NrtGeoMatrix4x4F.h"
  #include "NovelRT.Interop/Maths/NrtGeoVector2F.h"
  #include "NovelRT.Interop/Maths/NrtGeoVector3F.h"
  #include "NovelRT.Interop/Maths/NrtGeoVector4F.h"
  #include "NovelRT.Interop/Maths/NrtQuadTree.h"
  #include "NovelRT.Interop/Maths/NrtQuadTreePoint.h"

  // SceneGraph
  #include "NovelRT.Interop/SceneGraph/NrtQuadTreeNode.h"
  #include "NovelRT.Interop/SceneGraph/NrtQuadTreeScenePoint.h"
  #include "NovelRT.Interop/SceneGraph/NrtRenderObjectNode.h"
  #include "NovelRT.Interop/SceneGraph/NrtScene.h"
  #include "NovelRT.Interop/SceneGraph/NrtSceneNode.h"
  #include "NovelRT.Interop/SceneGraph/NrtSceneNodeBreadthFirstIterator.h"
  #include "NovelRT.Interop/SceneGraph/NrtSceneNodeDepthFirstIterator.h"

  // Timing
  #include "NovelRT.Interop/Timing/NrtStepTimer.h"
  #include "NovelRT.Interop/Timing/NrtTimestamp.h"

  // Utilities
  #include "NovelRT.Interop/Utilities/NrtMisc.h"

  // Windowing
  #include "NovelRT.Interop/Windowing/NrtWindowingService.h"
#endif

// clang-format on

#endif // !NOVELRT_H
