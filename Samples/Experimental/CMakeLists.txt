include(CMakeDependentOption)

cmake_dependent_option(NOVELRT_BUILD_SAMPLES_EXPERIMENTAL_VULKANRENDER "Build NovelRT experimental VulkanRender sample" ON "NOVELRT_BUILD_SAMPLES_EXPERIMENTAL" OFF)

if(NOVELRT_BUILD_SAMPLES_EXPERIMENTAL_VULKANRENDER)
  add_subdirectory(VulkanRender)
endif()
