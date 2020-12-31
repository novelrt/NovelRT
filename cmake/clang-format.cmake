file(GLOB_RECURSE
     ALL_SRC_FILES
      src/*/*.c src/*/*.cpp samples/*/*.cpp samples/*/*.c include/*/*.h tests/*/*.cpp
     )


find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
  message("Found clang-format at ${CLANG_FORMAT}")
  if(WIN32)
    add_custom_target(
        clang-format
        COMMAND clang-format
        -i
        -style=file
        ${ALL_SRC_FILES}
    )
    add_custom_target(
        clang-format-ci
        COMMAND clang-format
        -n
        -style=file
        ${ALL_SRC_FILES}
    )
  else()
    add_custom_target(
        clang-format
        COMMAND /usr/bin/clang-format
        -i
        -style=file
        ${ALL_SRC_FILES}
    )
    add_custom_target(
        clang-format-ci
        COMMAND /usr/bin/clang-format
        -n
        -style=file
        ${ALL_SRC_FILES}
    )
  endif()
else()
  message("Did not find clang-format! Disabling target.")
endif()


