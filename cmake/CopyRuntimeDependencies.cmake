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
      elseif(APPLE)
        get_target_property(libs ${dependency} LINK_LIBRARIES)
        if(libs)
          foreach(lib_idx ${libs})
            #message("DEP TEST - ${lib_idx}")
            if("${lib_idx}" MATCHES "\<.*")
              #message(STATUS "Ignoring genex")
              break()
            else()
              get_target_property(type ${lib_idx} TYPE)
              if("${type}" STREQUAL "INTERFACE_LIBRARY" OR "$type" STREQUAL "STATIC_LIBRARY")
                break()
              endif()
              if("${lib_idx}" MATCHES ".*::.*")
                string(REGEX REPLACE ".*::" "" lib_safe_name "${lib_idx}")
              else()
                set(lib_safe_name "${lib_idx}")
              endif()
              list(APPEND dep_lib_snippet 
                "execute_process(COMMAND echo \"Copying ${lib_safe_name} dependency for ${TARGET}\")
                execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_LINKER_FILE:${lib_idx}> $<TARGET_FILE_DIR:${TARGET}>/../Frameworks/$<TARGET_LINKER_FILE_NAME:${lib_idx}>)
                execute_process(COMMAND echo \"Adjusting RPATH for dependency ${lib_safe_name} in ${TARGET}\")
                execute_process(COMMAND \"otool -L \\\"$<TARGET_FILE:${TARGET}>\\\"\" OUTPUT_VARIABLE otool-output)
                execute_process(COMMAND echo \${otool-output})
                execute_process(COMMAND grep -o '.*$<TARGET_LINKER_FILE_NAME:${lib_idx}>' OUTPUT_VARIABLE grep-output)
                execute_process(COMMAND echo \${grep-output})
                if(grep-output)
                  string(STRIP \${grep-output} grep-output)
                endif()
                execute_process(COMMAND install_name_tool -change \"\${grep-output}\" \"@executable_path/../Frameworks/$<TARGET_LINKER_FILE_NAME:${lib_idx}>\" \"$<TARGET_FILE:${TARGET}>\")")
              list(JOIN dep_lib_snippet "\n" dep_lib_snippet)
              file(GENERATE 
                OUTPUT copy_${lib_safe_name}_from_${dependency}_to_${TARGET}$<$<BOOL:${multi_config}>:_$<CONFIG>>.cmake
                CONTENT "${dep_lib_snippet}"
              )
              add_custom_command(TARGET ${TARGET}
                POST_BUILD
                COMMAND ${CMAKE_COMMAND} -P copy_${lib_safe_name}_from_${dependency}_to_${TARGET}$<$<BOOL:${multi_config}>:_$<CONFIG>>.cmake
                DEPENDS $<TARGET_FILE:${TARGET}>
              )
              list(POP_BACK dep_lib_snippet)
              # add_custom_target("copy_${lib_safe_name}_to_${TARGET}" ALL
              #   COMMENT "Copying ${lib_safe_name} dependency for ${TARGET}"
              #   COMMAND ${CMAKE_COMMAND} -E copy_if_different
              #     $<TARGET_LINKER_FILE:${lib_idx}> $<TARGET_FILE_DIR:${TARGET}>/../Frameworks/$<TARGET_LINKER_FILE_NAME:${lib_idx}>
              # )
              # add_dependencies(${TARGET} "copy_${lib_safe_name}_to_${TARGET}")
              # add_custom_command(TARGET ${TARGET}
              #   POST_BUILD
              #   COMMAND ${CMAKE_COMMAND} -E echo "Adjusting RPATH for dependency ${lib_safe_name} in ${TARGET}"
              #   COMMAND install_name_tool -change "$<TARGET_LINKER_FILE_NAME:${lib_idx}>" "@executable_path/../Frameworks/$<TARGET_LINKER_FILE_NAME:${lib_idx}>" "$<TARGET_FILE:${TARGET}>"
              #   DEPENDS ${TARGET}
              # )
            endif()
          endforeach()
        endif()
      endif()
    endforeach()
    if(WIN32)
      add_custom_command(
        TARGET ${TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_RUNTIME_DLLS:${TARGET}> $<TARGET_FILE_DIR:${TARGET}>
        COMMAND_EXPAND_LISTS
      )
    elseif(APPLE)
      # add_custom_target("copy_${lib_safe_name}_from_${dependency}_to_${TARGET}" ALL
      #   COMMENT "Copying ${lib_safe_name} dependency for ${TARGET}"
      #   COMMAND ${CMAKE_COMMAND} -E copy_if_different
      #   $<TARGET_LINKER_FILE:${dependency}> $<TARGET_FILE_DIR:${TARGET}>/../Frameworks/$<TARGET_LINKER_FILE_NAME:${dependency}>
      # )
      # add_dependencies(${TARGET} "copy_${lib_safe_name}_from_${dependency}_to_${TARGET}")
      # add_custom_command(TARGET ${TARGET}
      #   POST_BUILD
      #   COMMAND ${CMAKE_COMMAND} -E echo "Adjusting RPATH for dependency ${lib_safe_name} in ${TARGET}"
      #   COMMAND install_name_tool -change "$<TARGET_LINKER_FILE_NAME:${dependency}>" "@executable_path/../Frameworks/$<TARGET_LINKER_FILE_NAME:${dependency}>" "$<TARGET_FILE:${TARGET}>"
      #   DEPENDS ${TARGET}
      # )
        list(APPEND dep_snippet 
          "execute_process(COMMAND echo \"Copying ${dependency} for ${TARGET}\")
          execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_LINKER_FILE:${dependency}> $<TARGET_FILE_DIR:${TARGET}>/../Frameworks/$<TARGET_LINKER_FILE_NAME:${dependency}>)
          execute_process(COMMAND echo \"Adjusting RPATH for ${dependency} in ${TARGET}\")
          execute_process(COMMAND \"otool -L \\\"$<TARGET_FILE:${TARGET}>\\\"\" OUTPUT_VARIABLE otool-output)
          execute_process(COMMAND grep -o '.*$<TARGET_LINKER_FILE_NAME:${dependency}>' OUTPUT_VARIABLE grep-output)
          if(grep-output)
            string(STRIP \${grep-output} grep-output)
          endif()
          execute_process(COMMAND install_name_tool -change \"\${grep-output}\" \"@executable_path/../Frameworks/$<TARGET_LINKER_FILE_NAME:${dependency}>\" \"$<TARGET_FILE:${TARGET}>\")")
        list(JOIN dep_snippet "\n" dep_snippet)
        file(GENERATE 
          OUTPUT copy_${dependency}_to_${TARGET}$<$<BOOL:${multi_config}>:_$<CONFIG>>.cmake
          CONTENT "${dep_snippet}"
        )
        add_custom_command(TARGET ${TARGET}
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -P copy_${dependency}_to_${TARGET}$<$<BOOL:${multi_config}>:_$<CONFIG>>.cmake
          DEPENDS ${dependency} ${TARGET}
        )
        list(POP_BACK dep_snippet)
    endif()
  endif()
  if(current_libs)
    #message("Current Libs TEST - ${current_libs}")
    if(APPLE)
    foreach(lib_idx ${current_libs})
      if("${lib_idx}" MATCHES ".*::.*")
        string(REGEX REPLACE ".*::" "" lib_safe_name "${lib_idx}")
      else()
        set(lib_safe_name "${lib_idx}")
      endif()
      # add_custom_target("copy_${lib_safe_name}_to_${TARGET}" ALL
      #   COMMENT "Copying ${lib_safe_name} dependency for ${TARGET}"
      #   COMMAND ${CMAKE_COMMAND} -E copy_if_different
      #     $<TARGET_LINKER_FILE:${lib_idx}> $<TARGET_FILE_DIR:${TARGET}>/../Frameworks/$<TARGET_FILE_NAME:${lib_idx}>
      # )
      # add_dependencies(${TARGET} "copy_${lib_safe_name}_to_${TARGET}")
      # add_custom_command(TARGET ${TARGET}
      #   POST_BUILD
      #   USES_TERMINAL
        
      #   COMMAND install_name_tool -change "$<TARGET_LINKER_FILE_NAME:${lib_idx}>" "@executable_path/../Frameworks/$<TARGET_LINKER_FILE_NAME:${lib_idx}>" "$<TARGET_FILE:${TARGET}>"
      #   DEPENDS ${TARGET}
      # )
      # add_custom_command(TARGET ${TARGET}
      #   POST_BUILD  
      #   COMMAND ${CMAKE_COMMAND} -E echo "Adjusting RPATH for specified library ${lib_safe_name} in ${TARGET}"
      #   DEPENDS ${TARGET}
      # )
      list(APPEND lib_snippet 
          "execute_process(COMMAND echo \"Copying ${lib_safe_name} for ${TARGET}\")
          execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_LINKER_FILE:${lib_idx}> $<TARGET_FILE_DIR:${TARGET}>/../Frameworks/$<TARGET_LINKER_FILE_NAME:${lib_idx}>)
          execute_process(COMMAND echo \"Adjusting RPATH for ${lib_safe_name} in ${TARGET}\")
          execute_process(COMMAND \"otool -L \\\"$<TARGET_FILE:${TARGET}>\\\"\" OUTPUT_VARIABLE otool-output)
          execute_process(COMMAND grep -o '.*$<TARGET_LINKER_FILE_NAME:${lib_idx}>' OUTPUT_VARIABLE grep-output)
          if(grep-output)
            string(STRIP \${grep-output} grep-output)
          endif()
          execute_process(COMMAND install_name_tool -change \"\${grep-output}}\" \"@executable_path/../Frameworks/$<TARGET_LINKER_FILE_NAME:${lib_idx}>\" \"$<TARGET_FILE:${TARGET}>\")")
        list(JOIN lib_snippet "\n" lib_snippet)
        file(GENERATE 
          OUTPUT copy_${lib_safe_name}_to_${TARGET}$<$<BOOL:${multi_config}>:_$<CONFIG>>.cmake
          CONTENT "${lib_snippet}"
        )
        add_custom_command(TARGET ${TARGET}
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -P copy_${lib_safe_name}_to_${TARGET}$<$<BOOL:${multi_config}>:_$<CONFIG>>.cmake
          DEPENDS ${TARGET}
        )
        list(POP_BACK lib_snippet)
      endforeach()
    endif()
  endif()
endfunction()
