set(SOURCES
  main.cpp
)

add_executable(UIEventExample ${SOURCES})
add_dependencies(UIEventExample Resources)
target_link_libraries(UIEventExample
  PRIVATE
    Engine
)
target_compile_definitions(UIEventExample PUBLIC ${NOVELRT_PLATFORM_COMPILE_DEFINITIONS})

copy_build_products(UIEventExample
  DEPENDENCY Resources
  TARGET_LOCATION $<TARGET_FILE_DIR:UIEventExample>/Resources
)
CopyRuntimeDependencies(UIEventExample DEPENDENCY Engine)
