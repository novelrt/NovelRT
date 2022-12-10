set(CORE_SOURCES

  Atom.cpp
  LoggingService.cpp
  EngineConfig.cpp

  Audio/AudioService.cpp

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

  Graphics/GraphicsMemoryBlock.cpp
  Graphics/GraphicsMemoryBlockCollection.cpp
  Graphics/GraphicsPipeline.cpp
  Graphics/GraphicsPipelineInput.cpp
  Graphics/GraphicsPipelineInputElement.cpp
  Graphics/GraphicsPipelineResource.cpp
  Graphics/GraphicsPipelineSignature.cpp
  Graphics/GraphicsResourceManager.cpp
  Graphics/ShaderProgram.cpp
  Graphics/Vulkan/VulkanGraphicsAdapter.cpp
  Graphics/Vulkan/VulkanGraphicsAdapterSelector.cpp
  Graphics/Vulkan/VulkanGraphicsBuffer.cpp
  Graphics/Vulkan/VulkanGraphicsContext.cpp
  Graphics/Vulkan/VulkanGraphicsDevice.cpp
  Graphics/Vulkan/VulkanGraphicsFence.cpp
  Graphics/Vulkan/VulkanGraphicsMemoryAllocator.cpp
  Graphics/Vulkan/VulkanGraphicsMemoryBlock.cpp
  Graphics/Vulkan/VulkanGraphicsMemoryBlockCollection.cpp
  Graphics/Vulkan/VulkanGraphicsPipeline.cpp
  Graphics/Vulkan/VulkanGraphicsPipelineSignature.cpp
  Graphics/Vulkan/VulkanGraphicsPluginProvider.cpp
  Graphics/Vulkan/VulkanGraphicsProvider.cpp
  Graphics/Vulkan/VulkanGraphicsSurfaceContext.cpp
  Graphics/Vulkan/VulkanGraphicsTexture.cpp
  Graphics/Vulkan/VulkanShaderProgram.cpp

  ${imgui_SOURCE_DIR}/imgui.cpp
  ${imgui_SOURCE_DIR}/imgui_demo.cpp
  ${imgui_SOURCE_DIR}/imgui_draw.cpp
  ${imgui_SOURCE_DIR}/imgui_tables.cpp
  ${imgui_SOURCE_DIR}/imgui_widgets.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_vulkan.cpp

  Input/Glfw/GlfwInputDevice.cpp
  Input/Glfw/GlfwInputPluginProvider.cpp
  Input/NovelKey.cpp

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
set_property(TARGET Engine PROPERTY VERSION ${PROJECT_VERSION})


if(GENERATOR_IS_MULTI_CONFIG)
  set_target_properties(Engine PROPERTIES OUTPUT_NAME "$<IF:$<CONFIG:Release>,NovelRT,NovelRT-$<CONFIG>" )
else()
  if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(ENGINE_NAME "NovelRT")
  elseif(CMAKE_BUILD_TYPE)
    set(ENGINE_NAME "NovelRT-${CMAKE_BUILD_TYPE}")
  else()
    set(ENGINE_NAME "NovelRT-\$<CONFIG>")
  endif()
  set_target_properties(Engine PROPERTIES OUTPUT_NAME ${ENGINE_NAME})
endif()

if(APPLE)
  get_target_property(ENGINE_NAME_FINAL Engine OUTPUT_NAME)
  set_target_properties(Engine PROPERTIES
    SOVERSION ${PROJECT_VERSION}
    NO_SONAME TRUE
  )
  target_link_options(Engine PRIVATE $<$<CXX_COMPILER_ID:AppleClang>:-install_name @rpath/lib${ENGINE_NAME_FINAL}.dylib>)
elseif(WIN32)
  set_property(TARGET Engine PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
endif()

target_compile_features(Engine PUBLIC cxx_std_17)
target_include_directories(Engine
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:$<TARGET_PROPERTY:glm::glm,INTERFACE_INCLUDE_DIRECTORIES>>
    $<BUILD_INTERFACE:$<TARGET_PROPERTY:Microsoft.GSL::GSL,INTERFACE_INCLUDE_DIRECTORIES>>
    $<BUILD_INTERFACE:${imgui_SOURCE_DIR}>
    $<BUILD_INTERFACE:${imgui_SOURCE_DIR}/backends>
    $<INSTALL_INTERFACE:include>
)

target_compile_options(Engine
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<CXX_COMPILER_ID:MSVC>:/WX>
    $<$<CXX_COMPILER_ID:MSVC>:/wd4611>
    $<$<CXX_COMPILER_ID:MSVC>:/MP>

    $<$<CXX_COMPILER_ID:GNU>:-pedantic>
    $<$<CXX_COMPILER_ID:GNU>:-pedantic-errors>
    $<$<CXX_COMPILER_ID:GNU>:-Wall>
    $<$<CXX_COMPILER_ID:GNU>:-Wextra>
    $<$<CXX_COMPILER_ID:GNU>:-Werror>
    $<$<CXX_COMPILER_ID:GNU>:-Wno-float-equal>
    $<$<CXX_COMPILER_ID:GNU>:-Wno-padded>

    $<$<CXX_COMPILER_ID:Clang>:-pedantic>
    $<$<CXX_COMPILER_ID:Clang>:-pedantic-errors>
    $<$<CXX_COMPILER_ID:Clang>:-Wall>
    $<$<CXX_COMPILER_ID:Clang>:-Wextra>
    $<$<CXX_COMPILER_ID:Clang>:-Werror>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-c++98-compat>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-c++98-compat-pedantic>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-float-equal>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-padded>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-reserved-id-macro>

    $<$<CXX_COMPILER_ID:AppleClang>:-pedantic>
    $<$<CXX_COMPILER_ID:AppleClang>:-pedantic-errors>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wall>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wextra>
    $<$<CXX_COMPILER_ID:AppleClang>:-Werror>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wno-c++98-compat>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wno-c++98-compat-pedantic>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wno-float-equal>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wno-padded>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wno-reserved-id-macro>
)

if(MSVC)
  set_property(TARGET Engine PROPERTY WINDOWS_EXPORT_ALL_SYMBOLS ON)
  target_compile_definitions(Engine PUBLIC -D__TBB_NO_IMPLICIT_LINKAGE=$<IF:$<CONFIG:DEBUG>,1,0>)
endif()

target_link_libraries(Engine
  PUBLIC
    Vulkan::Vulkan
    TBB::tbb
    OpenAL::OpenAL
    SndFile::sndfile
    glfw
    png
    spdlog::spdlog
    nlohmann_json::nlohmann_json
    stduuid
    fabulist::runtime
    Vorbis::vorbis
    Vorbis::vorbisenc
    FLAC::FLAC
    Opus::opus
    Ogg::ogg
    $<$<CXX_COMPILER_ID:MSVC>:Winmm>
    $<$<BOOL:${APPLE}>:${COREFOUNDATION}>
)

if(NOVELRT_INSTALL)
  install(
    TARGETS Engine
    EXPORT NovelRT
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    FRAMEWORK DESTINATION lib
  )
endif()

