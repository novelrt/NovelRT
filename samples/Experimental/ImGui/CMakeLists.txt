set(SOURCES
  main.cpp
)

if(APPLE)
  add_executable(ImGuiRender MACOSX_BUNDLE ${NOVELCHAN_ICON} ${SOURCES})
  set_target_properties(ImGuiRender
    PROPERTIES
      BUNDLE True
      MACOSX_BUNDLE_GUI_IDENTIFIER dev.novelrt.samples.ImGuiRender
      MACOS_BUNDLE_BUNDLE_NAME ImGuiRender
      MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
      MACOSX_BUNDLE_SHORT_VERION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
  )
else()
  add_executable(ImGuiRender ${SOURCES})
endif()
add_dependencies(ImGuiRender Resources)
target_link_libraries(ImGuiRender
  PRIVATE
    Engine
)

target_include_directories(ImGuiRender PRIVATE 
$<BUILD_INTERFACE:${imgui_SOURCE_DIR}>
$<BUILD_INTERFACE:${imgui_SOURCE_DIR}/backends>
)

copy_build_products(ImGuiRender
  DEPENDENCY Resources
  TARGET_LOCATION $<IF:$<BOOL:${APPLE}>,$<TARGET_FILE_DIR:ImGuiRender>/../Resources,$<TARGET_FILE_DIR:ImGuiRender>/Resources>
)

if(APPLE)
  copy_runtime_dependencies(ImGuiRender
    DEPENDENCY Engine
    LIBRARY Vulkan::MoltenVK
    LIBRARY Vorbis::vorbisenc
    LIBRARY Vorbis::vorbis
    LIBRARY FLAC::FLAC
    LIBRARY Opus::opus
    LIBRARY Ogg::ogg
    LIBRARY ZLIB::zlib
  )
  write_moltenvk_icd_file(ImGuiRender)
else()
  copy_runtime_dependencies(ImGuiRender
    DEPENDENCY Engine
  )
endif()
