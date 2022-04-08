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

if(NOVELRT_INCLUDE_CONAN_PATHS AND (WIN32 OR APPLE))
  add_dependencies(VulkanRender ThirdParty)
  copy_build_products(VulkanRender
    DEPENDENCY Resources
    TARGET_LOCATION $<TARGET_FILE_DIR:VulkanRender>/Resources

    DEPENDENCY Engine
    TARGET_LOCATION $<TARGET_FILE_DIR:VulkanRender>

    DEPENDENCY ThirdParty
    TARGET_LOCATION $<TARGET_FILE_DIR:VulkanRender>
  )
else()
  copy_build_products(VulkanRender
    DEPENDENCY Resources
    TARGET_LOCATION $<TARGET_FILE_DIR:VulkanRender>/Resources

    DEPENDENCY Engine
    TARGET_LOCATION $<TARGET_FILE_DIR:VulkanRender>
  )
endif()
