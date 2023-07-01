set(_gch_default_file_template "${CMAKE_CURRENT_LIST_DIR}/GenerateCombinedHeader.h.in" CACHE INTERNAL "")

function(generate_combined_header)
  cmake_parse_arguments(
    PARSE_ARGV 0
    _gch
    "INSTALL"
    "TARGET;FILE_NAME;FILE_TEMPLATE;DESTINATION"
    "HEADER_SETS"
  )

  if(NOT _gch_FILE_NAME)
    set(_gch_FILE_NAME "$<TARGET_NAME:${_gch_TARGET}>.hpp")
  endif()

  if(NOT _gch_FILE_TEMPLATE)
    set(_gch_FILE_TEMPLATE "${_gch_default_file_template}")
  endif()

  foreach(_set IN LISTS _gch_HEADER_SETS)
    get_target_property(_basedirs ${_gch_TARGET} "HEADER_DIRS_${_set}")
    get_target_property(_files ${_gch_TARGET} "HEADER_SET_${_set}")
    foreach(_file IN LISTS _files)
      set(_relpath "${_file}")
      foreach(_dir IN LISTS _basedirs)
        file(RELATIVE_PATH _test "${_dir}" "${_file}")
        string(LENGTH "${_test}" _testlen)
        string(LENGTH "${_relpath}" _rellen)
        if(_testlen LESS _rellen)
          set(_relpath "${_test}")
        endif()
      endforeach()
      list(APPEND _include_snippets "#include <${_relpath}>")
    endforeach()
  endforeach()

  string(MAKE_C_IDENTIFIER "${_gch_FILE_NAME}" _macro)
  string(TOUPPER "${_macro}" _macro)
  list(JOIN _include_snippets "\n" _include_snippet)

  set(GENERATE_COMBINED_HEADER_INCLUDE_GUARD "#ifndef ${_macro}\n#define ${_macro}")
  set(GENERATE_COMBINED_HEADER_INCLUDE_GUARD_END "#endif // !${_macro}")
  set(GENERATE_COMBINED_HEADER_INCLUDES "${_include_snippet}")

  configure_file(
    "${_gch_FILE_TEMPLATE}"
    "${_gch_FILE_NAME}.in"
  )
  file(GENERATE
    OUTPUT "${_gch_FILE_NAME}"
    INPUT "${CMAKE_CURRENT_BINARY_DIR}/${_gch_FILE_NAME}.in"
    TARGET "${_gch_TARGET}"
  )

  if(_gch_INSTALL)
    install(
      FILES "${CMAKE_CURRENT_BINARY_DIR}/${_gch_FILE_NAME}"
      DESTINATION "${_gch_DESTINATION}"
    )
  endif()
endfunction()
