set(RESOURCES_FILES
  Fonts/Gayathri-Regular.ttf
  Fonts/Raleway-Regular.ttf

  Images/novel-chan.png

  Scripts/avg.lua

  Shaders/BasicFragmentShader.glsl
  Shaders/BasicVertexShader.glsl
  Shaders/FontFragmentShader.glsl
  Shaders/FontVertexShader.glsl
  Shaders/TexturedFragmentShader.glsl
  Shaders/TexturedVertexShader.glsl
)

set(RESOURCES_OUTPUTS)
foreach(resource ${RESOURCES_FILES})
  add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${resource}"
    DEPENDS "${CMAKE_CURRENT_LIST_DIR}/${resource}"
    COMMAND ${CMAKE_COMMAND} -E copy
      "${CMAKE_CURRENT_LIST_DIR}/${resource}"
      "${CMAKE_CURRENT_BINARY_DIR}/${resource}"
    VERBATIM
  )
  list(APPEND RESOURCES_OUTPUTS "${CMAKE_CURRENT_BINARY_DIR}/${resource}")
endforeach()

add_custom_target(Resources
  DEPENDS ${RESOURCES_OUTPUTS}
)

set_target_properties(Resources
  PROPERTIES
    ADDITIONAL_COPY_LOCAL_FILES "${RESOURCES_OUTPUTS}"
    ADDITIONAL_COPY_LOCAL_FILES_DESTINATION Resources
)

