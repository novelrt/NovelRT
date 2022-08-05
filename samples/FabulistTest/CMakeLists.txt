set(SOURCES
  main.cpp
)

add_executable(FabulistTest ${SOURCES})
add_dependencies(FabulistTest Resources)
target_link_libraries(FabulistTest
  PRIVATE
  Engine
  )
target_compile_definitions(FabulistTest PUBLIC ${NOVELRT_PLATFORM_COMPILE_DEFINITIONS})

copy_build_products(FabulistTest
  DEPENDENCY Resources
  TARGET_LOCATION $<TARGET_FILE_DIR:FabulistTest>/Resources
)
CopyRuntimeDependencies(FabulistTest DEPENDENCY Engine)
