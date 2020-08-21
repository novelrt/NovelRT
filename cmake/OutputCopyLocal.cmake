define_property(TARGET
  PROPERTY INTERFACE_COPY_LOCAL
  BRIEF_DOCS "Copy the outputs of this target to any dependents of this target."
  FULL_DOCS "Copy the outputs of this target to any dependents of this target."
)

define_property(TARGET
  PROPERTY COPY_LOCAL
  BRIEF_DOCS "Copy the outputs of this target to any dependents of this target."
  FULL_DOCS "Copy the outputs of this target to any dependents of this target."
)

define_property(TARGET
  PROPERTY ADDITIONAL_COPY_LOCAL_FILES
  BRIEF_DOCS "Additional files to copy to dependents of this target."
  FULL_DOCS "Additional files to copy to dependents of this target."
)

define_property(TARGET
  PROPERTY ADDITIONAL_COPY_LOCAL_FILES_DESTINATION
  BRIEF_DOCS "Location to copy ADDITIONAL_COPY_LOCAL_FILES to."
  FULL_DOCS "Location to copy ADDITIONAL_COPY_LOCAL_FILES to."
)

function(add_copy_local_targets target dependency)
  get_target_property(copy_local ${dependency} COPY_LOCAL)
  get_target_property(interface_copy_local ${dependency} INTERFACE_COPY_LOCAL)
  get_target_property(copy_local_files ${dependency} ADDITIONAL_COPY_LOCAL_FILES)
  get_target_property(copy_local_files_destination ${dependency} ADDITIONAL_COPY_LOCAL_FILES_DESTINATION)
  get_target_property(copy_local_libs ${dependency} _COPY_LOCAL_LIBS)
  get_target_property(source_location ${dependency} BINARY_DIR)
  get_target_property(target_location ${target} BINARY_DIR)

  if(NOT copy_local)
    set(copy_local ${interface_copy_local})
  endif()

  if(copy_local AND ${copy_local})
    # Maintain a list of targets to copy local after the build is completed

    get_target_property(imported ${dependency} IMPORTED)

    if(imported)
      get_target_property(configurations ${dependency} IMPORTED_CONFIGURATIONS)

      if(configurations)
        foreach(configuration ${configurations})
          get_target_property(location ${dependency} IMPORTED_LOCATION_${configuration})

          if(location)
            if(target_file)
              set(target_file "$<IF:$<CONFIG:${configuration}>,${location},${target_file}>")
            else()
              # Use this configuration as a fallback.
              set(target_file "${location}")
            endif()
          endif()
        endforeach()
      endif()

      if(NOT target_file)
        get_target_property(target_file ${dependency} IMPORTED_LOCATION)
      endif()
    endif()

    if(NOT target_file)
      set(target_file "$<TARGET_FILE:${dependency}>")
    endif()

    if(copy_local_libs)
      set_property(
        TARGET ${target} APPEND
        PROPERTY _COPY_LOCAL_LIBS ${target_file} ${copy_local_libs}
      )
    else()
      set_property(
        TARGET ${target} APPEND
        PROPERTY _COPY_LOCAL_LIBS ${target_file}
      )
    endif()
  endif()

  if(copy_local_files)
    # Identify directories to create
    set(directories_to_create)
    foreach(file ${copy_local_files})
      file(RELATIVE_PATH relpath "${source_location}" "${file}")
      get_filename_component(directory "${relpath}" DIRECTORY)

      if(directory)
        if(copy_local_files_destination)
          set(directory "${copy_local_files_destination}/${directory}/")
        endif()
      elseif(copy_local_files_destination)
        set(directory "${copy_local_files_destination}/")
      endif()

      list(APPEND directories_to_create "${target_location}/${directory}")
    endforeach()

    # Ensure we're only creating unique directories
    list(REMOVE_DUPLICATES directories_to_create)

    # Create those directories.
    add_custom_command(
      TARGET ${target} POST_BUILD
      DEPENDS "${copy_local_file}"
      COMMAND ${CMAKE_COMMAND} -E make_directory
        ${directories_to_create}
      VERBATIM
    )

    foreach(directory ${directories_to_create})
      # Group files to copy by directory
      if(copy_local_files_destination)
        file(RELATIVE_PATH relpath "${target_location}/${copy_local_files_destination}" "${directory}")
      else()
        file(RELATIVE_PATH relpath "${target_location}/${copy_local_files_destination}" "${directory}")
      endif()

      set(files_to_copy)
      foreach(file ${copy_local_files})
        get_filename_component(dirname "${file}" DIRECTORY)
        file(RELATIVE_PATH relpath2 "${source_location}" "${dirname}")
        if("${relpath}" STREQUAL "${relpath2}")
          list(APPEND files_to_copy "${file}")
        endif()
      endforeach()

      # Copy the files for this directory.
      add_custom_command(
        TARGET ${target} POST_BUILD
        DEPENDS "${copy_local_file}"
        COMMAND ${CMAKE_COMMAND} -E copy
          ${files_to_copy}
          ${directory}
        VERBATIM
      )
    endforeach()
  endif()
