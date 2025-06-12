include(CMakeDependentOption)

cmake_dependent_option(NOVELRT_BUILD_SAMPLES_EXPERIMENTAL_AUDIO "Build NovelRT experimental Audio sample" ON "NOVELRT_BUILD_SAMPLES_EXPERIMENTAL" OFF)
cmake_dependent_option(NOVELRT_BUILD_SAMPLES_EXPERIMENTAL_VULKANRENDER "Build NovelRT experimental VulkanRender sample" ON "NOVELRT_BUILD_SAMPLES_EXPERIMENTAL" OFF)
cmake_dependent_option(NOVELRT_BUILD_SAMPLES_EXPERIMENTAL_IMGUI "Build NovelRT experimental ImGui sample" ON "NOVELRT_BUILD_SAMPLES_EXPERIMENTAL" OFF)

if(NOVELRT_BUILD_SAMPLES_EXPERIMENTAL_AUDIO)
  add_subdirectory(Audio)
endif()

if(NOVELRT_BUILD_SAMPLES_EXPERIMENTAL_VULKANRENDER)
  add_subdirectory(VulkanRender)
endif()

if(NOVELRT_BUILD_SAMPLES_EXPERIMENTAL_IMGUI)
  add_subdirectory(ImGui)
endif()
