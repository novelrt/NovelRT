set(SOURCES
  main.cpp
)

add_executable(InputEcsSample ${SOURCES})
add_dependencies(InputEcsSample Resources)
target_link_libraries(InputEcsSample
  PRIVATE
    Engine
)
target_compile_definitions(InputEcsSample PUBLIC ${NOVELRT_PLATFORM_COMPILE_DEFINITIONS})

copy_build_products(InputEcsSample
  DEPENDENCY Resources
  TARGET_LOCATION $<TARGET_FILE_DIR:InputEcsSample>/Resources
)
CopyRuntimeDependencies(InputEcsSample Engine)
