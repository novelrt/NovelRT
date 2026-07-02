include(CMakeDependentOption)

cmake_dependent_option(NOVELRT_BUILD_SAMPLES_ECS_GRAPHICS "Build NovelRT ECS Graphics sample" ON "NOVELRT_BUILD_SAMPLES_ECS" OFF)
cmake_dependent_option(NOVELRT_BUILD_SAMPLES_ECS_SCRIPTING "Build NovelRT ECS Scripting sample" ON "NOVELRT_BUILD_SAMPLES_ECS" OFF)
cmake_dependent_option(NOVELRT_BUILD_SAMPLES_ECS_UI "Build NovelRT ECS UI sample" ON "NOVELRT_BUILD_SAMPLES_ECS" OFF)
cmake_dependent_option(NOVELRT_BUILD_SAMPLES_ECS_AUDIO "Build NovelRT ECS Audio sample" ON "NOVELRT_BUILD_SAMPLES_ECS" OFF)

if(NOVELRT_BUILD_SAMPLES_ECS_GRAPHICS)
  add_subdirectory(Graphics)
endif()

if(NOVELRT_BUILD_SAMPLES_ECS_UI)
  add_subdirectory(UI)
endif()

if(NOVELRT_BUILD_SAMPLES_ECS_SCRIPTING)
  add_subdirectory(Scripting)
endif()

if(NOVELRT_BUILD_SAMPLES_ECS_AUDIO)
  add_subdirectory(Audio)
endif()
