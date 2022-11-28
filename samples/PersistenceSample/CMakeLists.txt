set(SOURCES
  main.cpp
)

add_executable(PersistenceSample ${SOURCES})
add_dependencies(PersistenceSample Resources)
target_link_libraries(PersistenceSample
  PRIVATE
    Engine
)

copy_build_products(PersistenceSample
  DEPENDENCY Resources
  TARGET_LOCATION $<TARGET_FILE_DIR:PersistenceSample>/Resources
)
copy_runtime_dependencies(PersistenceSample
  DEPENDENCY Engine
)
