include(CopyBuildProducts)

set(SOURCES
  main.cpp
)

add_executable(Simple ${SOURCES})
add_dependencies(Simple Resources)
target_link_libraries(Simple
  PRIVATE
    Engine
)

copy_build_products(Simple
  DEPENDENCY Resources
  TARGET_LOCATION $<TARGET_FILE_DIR:Simple>/Resources

  DEPENDENCY Engine
  TARGET_LOCATION $<TARGET_FILE_DIR:Simple>

  DEPENDENCY Dotnet
  TARGET_LOCATION $<TARGET_FILE_DIR:Simple>/dotnet
  CONDITION NOVELRT_INCLUDE_INK

  DEPENDENCY Dotnet
  DEPENDENCY_FILES nethost.dll
  TARGET_LOCATION $<TARGET_FILE_DIR:Simple>
  CONDITION NOVELRT_INCLUDE_INK AND WIN32
)

if(NOVELRT_INCLUDE_INK)
  add_dependencies(Simple Dotnet)
  target_compile_definitions(Simple PRIVATE NOVELRT_INK)
endif()
