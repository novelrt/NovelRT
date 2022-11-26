function(copy_runtime_dependencies TARGET)
  set(valid_options "DEPENDENCY;LIBRARY")
  foreach(arg IN LISTS ARGN)
    if("${arg}" IN_LIST valid_options)
      set(mode "${arg}")
    elseif("${mode}" STREQUAL "DEPENDENCY")
      list(LENGTH RUNTIME_DEPENDENCY_SOURCES current_dependencies)
      list(APPEND RUNTIME_DEPENDENCY_SOURCES "${arg}")
    elseif("${mode}" STREQUAL "LIBRARY")
      list(APPEND current_libs "${arg}")
    endif()
  endforeach()
  get_property(multi_config GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
  if(RUNTIME_DEPENDENCY_SOURCES)
    foreach(dependency_idx RANGE 0 ${current_dependencies})
      list(GET RUNTIME_DEPENDENCY_SOURCES ${dependency_idx} dependency)
      if(WIN32)
        add_custom_command(
        TARGET ${TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_RUNTIME_DLLS:${dependency}> $<TARGET_FILE_DIR:${TARGET}>
        COMMAND_EXPAND_LISTS
        )
      # elseif(APPLE)
      #   get_target_property(libs ${dependency} LINK_LIBRARIES)
      #   if(libs)
      #     foreach(lib_idx ${libs})
      #       if("${lib_idx}" MATCHES "\<.*")
      #         break()
      #       else()
      #         get_target_property(type ${lib_idx} TYPE)
      #         if("${type}" STREQUAL "INTERFACE_LIBRARY" OR "$type" STREQUAL "STATIC_LIBRARY")
      #           break()
      #         endif()
      #         if("${lib_idx}" MATCHES ".*::.*")
      #           string(REGEX REPLACE ".*::" "" lib_safe_name "${lib_idx}")
      #         else()
      #           set(lib_safe_name "${lib_idx}")
      #         endif()
      #         list(APPEND dep_lib_snippet
      #           "
      #           if(EXISTS otool.txt)
      #             file(REMOVE otool.txt)
      #           endif()
      #           set(lib_file \"$<TARGET_LINKER_FILE:${lib_idx}>\")
      #           set(lib_file_name \"$<TARGET_LINKER_FILE_NAME:${lib_idx}>\")
      #           string(FIND \"\${lib_file}\" \"libvulkan.dylib\" vulkanTest)
      #           if(NOT vulkanTest EQUAL -1)
      #             string(REPLACE \"libvulkan.dylib\" \"libvulkan.1.dylib\" lib_file \${lib_file})
      #             string(REPLACE \"libvulkan.dylib\" \"libvulkan.1.dylib\" lib_file_name \${lib_file_name})
      #             message(STATUS \"Overriding Vulkan library for macOS\")
      #           endif()
      #           execute_process(COMMAND echo \"Copying ${lib_safe_name} and adjusting RPATH for ${TARGET}\")
      #           execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different \${lib_file} $<TARGET_FILE_DIR:${TARGET}>/../Frameworks/\${lib_file_name})
      #           execute_process(COMMAND otool -L $<TARGET_FILE:${TARGET}> OUTPUT_FILE otool.txt)
      #           set(GREP_ARGS .*\${lib_file_name})
      #           execute_process(
      #             COMMAND grep -o \${GREP_ARGS} otool.txt
      #             OUTPUT_VARIABLE grep-output
      #             RESULT_VARIABLE grep-result)
      #           if(grep-output)
      #             string(STRIP \${grep-output} grep-output)
      #             execute_process(COMMAND install_name_tool -change \"\${grep-output}\" \"@executable_path/../Frameworks/\${lib_file_name}\" \"$<TARGET_FILE:${TARGET}>\")
      #           endif()
      #           if(EXISTS otool.txt)
      #             file(REMOVE otool.txt)
      #           endif()
      #           ")
      #         list(JOIN dep_lib_snippet "\n" dep_lib_snippet)
      #         file(GENERATE
      #           OUTPUT copy_${lib_safe_name}_from_${dependency}_to_${TARGET}$<$<BOOL:${multi_config}>:_$<CONFIG>>.cmake
      #           CONTENT "${dep_lib_snippet}"
      #         )
      #         add_custom_command(TARGET ${TARGET}
      #           POST_BUILD
      #           COMMAND ${CMAKE_COMMAND} -P copy_${lib_safe_name}_from_${dependency}_to_${TARGET}$<$<BOOL:${multi_config}>:_$<CONFIG>>.cmake
      #           DEPENDS $<TARGET_FILE:${TARGET}>
      #         )
      #         list(POP_BACK dep_lib_snippet)
      #       endif()
      #     endforeach()
      #   endif()
      endif()
    endforeach()
    if(WIN32)
      add_custom_command(
        TARGET ${TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_RUNTIME_DLLS:${TARGET}> $<TARGET_FILE_DIR:${TARGET}>
        COMMAND_EXPAND_LISTS
      )
    # elseif(APPLE)
    #     set(config_suffix "")
    #     if(multi_config)
    #       set(config_suffix "_${CONFIG}")
    #     endif()
    #     list(APPEND dep_snippet
    #       "
    #       if(EXISTS otool.txt)
    #         file(REMOVE otool.txt)
    #       endif()
    #       execute_process(COMMAND echo \"Copying ${dependency} and adjusting RPATH for ${TARGET}\")
    #       execute_process(
    #         COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_LINKER_FILE:${dependency}> $<TARGET_FILE_DIR:${TARGET}>/../Frameworks/$<TARGET_LINKER_FILE_NAME:${dependency}>
    #         OUTPUT_VARIABLE copy-output
    #       )
    #       execute_process(COMMAND otool -L $<TARGET_FILE:${TARGET}> OUTPUT_FILE otool.txt)
    #       set(GREP_ARGS .*$<TARGET_LINKER_FILE_NAME:${dependency}>)
    #       execute_process(
    #         COMMAND grep -o \${GREP_ARGS} otool.txt
    #         OUTPUT_VARIABLE grep-output
    #         RESULT_VARIABLE grep-result)
    #       if(grep-output)
    #         string(STRIP \${grep-output} grep-output)
    #         execute_process(
    #           COMMAND install_name_tool -change \"\${grep-output}\" \"@executable_path/../Frameworks/$<TARGET_LINKER_FILE_NAME:${dependency}>\" \"$<TARGET_FILE:${TARGET}>\"
    #         )
    #       endif()
    #       if(EXISTS otool.txt)
    #         file(REMOVE otool.txt)
    #       endif()
    #       ")
    #     list(JOIN dep_snippet "\n" dep_snippet)
    #     file(GENERATE
    #       OUTPUT copy_${dependency}_to_${TARGET}${config_suffix}.cmake
    #       CONTENT "${dep_snippet}"
    #     )
    #     add_custom_command(TARGET ${TARGET}
    #       POST_BUILD
    #       COMMAND ${CMAKE_COMMAND} -P copy_${dependency}_to_${TARGET}${config_suffix}.cmake
    #       DEPENDS $<TARGET_FILE:${TARGET}> $<TARGET_FILE:${dependency}>
    #     )
    #     list(POP_BACK dep_snippet)
    # endif()
  endif()
  # if(current_libs)
  #   if(APPLE)
  #   foreach(lib_idx ${current_libs})
  #     if("${lib_idx}" MATCHES ".*::.*")
  #       string(REGEX REPLACE ".*::" "" lib_safe_name "${lib_idx}")
  #     else()
  #       set(lib_safe_name "${lib_idx}")
  #     endif()
  #     list(APPEND lib_snippet
  #         "
  #         if(EXISTS otool.txt)
  #           file(REMOVE otool.txt)
  #         endif()
  #         set(lib_file \"$<TARGET_LINKER_FILE:${lib_idx}>\")
  #         set(lib_file_name \"$<TARGET_LINKER_FILE_NAME:${lib_idx}>\")
  #         string(FIND \"vulkan\" \${lib_file} vulkanTest)
  #         string(FIND \"\${lib_file}\" \"libvulkan.dylib\" vulkanTest)
  #         if(NOT vulkanTest EQUAL -1)
  #           string(REPLACE \"libvulkan.dylib\" \"libvulkan.1.dylib\" lib_file \${lib_file})
  #           string(REPLACE \"libvulkan.dylib\" \"libvulkan.1.dylib\" lib_file_name \${lib_file_name})
  #           message(STATUS \"Overriding Vulkan library for macOS\")
  #         endif()
  #         execute_process(COMMAND echo \"Copying ${lib_safe_name} and adjusting RPATH for ${TARGET}\")
  #         execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different \${lib_file} $<TARGET_FILE_DIR:${TARGET}>/../Frameworks/\${lib_file_name})
  #         execute_process(COMMAND otool -L $<TARGET_FILE:${TARGET}> OUTPUT_FILE otool.txt)
  #         set(GREP_ARGS .*\${lib_file_name})
  #         execute_process(
  #           COMMAND grep -o \${GREP_ARGS} otool.txt
  #           OUTPUT_VARIABLE grep-output
  #           RESULT_VARIABLE grep-result)
  #         if(grep-output)
  #           string(STRIP \${grep-output} grep-output)
  #           execute_process(COMMAND install_name_tool -change \"\${grep-output}\" \"@executable_path/../Frameworks/\${lib_file_name}\" \"$<TARGET_FILE:${TARGET}>\")
  #         endif()
  #         if(EXISTS otool.txt)
  #           file(REMOVE otool.txt)
  #         endif()
  #         ")
  #       list(JOIN lib_snippet "\n" lib_snippet)
  #       file(GENERATE
  #         OUTPUT copy_${lib_safe_name}_to_${TARGET}$<$<BOOL:${multi_config}>:_$<CONFIG>>.cmake
  #         CONTENT "${lib_snippet}"
  #       )
  #       add_custom_command(TARGET ${TARGET}
  #         POST_BUILD
  #         COMMAND ${CMAKE_COMMAND} -P copy_${lib_safe_name}_to_${TARGET}$<$<BOOL:${multi_config}>:_$<CONFIG>>.cmake
  #         DEPENDS $<TARGET_FILE:${TARGET}>
  #       )
  #       list(POP_BACK lib_snippet)
  #     endforeach()
  #   endif()
  # endif()
endfunction()
