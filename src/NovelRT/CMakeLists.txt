set(CORE_SOURCES

  Atom.cpp
  LoggingService.cpp
  EngineConfig.cpp

  #Audio/AudioService.cpp

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
  # Ecs/Audio/AudioSystem.cpp
  Ecs/Input/InputSystem.cpp
  Ecs/Narrative/NarrativePlayerSystem.cpp

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

  ${NOVELRT_ENGINE_PLATFORM_SOURCES}
)

add_library(Engine SHARED ${CORE_SOURCES})
set_property(TARGET Engine PROPERTY VERSION ${PROJECT_VERSION})
add_dependencies(Engine runtime compiler)


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
    $<INSTALL_INTERFACE:include>
)

target_compile_options(Engine PRIVATE ${NOVELRT_TARGET_COMPILE_OPTIONS})
target_compile_definitions(Engine PUBLIC ${NOVELRT_TARGET_COMPILE_DEFS})

target_link_libraries(Engine
  PUBLIC
    runtime
    ${NOVELRT_ENGINE_LINK_LIBS}
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

