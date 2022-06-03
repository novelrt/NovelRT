set(SOURCES
  main.cpp
  )

add_executable(FabulistTest ${SOURCES})
add_dependencies(FabulistTest Resources)
target_link_libraries(FabulistTest
  PRIVATE
  Engine
  )

copy_build_products(FabulistTest
  DEPENDENCY Resources
  TARGET_LOCATION $<TARGET_FILE_DIR:FabulistTest>/Resources

  DEPENDENCY Engine
  TARGET_LOCATION $<TARGET_FILE_DIR:FabulistTest>
  )
