include(CMakeDependentOption)

cmake_dependent_option(NOVELRT_BUILD_SAMPLES_ECS_GRAPHICS "Build NovelRT ECS Graphics sample" ON "NOVELRT_BUILD_SAMPLES_ECS" OFF)

if(NOVELRT_BUILD_SAMPLES_ECS_GRAPHICS)
  add_subdirectory(Graphics)
endif()
