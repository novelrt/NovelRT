if(NOVELRT_VULKAN_SDK)
  find_package(Vulkan ${NOVELRT_VULKAN_VERSION} REQUIRED)
endif()
set(SOURCES
  main.cpp
  )

add_executable(FabulistTest ${SOURCES})
add_dependencies(FabulistTest Resources)
target_link_libraries(FabulistTest
  PRIVATE
  Engine
  )
target_compile_definitions(FabulistTest PUBLIC -DNOVELRT_MOLTENVK_VENDORED=$<IF:$<BOOL:${NOVELRT_MOLTENVK_VENDORED}>,1,0>)

copy_build_products(FabulistTest
  DEPENDENCY Resources
  TARGET_LOCATION $<TARGET_FILE_DIR:FabulistTest>/Resources

  DEPENDENCY Engine
  TARGET_LOCATION $<TARGET_FILE_DIR:FabulistTest>
  )
