set(RESOURCES_FILES
  Fonts/Gayathri-Regular.ttf
  Fonts/Raleway-Regular.ttf

  Images/novel-chan.png

  Scripts/avg.lua
  Scripts/story.json

  Shaders/BasicFragmentShader.glsl
  Shaders/BasicVertexShader.glsl
  Shaders/FontFragmentShader.glsl
  Shaders/FontVertexShader.glsl
  Shaders/TexturedFragmentShader.glsl
  Shaders/TexturedVertexShader.glsl
)

foreach(resource ${RESOURCES_FILES})
  configure_file(${resource} Resources/${resource} COPYONLY)
endforeach()

add_executable(Resources IMPORTED GLOBAL)
set_target_properties(Resources
  PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/Resources/IF_YOU_SEE_THIS_YOU_TRIED_TO_RUN_THE_RESOURCES_TARGET
)

