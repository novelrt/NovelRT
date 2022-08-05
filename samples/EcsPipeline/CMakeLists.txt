set(SOURCES
  main.cpp
)

add_executable(EcsPipeline ${SOURCES})
add_dependencies(EcsPipeline Resources)
target_link_libraries(EcsPipeline
  PRIVATE
    Engine
)
target_compile_definitions(EcsPipeline PUBLIC ${NOVELRT_PLATFORM_COMPILE_DEFINITIONS})

copy_build_products(EcsPipeline
  DEPENDENCY Resources
  TARGET_LOCATION $<TARGET_FILE_DIR:EcsPipeline>/Resources
)
CopyRuntimeDependencies(EcsPipeline
  DEPENDENCY Engine)

