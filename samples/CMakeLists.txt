include(CopyDependencyOutputs)

set(NovelRT_Samples_SRCS
main.cpp
)

add_executable(NovelRT_Samples ${NovelRT_Samples_SRCS})
add_dependencies(NovelRT_Samples NovelRT)

target_link_libraries(NovelRT_Samples NovelRT)
copy_dependency_outputs(NovelRT_Samples NovelRT _output_files_list)
add_dependency_outputs(NovelRT_Samples ${_output_files_list})
install_dependency_outputs(
  FILES ${_output_files_list}
  DESTINATION bin)

mark_as_advanced(_output_files_list)

install(
  TARGETS NovelRT_Samples
  RUNTIME DESTINATION bin)
