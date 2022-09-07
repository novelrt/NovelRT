set(SOURCES
  main.cpp
)

add_executable(VulkanRender ${SOURCES})
add_dependencies(VulkanRender Resources)
target_link_libraries(VulkanRender
  PRIVATE
    Engine
)
target_compile_definitions(VulkanRender PUBLIC -DNOVELRT_MOLTENVK_VENDORED=$<IF:$<BOOL:${NOVELRT_MOLTENVK_VENDORED}>,1,0>)

copy_build_products(VulkanRender
  DEPENDENCY Resources
  TARGET_LOCATION $<TARGET_FILE_DIR:VulkanRender>/Resources
)
copy_runtime_dependencies(VulkanRender
  DEPENDENCY Engine
)
