if(NOT DEFINED NOVELRT_LIB_SUFFIX)
  set(NOVELRT_LIB_SUFFIX "" CACHE INTERNAL "")
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

if(APPLE)
  #Other OSes build fine but Apple builds in Alphabetical order which causes link failures
  add_dependencies(Engine ${NOVELRT_VULKAN_DEPS})
  set(NOVELRT_LIB_SUFFIX "dylib")
elseif(WIN32)
  set_property(TARGET Engine PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
  target_link_libraries(Engine
    PUBLIC
      Winmm
  )
  set(NOVELRT_LIB_SUFFIX "dll")
endif()

target_compile_features(Engine PUBLIC cxx_std_17)
target_include_directories(Engine
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(MSVC)
  set_property(TARGET Engine PROPERTY WINDOWS_EXPORT_ALL_SYMBOLS ON)
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
    fabulist::runtime
    freetype
    glfw
    glm::glm
    OpenAL::OpenAL
    png
    spdlog::spdlog
    TBB::tbb
    Vulkan::Vulkan
    jsoncons
    stduuid
    SndFile::sndfile
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

  # I hate CMake I hate it I hate it I hate it
  # (work around for CMAKE REFUSING TO COPY NECESSARY FILES FOR DEBUGGING MAKING IT IMPOSSIBLE TO DEBUG)
  #add_custom_command(TARGET Engine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
  #    ${CMAKE_BINARY_DIR}/thirdparty
  #    $<TARGET_FILE_DIR:Engine>)
  #add_custom_command(TARGET Engine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
  #  $<TARGET_FILE_DIR:OpenAL>
  #  $<TARGET_FILE_DIR:Engine>)
  #add_custom_command(TARGET Engine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
  #  $<TARGET_FILE_DIR:sndfile>
  #  $<TARGET_FILE_DIR:Engine>)
  #add_custom_command(TARGET Engine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
  #  $<TARGET_FILE_DIR:tbb>
  #  $<TARGET_FILE_DIR:Engine>)
  #if(NOT NOVELRT_VULKAN_SDK)
  #  add_custom_command(TARGET Engine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
  #    $<TARGET_FILE:${NOVELRT_VULKAN_TARGET}>
  #    $<TARGET_FILE_DIR:Engine>/$<TARGET_FILE_NAME:${NOVELRT_VULKAN_TARGET}>)
  #  if(APPLE)
  #    add_custom_command(TARGET Engine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
  #      ${NOVELRT_MOLTENVK_DYLIB_PATH}
  #      $<TARGET_FILE_DIR:Engine>)
  #    set(NOVELRT_ADDITIONAL_LIBS_APPLE ON)
  #    set(NOVELRT_ADDITIONAL_LIBS "${NOVELRT_MOLTENVK_LIBTOCOPY};${NOVELRT_MOLTENVK_ICDTOCOPY}")
  #  endif()
  #endif()
  #file(GLOB libs RELATIVE
  #  ${CMAKE_BINARY_DIR}/thirdparty ${CMAKE_BINARY_DIR}/thirdparty/*.${NOVELRT_LIB_SUFFIX})

  #set_target_properties(Engine
  #  PROPERTIES
  #    RESOURCE "$<TARGET_FILE_NAME:OpenAL>;$<TARGET_FILE_NAME:sndfile>;$<TARGET_FILE_NAME:tbb>;$<$<NOT:$<BOOL:${NOVELRT_VULKAN_SDK}>>:$<TARGET_FILE_NAME:${NOVELRT_VULKAN_TARGET}>>;$<$<BOOL:${NOVELRT_ADDITIONAL_LIBS_APPLE}>:${NOVELRT_ADDITIONAL_LIBS}>")

