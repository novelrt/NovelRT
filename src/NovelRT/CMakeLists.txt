set(CORE_SOURCES

  Atom.cpp
  LoggingService.cpp
  EngineConfig.cpp

  Ecs/Catalogue.cpp
  Ecs/ComponentBufferMemoryContainer.cpp
  Ecs/ComponentCache.cpp
  Ecs/EcsUtils.cpp
  Ecs/EntityCache.cpp
  Ecs/EntityGraphView.cpp
  Ecs/LinkedEntityListView.cpp
  Ecs/SparseSetMemoryContainer.cpp
  Ecs/SystemScheduler.cpp
  Ecs/UnsafeComponentView.cpp
  Ecs/Graphics/DefaultRenderingSystem.cpp
  Ecs/Audio/AudioSystem.cpp
  Ecs/Input/InputSystem.cpp
  # Ecs/Narrative/NarrativePlayerSystem.cpp

  Maths/GeoBounds.cpp
  Maths/QuadTree.cpp

  Persistence/Chapter.cpp
  Persistence/Persistable.cpp
  Persistence/Graphics/RenderingComponentPersistenceRule.cpp

  PluginManagement/TemporaryFnPtrs.cpp

  ResourceManagement/ResourceLoader.cpp
  ResourceManagement/Desktop/DesktopResourceLoader.cpp
  ResourceManagement/Desktop/DesktopResourceManagementPluginProvider.cpp

  Threading/VolatileState.cpp

  Timing/StepTimer.cpp

  Utilities/Misc.cpp

  Windowing/Glfw/GlfwWindowingDevice.cpp
  Windowing/Glfw/GlfwWindowingPluginProvider.cpp
)

add_library(Engine SHARED ${CORE_SOURCES})
add_library(NovelRT::Engine ALIAS Engine)
set_target_properties(Engine
  PROPERTIES
    OUTPUT_NAME "$<IF:$<CONFIG:Release>,NovelRT,NovelRT-$<CONFIG>>"
    SOVERSION "${PROJECT_VERSION}"
    VERSION "${PROJECT_VERSION}"
    WINDOWS_EXPORT_ALL_SYMBOLS ON)

target_compile_features(Engine PUBLIC cxx_std_17)
target_include_directories(Engine
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:$<TARGET_PROPERTY:glm::glm,INTERFACE_INCLUDE_DIRECTORIES>>
    $<BUILD_INTERFACE:$<TARGET_PROPERTY:Microsoft.GSL::GSL,INTERFACE_INCLUDE_DIRECTORIES>>
   # $<BUILD_INTERFACE:$<TARGET_PROPERTY:VulkanMemoryAllocator::VulkanMemoryAllocator,INTERFACE_INCLUDE_DIRECTORIES>>
    $<INSTALL_INTERFACE:include>
)

target_compile_options(Engine PRIVATE ${NOVELRT_TARGET_COMPILE_OPTIONS})
target_compile_definitions(Engine PUBLIC ${NOVELRT_TARGET_COMPILE_DEFS})

target_link_libraries(Engine
  PUBLIC
  # runtime
  tbb
  sndfile
  samplerate
  glfw
  png
  spdlog
  nlohmann_json
  stduuid
  vorbis
  vorbisenc
  FLAC
  opus
  ogg
  $<$<BOOL:$<STREQUAL:${NOVELRT_TARGET},Linux>>:OpenAL>
  NovelRT-Graphics
  NovelRT-Audio
  NovelRT-Input
)

if(${NOVELRT_TARGET} STREQUAL "macOS")
target_link_libraries(Engine
  PRIVATE
  "-framework AVFoundation"
)
endif()

if(NOVELRT_INSTALL)
  install(
    TARGETS Engine
    EXPORT NovelRTConfig
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    FRAMEWORK DESTINATION lib
  )
endif()

