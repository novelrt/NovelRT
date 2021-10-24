set(RESOURCES_FILES
  Fonts/Gayathri-Regular.ttf
  Fonts/Raleway-Regular.ttf

  Images/novel-chan.png

  Scripts/avg.lua
  Scripts/story.ink
  Scripts/story.json

  Shaders/BasicFragmentShader.glsl
  Shaders/BasicVertexShader.glsl
  Shaders/FontFragmentShader.glsl
  Shaders/FontVertexShader.glsl
  Shaders/TexturedFragmentShader.glsl
  Shaders/TexturedVertexShader.glsl
  Shaders/frag.spv
  Shaders/vert.spv

  Sounds/waltz.ogg
  Sounds/lazer.ogg
  Sounds/nani.ogg
  Sounds/goat.ogg
)

foreach(resource ${RESOURCES_FILES})
  configure_file(${resource} Resources/${resource} COPYONLY)
endforeach()

add_executable(Resources IMPORTED GLOBAL)
set_target_properties(Resources
  PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/Resources/IF_YOU_SEE_THIS_YOU_TRIED_TO_RUN_THE_RESOURCES_TARGET
)

