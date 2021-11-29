function(copy_build_products target)
  set(valid_options "DEPENDENCY;DEPENDENCY_FILES;TARGET_LOCATION;CONDITION")
  foreach(arg IN LISTS ARGN)
    if("${arg}" IN_LIST valid_options)
      set(mode "${arg}")
    elseif("${mode}" STREQUAL "DEPENDENCY")
      list(LENGTH COPY_BUILD_PRODUCTS_DEPENDENCIES current_dependency)
      list(APPEND COPY_BUILD_PRODUCTS_DEPENDENCIES "${arg}")
    elseif("${mode}" STREQUAL "DEPENDENCY_FILES")
      list(APPEND "COPY_BUILD_PRODUCTS_${current_dependency}_FILES" "${arg}")
    elseif("${mode}" STREQUAL "TARGET_LOCATION")
      if(DEFINED "COPY_BUILD_PRODUCTS_${current_dependency}_TARGET_LOCATION")
        message(FATAL_ERROR "Target location for dependency ${current_dependency} already set!")
      endif()
      set("COPY_BUILD_PRODUCTS_${current_dependency}_TARGET_LOCATION" "${arg}")
    elseif("${mode}" STREQUAL "CONDITION")
      if(DEFINED "COPY_BUILD_PRODUCTS_${current_dependency}_CONDITION")
       set("COPY_BUILD_PRODUCTS_${current_dependency}_CONDITION" "${COPY_BUILD_PRODUCTS_${current_dependency}_CONDITION} ${arg}")
      else()
        set("COPY_BUILD_PRODUCTS_${current_dependency}_CONDITION" "${arg}")
      endif()
    endif()
  endforeach()

  set(COPY_BUILD_PRODUCTS_COPIED_RESOURCES)
  foreach(dependency_idx RANGE 0 ${current_dependency})
    list(GET COPY_BUILD_PRODUCTS_DEPENDENCIES ${dependency_idx} dependency)
    get_target_property(type ${dependency} TYPE)
    get_target_property(resx_tmp ${dependency} RESOURCE)
    get_target_property(bindir ${dependency} BINARY_DIR)

    set(resx "")
    if(resx_tmp)
      foreach(res IN LISTS resx_tmp)
        if(IS_ABSOLUTE "${res}")
          file(RELATIVE_PATH relpath "${bindir}" "${res}")
          list(APPEND resx "${relpath}")
        else()
          list(APPEND resx "${res}")
        endif()
      endforeach()
    endif()

    set(cond_succeeded NO)
    if(NOT DEFINED "COPY_BUILD_PRODUCTS_${dependency_idx}_CONDITION")
      set(cond_succeeded YES)
    else()
      cmake_language(EVAL CODE "if(COPY_BUILD_PRODUCTS_${dependency_idx}_CONDITION)\nset(cond_succeeded YES)\nendif()")
    endif()

    if("${type}" STREQUAL "INTERFACE_LIBRARY")
      set(tgt_dir "$<TARGET_PROPERTY:${dependency},BINARY_DIR>")
      set(tgt_outputs "")
    else()
      set(tgt_dir "$<TARGET_FILE_DIR:${dependency}>")
      set(tgt_outputs "$<TARGET_FILE_NAME:${dependency}>")
    endif()

    list(APPEND tgt_outputs ${resx})

    if(DEFINED COPY_BUILD_PRODUCTS_${dependency_idx}_FILES)
      set(tgt_outputs "${COPY_BUILD_PRODUCTS_${dependency_idx}_FILES}")
    endif()

    list(REMOVE_DUPLICATES tgt_outputs)

    if(cond_succeeded)
      foreach(file IN LISTS tgt_outputs)
        list(APPEND COPY_BUILD_PRODUCTS_COPIED_RESOURCES "${COPY_BUILD_PRODUCTS_${dependency_idx}_TARGET_LOCATION}/${file}")
        list(APPEND copy_snippet
"# ${COPY_BUILD_PRODUCTS_${dependency_idx}_CONDITION} (${dependency} -> ${target})
execute_process(COMMAND \${CMAKE_COMMAND} -E copy_if_different
  ${tgt_dir}/${file}
  ${COPY_BUILD_PRODUCTS_${dependency_idx}_TARGET_LOCATION}/${file}
)")
      endforeach()
    endif()
  endforeach()

  list(JOIN copy_snippet "\n" copy_snippet)

  get_property(multi_config GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
  file(GENERATE
    OUTPUT copy_build_products$<$<BOOL:${multi_config}>:_$<CONFIG>>.cmake
    CONTENT "${copy_snippet}")
  add_custom_target("copy_build_products_to_${target}" ALL
    COMMAND ${CMAKE_COMMAND} -P copy_build_products$<$<BOOL:${multi_config}>:_$<CONFIG>>.cmake
    COMMENT "Copying required build products to ${target}")
  add_dependencies(${target} copy_build_products_to_${target})
  add_dependencies(copy_build_products_to_${target} ${COPY_BUILD_PRODUCTS_DEPENDENCIES})
  set_property(TARGET copy_build_products_to_${target} APPEND PROPERTY
    ADDITIONAL_CLEAN_FILES "${COPY_BUILD_PRODUCTS_COPIED_RESOURCES}"
  )
  set_property(
    TARGET ${target} APPEND PROPERTY
    RESOURCE "${COPY_BUILD_PRODUCTS_COPIED_RESOURCES}"
  )
endfunction()
