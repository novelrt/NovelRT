set(SOURCES
  main.cpp
)

add_executable(VulkanRender ${SOURCES})
add_dependencies(VulkanRender Resources)
target_link_libraries(VulkanRender
  PRIVATE
    Engine
)
target_compile_definitions(VulkanRender PUBLIC ${NOVELRT_PLATFORM_COMPILE_DEFINITIONS})

copy_build_products(VulkanRender
  DEPENDENCY Resources
  TARGET_LOCATION $<TARGET_FILE_DIR:VulkanRender>/Resources
)
CopyRuntimeDependencies(VulkanRender DEPENDENCY Engine)
