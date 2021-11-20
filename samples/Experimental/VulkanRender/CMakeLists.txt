set(SOURCES
  main.cpp
)

add_executable(VulkanRender ${SOURCES})
add_dependencies(VulkanRender Dotnet Resources)
target_link_libraries(VulkanRender
  PRIVATE
    Engine
)

copy_build_products(VulkanRender
  DEPENDENCY Resources
  TARGET_LOCATION $<TARGET_FILE_DIR:VulkanRender>/Resources

  DEPENDENCY Engine
  TARGET_LOCATION $<TARGET_FILE_DIR:VulkanRender>

  DEPENDENCY Dotnet
  TARGET_LOCATION $<TARGET_FILE_DIR:VulkanRender>/dotnet
  CONDITION NOVELRT_INCLUDE_INK

  DEPENDENCY Dotnet
  DEPENDENCY_FILES nethost.dll
  TARGET_LOCATION $<TARGET_FILE_DIR:VulkanRender>
  CONDITION NOVELRT_INCLUDE_INK AND WIN32
)
