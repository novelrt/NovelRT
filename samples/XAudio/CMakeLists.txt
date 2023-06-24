include(CopyBuildProducts)
include(CopyRuntimeDependencies)

add_executable(XAudioSample main.cpp)
add_dependencies(XAudioSample Resources)
target_link_libraries(XAudioSample
  PRIVATE
    Engine
)

copy_build_products(XAudioSample
  DEPENDENCY Resources
  TARGET_LOCATION $<IF:$<BOOL:${APPLE}>,$<TARGET_FILE_DIR:XAudioSample>/../Resources,$<TARGET_FILE_DIR:XAudioSample>/Resources>
)

copy_runtime_dependencies(XAudioSample
    DEPENDENCY Engine
)
