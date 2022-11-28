set(SOURCES
  main.cpp
)

add_executable(InputEcsSample ${SOURCES})
add_dependencies(InputEcsSample Resources)
target_link_libraries(InputEcsSample
  PRIVATE
    Engine
)

copy_build_products(InputEcsSample
  DEPENDENCY Resources
  TARGET_LOCATION $<TARGET_FILE_DIR:InputEcsSample>/Resources
)
copy_runtime_dependencies(InputEcsSample
  DEPENDENCY Engine
)
