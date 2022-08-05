function(CopyRuntimeDependencies TARGET)
  set(valid_options "DEPENDENCY;")
  foreach(arg IN LISTS ARGN)
    if("${arg}" IN_LIST valid_options)
      set(mode "${arg}")
    elseif("${mode}" STREQUAL "DEPENDENCY")
      list(LENGTH RUNTIME_DEPENDENCY_SOURCES current_dependencies)
      list(APPEND RUNTIME_DEPENDENCY_SOURCES "${arg}")
    endif()
  endforeach()
  foreach(dependency_idx RANGE 0 ${current_dependencies})
    list(GET RUNTIME_DEPENDENCY_SOURCES ${dependency_idx} dependency)
    if(WIN32)
      add_custom_command(
      TARGET ${TARGET} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
              $<TARGET_RUNTIME_DLLS:${dependency}> $<TARGET_FILE_DIR:${TARGET}>
      COMMAND_EXPAND_LISTS
      )
    endif()
  endforeach()
  add_custom_command(
    TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:${TARGET}> $<TARGET_FILE_DIR:${TARGET}>
    COMMAND_EXPAND_LISTS
  )
endfunction()
