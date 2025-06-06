set(RESOURCES_FILES
  novel-chan.icns
  
  Fonts/Gayathri-Regular.ttf
  Fonts/Raleway-Regular.ttf

  Images/novel-chan.png
  Images/novel-chan-white-bg.png
  Images/test.png
  Images/uwu.png

  Scripts/question.json

  Shaders/BasicFragmentShader.glsl
  Shaders/BasicVertexShader.glsl
  Shaders/FontFragmentShader.glsl
  Shaders/FontVertexShader.glsl
  Shaders/TexturedFragmentShader.glsl
  Shaders/TexturedVertexShader.glsl
  Shaders/frag.spv
  Shaders/vert.spv
  Shaders/vulkanrenderfrag.spv
  Shaders/vulkanrendervert.spv
  Shaders/imgui_frag.spv
  Shaders/imgui_vert.spv
  Shaders/imgui_shader.vert
  Shaders/imgui_shader.frag

  Sounds/goat.wav
  Sounds/uwu.ogg
)

foreach(resource ${RESOURCES_FILES})
  configure_file(${resource} ${resource} COPYONLY)
endforeach()

add_library(Resources INTERFACE IMPORTED GLOBAL)
set_target_properties(Resources
  PROPERTIES
    RESOURCE "${RESOURCES_FILES}"
)

install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/Resources/Shaders/
  DESTINATION bin/Resources/Shaders
  FILES_MATCHING PATTERN "*.spv"
)
