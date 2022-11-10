include(CopyBuildProducts)
include(CopyRuntimeDependencies)
include(WriteMoltenVKICD)

if(APPLE)
  set(novelchan_icon ${PROJECT_SOURCE_DIR}/Resources/novel-chan.icns)
  set_source_files_properties(${novelchan_icon} PROPERTIES
    MACOSX_PACKAGE_LOCATION "Resources"
  )
  set(MACOSX_BUNDLE_ICON_FILE novel-chan.icns)
endif()

add_subdirectory(Experimental)
add_subdirectory(EcsPipeline)
add_subdirectory(InputEcsSample)
add_subdirectory(PersistenceSample)
add_subdirectory(UIEventExample)
add_subdirectory(FabulistTest)
add_subdirectory(AudioEcsSample)

add_custom_target(Samples
  DEPENDS
    VulkanRender
    EcsPipeline
    InputEcsSample
    PersistenceSample
    UIEventExample
    FabulistTest
    AudioEcsSample
)
