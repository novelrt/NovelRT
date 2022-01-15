find_package(ffmpeg)

set(SOURCES
  main.cpp
)

add_executable(BadApple ${SOURCES})
add_dependencies(BadApple Dotnet Engine Resources)
target_link_libraries(BadApple
  PRIVATE
    Engine
    ffmpeg::avformat
    ffmpeg::avcodec
    ffmpeg::swscale
)

copy_build_products(BadApple
  DEPENDENCY Resources
  TARGET_LOCATION $<TARGET_FILE_DIR:BadApple>/Resources

  DEPENDENCY Engine
  TARGET_LOCATION $<TARGET_FILE_DIR:BadApple>

  DEPENDENCY Dotnet
  TARGET_LOCATION $<TARGET_FILE_DIR:BadApple>/dotnet
  CONDITION NOVELRT_INCLUDE_INK

  DEPENDENCY Dotnet
  DEPENDENCY_FILES nethost.dll
  TARGET_LOCATION $<TARGET_FILE_DIR:BadApple>
  CONDITION NOVELRT_INCLUDE_INK AND WIN32
)
