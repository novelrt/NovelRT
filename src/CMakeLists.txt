find_package(Freetype REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(sdl2-mixer CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

# lua doesn't provide native cmake support
find_path(LUA_INCLUDE_DIR lua.h)
include_directories(${LUA_INCLUDE_DIR})

find_library(LUA_LIBRARY lua)
link_libraries(${LUA_LIBRARY})

find_package(Doxygen QUIET)

file(GLOB_RECURSE NOVELRT_LIB_HEADERS CONFIGURE_DEPENDS ../include/*.h)
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${NOVELRT_LIB_HEADERS})

file(GLOB_RECURSE NOVELRT_LIB_SOURCES CONFIGURE_DEPENDS NovelRT/*.cpp)
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${NOVELRT_LIB_SOURCES})

set(NOVELRT_LIB_LINK_LIBRARIES
  Freetype::Freetype
  glad::glad
  glfw
  glm
  SDL2::SDL2-static
  SDL2::SDL2_image
  SDL2::SDL2_mixer
  SDL2::SDL2main
  spdlog::spdlog
)

if(NOT WIN32)
  set(NOVELRT_LIB_LINK_LIBRARIES
    ${NOVELRT_LIB_LINK_LIBRARIES}
    m
    stdc++fs
  )
endif()

if (WIN32)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

add_library(NovelRT SHARED ${NOVELRT_LIB_HEADERS} ${NOVELRT_LIB_SOURCES})
target_link_libraries(NovelRT ${NOVELRT_LIB_LINK_LIBRARIES})

file(GLOB_RECURSE NOVELRT_LIB_FONT_RESOURCES CONFIGURE_DEPENDS Resources/Fonts/*.ttf)
file(GLOB_RECURSE NOVELRT_LIB_IMAGE_RESOURCES CONFIGURE_DEPENDS Resources/Images/*.png)
file(GLOB_RECURSE NOVELRT_LIB_SCRIPT_RESOURCES CONFIGURE_DEPENDS Resources/Scripts/*.lua)
file(GLOB_RECURSE NOVELRT_LIB_SHADER_RESOURCES CONFIGURE_DEPENDS Resources/Shaders/*.glsl)

add_custom_command(TARGET NovelRT POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:NovelRT>/Resources/Fonts
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${NOVELRT_LIB_FONT_RESOURCES} $<TARGET_FILE_DIR:NovelRT>/Resources/Fonts
  COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:NovelRT>/Resources/Images
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${NOVELRT_LIB_IMAGE_RESOURCES} $<TARGET_FILE_DIR:NovelRT>/Resources/Images
  COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:NovelRT>/Resources/Scripts
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${NOVELRT_LIB_SCRIPT_RESOURCES} $<TARGET_FILE_DIR:NovelRT>/Resources/Scripts
  COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:NovelRT>/Resources/Shaders
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${NOVELRT_LIB_SHADER_RESOURCES} $<TARGET_FILE_DIR:NovelRT>/Resources/Shaders
)

# Docs

if (DOXYGEN_FOUND)
  set(DOXYGEN_INPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
  set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/docs)
  set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/index.html)
  set(DOXYGEN_FAKE_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/__index.html)
  set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
  set(DOXYFILE_OUT ${DOXYGEN_OUTPUT_DIR}/Doxyfile)

  set(DOCS_IMAGES
    novel-chan_doxy.png
  )
  set(DOCS_RESOURCES
    ${DOCS_IMAGES}
  )

  #Replace variables inside @@ with the current values
  configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)
  file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR}) #Doxygen won't create this for us
  file(COPY ${DOCS_RESOURCES} DESTINATION ${DOXYGEN_OUTPUT_DIR})

  add_custom_command(OUTPUT
                       ${DOXYGEN_INDEX_FILE}
                       ${DOXYGEN_FAKE_INDEX_FILE}
                     COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
                     MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
                     COMMENT "Generating docs")

  add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})
endif (DOXYGEN_FOUND)
