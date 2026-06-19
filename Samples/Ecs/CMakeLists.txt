include(CMakeDependentOption)

cmake_dependent_option(NOVELRT_BUILD_SAMPLES_ECS_GRAPHICS "Build NovelRT ECS Graphics sample" ON "NOVELRT_BUILD_SAMPLES_ECS" OFF)
cmake_dependent_option(NOVELRT_BUILD_SAMPLES_ECS_SCRIPTING "Build NovelRT ECS Scripting sample" ON "NOVELRT_BUILD_SAMPLES_ECS" OFF)
cmake_dependent_option(NOVELRT_BUILD_SAMPLES_ECS_FABULISTRENDERING "Build NovelRT Ecs FabulistRendering sample" ON "NOVELRT_BUILD_SAMPLES_ECS" OFF)

if(NOVELRT_BUILD_SAMPLES_ECS_GRAPHICS)
  add_subdirectory(Graphics)
endif()

if(NOVELRT_BUILD_SAMPLES_ECS_SCRIPTING)
  add_subdirectory(Scripting)
endif()

if(NOVELRT_BUILD_SAMPLES_ECS_SCRIPTING)
  add_subdirectory(FabulistRendering)
endif()
