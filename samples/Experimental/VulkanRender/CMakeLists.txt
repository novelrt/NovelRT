include(CopyBuildProducts)

set(SOURCES
  main.cpp
)

add_executable(VulkanRender ${SOURCES})
add_dependencies(VulkanRender Resources)
target_link_libraries(VulkanRender
  PRIVATE
    Engine
)

copy_build_products(VulkanRender
  DEPENDENCY Resources
  TARGET_LOCATION $<TARGET_FILE_DIR:VulkanRender>/Resources

  DEPENDENCY Engine
  TARGET_LOCATION $<TARGET_FILE_DIR:VulkanRender>
)
