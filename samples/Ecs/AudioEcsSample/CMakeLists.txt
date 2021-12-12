include(CopyBuildProducts)

set(SOURCES
  main.cpp
)

add_executable(AudioEcsSample ${SOURCES})
add_dependencies(AudioEcsSample Resources)
target_link_libraries(AudioEcsSample
  PRIVATE
    Engine
)

copy_build_products(AudioEcsSample
  DEPENDENCY Resources
  TARGET_LOCATION $<TARGET_FILE_DIR:AudioEcsSample>/Resources

  DEPENDENCY Engine
  TARGET_LOCATION $<TARGET_FILE_DIR:AudioEcsSample>

  DEPENDENCY Dotnet
  TARGET_LOCATION $<TARGET_FILE_DIR:AudioEcsSample>/dotnet
  CONDITION NOVELRT_INCLUDE_INK

  DEPENDENCY Dotnet
  DEPENDENCY_FILES nethost.dll
  TARGET_LOCATION $<TARGET_FILE_DIR:AudioEcsSample>
  CONDITION NOVELRT_INCLUDE_INK AND WIN32
)

if(NOVELRT_INCLUDE_INK)
  add_dependencies(AudioEcsSample Dotnet)
  target_compile_definitions(AudioEcsSample PRIVATE NOVELRT_INK)
endif()
