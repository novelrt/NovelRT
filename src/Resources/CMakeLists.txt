include(CopyDependencyOutputs)

set(NovelRT_RESX
Fonts/Gayathri-Regular.ttf Fonts/Raleway-Regular.ttf

Images/novel-chan.png


Shaders/BasicFragmentShader.glsl Shaders/BasicVertexShader.glsl
Shaders/FontFragmentShader.glsl Shaders/FontVertexShader.glsl
Shaders/TexturedFragmentShader.glsl Shaders/TexturedVertexShader.glsl
)

if(NOVELRT_SUPPORT_LUA)
  list(APPEND NOVELRT_RESX
    Scripts/avg.lua
  )
endif()

string(REPLACE "${CMAKE_BINARY_DIR}/" "" _local_path "${CMAKE_CURRENT_BINARY_DIR}")
mark_as_advanced(_local_path)

foreach(file IN LISTS NovelRT_RESX)
  add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/Resources/${file}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/${file}" "${CMAKE_CURRENT_BINARY_DIR}/Resources/${file}"
    MAIN_DEPENDENCY ${file}
    COMMENT "Generating ${_local_path}/Resources/${file}")
endforeach()

list(APPEND _NovelRT_Resources ${NovelRT_RESX})
list(TRANSFORM _NovelRT_Resources PREPEND "${CMAKE_CURRENT_BINARY_DIR}/Resources/")
mark_as_advanced(_NovelRT_Resources)

add_custom_target(NovelRT_Resources
  DEPENDS ${_NovelRT_Resources}
  SOURCES ${NovelRT_RESX})
add_dependency_outputs(NovelRT_Resources ${_NovelRT_Resources})
