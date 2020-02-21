function(copy_dependency_outputs target dependency)
  get_target_property(dependency_files_list ${dependency} COPY_FILES)
  get_target_property(dependency_binary_dir ${dependency} BINARY_DIR)

  string(REPLACE "${CMAKE_BINARY_DIR}/" "" local_path "${CMAKE_CURRENT_BINARY_DIR}")

  foreach(input ${dependency_files_list})
    if(NOVELRT_GENERATOR_IS_MULTI_CONFIG)
      string(REPLACE "${dependency_binary_dir}/" "" output "${input}")
      string(REPLACE "${CMAKE_CFG_INTDIR}/" "" output "${output}")

      list(APPEND outputs "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${output}")

      add_custom_command(
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${output}"
        COMMAND ${CMAKE_COMMAND} -E copy "${input}" "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${output}"
        COMMENT "Generating ${local_path}/${CMAKE_CFG_INTDIR}/${output}")
    else()
      string(REPLACE "${dependency_binary_dir}/" "" output "${input}")

      list(APPEND outputs "${CMAKE_CURRENT_BINARY_DIR}/${output}")

      add_custom_command(
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${output}"
        COMMAND ${CMAKE_COMMAND} -E copy "${input}" "${CMAKE_CURRENT_BINARY_DIR}/${output}"
        COMMENT "Generating ${local_path}/${output}")
    endif()
  endforeach()

  add_custom_target("${target}_copy_outputs_from_${dependency}"
    DEPENDS "${outputs}")

  add_dependencies("${target}_copy_outputs_from_${dependency}" ${dependency})
  add_dependencies(${target} "${target}_copy_outputs_from_${dependency}")

  if(ARGC GREATER 2)
    set(${ARGV2} ${outputs} PARENT_SCOPE)
  endif()
endfunction()

function(add_dependency_outputs target)
  get_target_property(output_files_list ${target} COPY_FILES)

  if(output_files_list)
    set_target_properties(${target}
      PROPERTIES
        COPY_FILES "${output_files_list};${ARGN}")
  else()
    set_target_properties(${target}
      PROPERTIES
        COPY_FILES "${ARGN}")
  endif()

  mark_as_advanced(output_files_list)
endfunction()
