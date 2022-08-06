if(NOVELRT_BUILD_SHARED_LIBS)
  set(type SHARED)
else()
  set(type STATIC)
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

add_library(Engine ${type} ${SOURCES})
set_property(TARGET Engine PROPERTY OUTPUT_NAME "$<IF:$<CONFIG:Debug>,NovelRT-$<CONFIG>,NovelRT>")

target_include_directories(Engine
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${glm_SOURCE_DIR}>
    $<BUILD_INTERFACE:${gsl_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${stduuid_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${jsoncons_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${libpng_SOURCE_DIR}>
    $<BUILD_INTERFACE:${libpng_BINARY_DIR}>
    # $<BUILD_INTERFACE:$<TARGET_PROPERTY:Vulkan::Headers,INTERFACE_INCLUDE_DIRECTORIES>>
)

# if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
#   target_compile_options(Engine
#     PRIVATE
#       -pedantic
#       -pedantic-errors
#       -Wall
#       -Wextra
#       -Werror
#       -Wno-float-equal
#       -Wno-padded
#   )
# else()
#   target_compile_options(Engine
#     PRIVATE
#       -pedantic
#       -pedantic-errors
#       -Wall
#       -Wextra
#       -Werror
#       -Wno-c++98-compat
#       -Wno-c++98-compat-pedantic
#       -Wno-float-equal
#       -Wno-padded
#       -Wno-reserved-id-macro
#   )
# endif()

target_link_libraries(Engine PUBLIC
  Fabulist::Runtime
  Freetype::Freetype
  GLFW::glfw
  OpenAL::OpenAL
  PNG::PNG
  Spdlog::spdlog
  TBB::tbb
  Vulkan::Vulkan
  Sndfile::sndfile
)
target_compile_definitions(Engine PUBLIC ${NOVELRT_PLATFORM_COMPILE_DEFINITIONS})
target_compile_options(Engine PUBLIC ${NOVELRT_PLATFORM_COMPILE_OPTIONS})

get_target_property(NOVELRT_LINK_LIBS Engine LINK_LIBRARIES)
target_link_libraries(Engine PUBLIC ${NOVELRT_PLATFORM_LINK_LIBRARIES})

if(NOVELRT_INSTALL)
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

  install(CODE
    "set(to_remove \${CMAKE_INSTALL_PREFIX}/include/PROJECT_NAME)
    message(STATUS \"Removing: \${to_remove}\")
    execute_process(COMMAND ${CMAKE_COMMAND} \"-E\" \"remove_directory\" \${to_remove})"
  )

  foreach(lib IN LISTS NOVELRT_LINK_LIBS)
    list(APPEND NOVELRT_INSTALLATION_LIBS $<TARGET_LINKER_FILE:${lib}>)
    if(NOT WIN32)
      get_target_property(targetType ${lib} TYPE)
      if(targetType STREQUAL "SHARED_LIBRARY")
        list(APPEND NOVELRT_INSTALLATION_FILES $<TARGET_FILE:${lib}>)
      endif()
    endif()
  endforeach()

  if(WIN32)
    list(APPEND NOVELRT_INSTALLATION_FILES $<TARGET_RUNTIME_DLLS:Engine>)
  endif()

  install(FILES ${NOVELRT_INSTALLATION_LIBS}
    DESTINATION lib
  )
  install(FILES ${NOVELRT_INSTALLATION_FILES}
    DESTINATION bin
  )
endif()