endfunction()

macro(add_library name)
  _add_library(${name} ${ARGN})

  get_target_property(interface ${name} TYPE)
  get_target_property(aliased ${name} ALIASED_TARGET)

  if(NOT "${interface}" STREQUAL "INTERFACE_LIBRARY")
    unset(interface)
  endif()

  # Libraries should likely be copied locally by default.

  # ALIAS libraries can't have set_target_properties called
  if(NOT aliased)
    # Interface libraries have a whitelist on the property names which can be set.
    if(interface)
      set_target_properties(${name}
        PROPERTIES
          INTERFACE_COPY_LOCAL TRUE
      )
    else()
      set_target_properties(${name}
        PROPERTIES
          COPY_LOCAL TRUE
      )
    endif()
  endif()

  unset(interface)
  unset(aliased)
endmacro()

macro(add_executable name)
  _add_executable(${name} ${ARGN})

  get_target_property(imported ${name} IMPORTED)
  get_target_property(aliased ${name} ALIASED_TARGET)

  # executables likely shouldn't be copied locally by default.
  if(NOT aliased)
    set_target_properties(${name}
      PROPERTIES
        COPY_LOCAL FALSE
    )

    # Imported targets cannot have custom commands added to them.
    if(NOT imported)
      file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/CopyDependencies.cmake [[
foreach(copy_file ${COPY_LOCAL_FILES})
  get_filename_component(name "${copy_file}" NAME)
  while(IS_SYMLINK "${copy_file}")
    file(READ_SYMLINK "${copy_file}" link_dest)
    if(NOT IS_ABSOLUTE "${link_dest}")
      get_filename_component(dir "${copy_file}" DIRECTORY)
      set(link_dest "${dir}/${link_dest}")
    endif()
    set(copy_file "${link_dest}")
  endwhile()
  configure_file(${copy_file} ${DESTINATION}/${name} COPYONLY)
endforeach()]])
      add_custom_command(
        TARGET ${name} POST_BUILD
        COMMAND ${CMAKE_COMMAND}
          -DCOPY_LOCAL_FILES=$<REMOVE_DUPLICATES:$<GENEX_EVAL:$<TARGET_PROPERTY:${name},_COPY_LOCAL_LIBS>>>
          -DDESTINATION=$<TARGET_FILE_DIR:${name}>
          -P ${CMAKE_CURRENT_BINARY_DIR}/CopyDependencies.cmake
        VERBATIM
      )
    endif()
  endif()

  unset(imported)
  unset(aliased)
endmacro()

macro(add_dependencies target)
  foreach(dependency ${ARGN})
    add_copy_local_targets(${target} ${dependency})
  endforeach()

  _add_dependencies(${target} ${ARGN})
endmacro()

macro(target_link_libraries target)
  foreach(dependency ${ARGN})
    if(TARGET ${dependency})
      add_copy_local_targets(${target} ${dependency})
    endif()
  endforeach()

  _target_link_libraries(${target} ${ARGN})
endmacro()
