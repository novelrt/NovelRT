set(RESOURCES_FILES
  Fonts/Gayathri-Regular.ttf
  Fonts/Raleway-Regular.ttf

  Images/novel-chan.png
  Images/novel-chan-white-bg.png
  Images/test.png
  Images/uwu.png

  Scripts/avg.lua
  Scripts/story.ink
  Scripts/story.json

  Shaders/frag.spv
  Shaders/vert.spv
  Shaders/ImguiVert.spv
  Shaders/ImguiPixel.spv


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
