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
  Sounds/laz0r.ogg
  Sounds/goat.ogg
)

foreach(resource ${RESOURCES_FILES})
  configure_file(${resource} ${resource} COPYONLY)
endforeach()

add_library(Resources INTERFACE IMPORTED GLOBAL)
set_target_properties(Resources
  PROPERTIES
    RESOURCE "${RESOURCES_FILES}"
)

