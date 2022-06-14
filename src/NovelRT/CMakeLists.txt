find_package(BZip2 ${NOVELRT_BZIP2_VERSION} REQUIRED)
find_package(flac ${NOVELRT_FLAC_VERSION} REQUIRED)
find_package(Freetype ${NOVELRT_FREETYPE_VERSION} REQUIRED)
find_package(Ogg ${NOVELRT_OGG_VERSION} REQUIRED)
find_package(OpenAL ${NOVELRT_OPENAL_VERSION} REQUIRED)
find_package(Opus ${NOVELRT_Opus_VERSION} REQUIRED)
find_package(PNG ${NOVELRT_PNG_VERSION} REQUIRED)
find_package(SndFile ${NOVELRT_SNDFILE_VERISON} REQUIRED)
find_package(Vorbis ${NOVELRT_VORBIS_VERSION} REQUIRED)
find_package(Vulkan ${NOVELRT_VULKAN_VERSION} REQUIRED)
if(APPLE)
  find_package(moltenvk REQUIRED)
endif()



set(SOURCES
  Atom.cpp

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

  EngineConfig.cpp

  Input/Glfw/GlfwInputDevice.cpp
  Input/Glfw/GlfwInputPluginProvider.cpp
  Input/NovelKey.cpp

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

  Threading/VolatileState.cpp
  Windowing/Glfw/GlfwWindowingDevice.cpp
  Windowing/Glfw/GlfwWindowingPluginProvider.cpp

  LoggingService.cpp

  Maths/GeoBounds.cpp
  Maths/QuadTree.cpp

  Persistence/Chapter.cpp
  Persistence/Persistable.cpp

  PluginManagement/TemporaryFnPtrs.cpp

  ResourceManagement/Desktop/DesktopResourceLoader.cpp
  ResourceManagement/Desktop/DesktopResourceManagementPluginProvider.cpp

  Timing/StepTimer.cpp

  Utilities/Misc.cpp
  )

add_library(Engine SHARED ${SOURCES})

set_property(TARGET Engine PROPERTY OUTPUT_NAME "$<IF:$<CONFIG:Release>,NovelRT,NovelRT-$<CONFIG>>")

if(WIN32)
  set_property(TARGET Engine PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
endif()
target_compile_features(Engine PUBLIC cxx_std_17)
target_include_directories(Engine
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${glm_SOURCE_DIR}>
    $<BUILD_INTERFACE:${GSL_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(MSVC)
  target_compile_definitions(Engine PUBLIC -D__TBB_NO_IMPLICIT_LINKAGE=$<IF:$<CONFIG:DEBUG>,1,0>)
  target_compile_options(Engine
    PRIVATE
      /W4
      /WX
      /wd4611
      /MP
  )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(Engine
    PRIVATE
      -pedantic
      -pedantic-errors
      -Wall
      -Wextra
      -Werror
      -Wno-float-equal
      -Wno-padded
  )
else()
  target_compile_options(Engine
    PRIVATE
      -pedantic
      -pedantic-errors
      -Wall
      -Wextra
      -Werror
      -Wno-c++98-compat
      -Wno-c++98-compat-pedantic
      -Wno-float-equal
      -Wno-padded
      -Wno-reserved-id-macro
  )
endif()

target_link_libraries(Engine
  PUBLIC
    BZip2::BZip2
    FLAC::FLAC
    Freetype::Freetype
    glfw
    Ogg::Ogg
    OpenAL::OpenAL
    Opus::Opus
    PNG::PNG
    SndFile::SndFile
    spdlog
    TBB::tbb
    Vorbis::Vorbis
    Vulkan::Vulkan
    runtime # Fabulist support - target name is vague. Fix later. :]
    jsoncons
)

install(
  TARGETS Engine
  EXPORT NovelRT
  DESTINATION lib
  RUNTIME DESTINATION bin
)
#Workaround due to hierarchy destruction when installing by TARGETS
install(
  DIRECTORY ${CMAKE_SOURCE_DIR}/include/NovelRT/
  DESTINATION include/NovelRT
  FILES_MATCHING PATTERN "*.h"
)

if(WIN32)
  target_link_libraries(Engine
    PUBLIC
      Winmm
  )

  # I hate CMake I hate it I hate it I hate it
  # (work around for CMAKE REFUSING TO COPY NECESSARY FILES FOR DEBUGGING MAKING IT IMPOSSIBLE TO DEBUG)
  add_custom_command(TARGET Engine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
      ${CMAKE_BINARY_DIR}/thirdparty
      $<TARGET_FILE_DIR:Engine>)
  add_custom_command(TARGET Engine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:tbb>
    $<TARGET_FILE_DIR:Engine>/$<TARGET_FILE_NAME:tbb>)
  file(GLOB libs RELATIVE ${CMAKE_BINARY_DIR}/thirdparty ${CMAKE_BINARY_DIR}/thirdparty/*.dll)
  set_target_properties(Engine PROPERTIES RESOURCE "${libs};$<TARGET_FILE_NAME:tbb>")
elseif(APPLE)
  add_custom_command(TARGET Engine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_BINARY_DIR}/thirdparty
          $<TARGET_FILE_DIR:Engine>)
  add_custom_command(TARGET Engine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
          $<TARGET_FILE:tbb>
          $<TARGET_FILE_DIR:Engine>/$<TARGET_FILE_NAME:tbb>)
  file(GLOB libs RELATIVE ${CMAKE_BINARY_DIR}/thirdparty ${CMAKE_BINARY_DIR}/thirdparty/*.dylib)
  set_target_properties(Engine PROPERTIES RESOURCE "${libs};$<TARGET_FILE_NAME:tbb>")
endif()

