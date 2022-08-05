set(SOURCES
  main.cpp
  )

add_executable(PersistenceSample ${SOURCES})
add_dependencies(PersistenceSample Resources)
target_link_libraries(PersistenceSample
  PRIVATE
  Engine
  )
target_compile_definitions(PersistenceSample PUBLIC  ${NOVELRT_PLATFORM_COMPILE_DEFINITIONS})

copy_build_products(PersistenceSample
  DEPENDENCY Resources
  TARGET_LOCATION $<TARGET_FILE_DIR:PersistenceSample>/Resources
)
CopyRuntimeDependencies(PersistenceSample DEPENDENCY Engine)
