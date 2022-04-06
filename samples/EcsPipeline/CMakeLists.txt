set(SOURCES
  main.cpp
  )

add_executable(EcsPipeline ${SOURCES})
add_dependencies(EcsPipeline Resources)
target_link_libraries(EcsPipeline
  PRIVATE
  Engine
  )

copy_build_products(EcsPipeline
  DEPENDENCY Resources
  TARGET_LOCATION $<TARGET_FILE_DIR:EcsPipeline>/Resources

  DEPENDENCY Engine
  TARGET_LOCATION $<TARGET_FILE_DIR:EcsPipeline>
  DROP_PATH ON
  )
