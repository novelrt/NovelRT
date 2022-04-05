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
    typedef class LoggingService LoggingService;
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
  #include "EngineConfig.h"

  // Value types
  #include "Atom.h"
  #include "Timing/Timestamp.h"
  #include "Utilities/Event.h" //these have to exist up here due to include order issues
  #include "Utilities/Lazy.h"
  #include "Utilities/Misc.h"

  #include "Graphics/RGBAColour.h"

  //Maths types
  #include "Maths/Maths.h"

  // Base Types
  #include "LoggingService.h" // this isn't in the services section due to include order/dependencies.
  #include "Timing/StepTimer.h"

  // Audio types
  #include "Audio/Audio.h"

  // ECS types
  #include "Ecs/Ecs.h"

  // Exception types
  #include "Exceptions/Exceptions.h"

  // Experimental types
  #include "Graphics/Graphics.h"
  #include "Graphics/Vulkan/Graphics.Vulkan.h"
  #include "Threading/Threading.h"
  #include "Windowing/Windowing.h"
  #include "Windowing/Glfw/Windowing.Glfw.h"
  #include "Input/Input.h"
  #include "Input/Glfw/Input.Glfw.h"


  // Plugin Management types
  #include "PluginManagement/PluginManagement.h"

 // ResourceManagement types
  #include "ResourceManagement/ResourceManagement.h"
  #include "ResourceManagement/Desktop/ResourceManagement.Desktop.h"

  // Engine service types
  #include "Audio/AudioService.h"

  // Scene Graph types
  #include "SceneGraph/SceneGraph.h"
#endif // __cplusplus

#if defined(NOVELRT_C_API)
  #include "NovelRT.Interop/NrtTypedefs.h"

  // Core
  #include "NovelRT.Interop/NrtErrorHandling.h"
  #include "NovelRT.Interop/NrtLoggingService.h"

  // Audio
  #include "NovelRT.Interop/Audio/NrtAudio.h"

  // Ecs
  #include "NovelRT.Interop/Ecs/NrtCatalogue.h"
  #include "NovelRT.Interop/Ecs/NrtComponentBufferMemoryContainer.h"
  #include "NovelRT.Interop/Ecs/NrtComponentCache.h"
  #include "NovelRT.Interop/Ecs/NrtEntityCache.h"
  #include "NovelRT.Interop/Ecs/NrtEntityIdVector.h"
  #include "NovelRT.Interop/Ecs/NrtSparseSetMemoryContainer.h"
  #include "NovelRT.Interop/Ecs/NrtSystemScheduler.h"
  #include "NovelRT.Interop/Ecs/NrtUnsafeComponentView.h"
  #include "NovelRT.Interop/Ecs/Audio/NrtEcsAudio.h"

#ifdef NOVELRT_INK
  // Ink
  #include "NovelRT.Interop/Ink/NrtInkService.h"
  #include "NovelRT.Interop/Ink/NrtStory.h"
#endif

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
