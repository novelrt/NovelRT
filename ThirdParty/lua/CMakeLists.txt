include(FetchContent)

FetchContent_MakeAvailable(lua)

file(READ "${lua_SOURCE_DIR}/src/Makefile" lua_makefile)

# Parse out object files
string(REGEX REPLACE ".+CORE_O=[\t ]+(.+)[\r\n ]+LIB_O=[\t ]+([^A-Z]+)[\r\n ]+[A-Z_].+" "\\1;\\2" lua_objects "${lua_makefile}")
string(REGEX REPLACE "[\r\t\n ]+\\\\[\r\t\n ]+" " " lua_objects "${lua_objects}")
string(STRIP "${lua_objects}" lua_objects)
string(REGEX REPLACE "[\r\n ]+" ";" lua_objects "${lua_objects}")

# Parse out source files and headers
string(REGEX REPLACE ".+# DO NOT DELETE[\r\n ]+([^#]+).+" "\\1" lua_sources "${lua_makefile}")
string(REGEX REPLACE "[\r\t\n ]+\\\\[\r\t\n ]+" " " lua_sources "${lua_sources}")
string(STRIP "${lua_sources}" lua_sources)
string(REGEX REPLACE "[\r\n]+" ";" lua_sources "${lua_sources}")
string(REGEX REPLACE "[: ]+" "\\\\;" lua_sources "${lua_sources}")

set(source_files "")
set(header_files "")
foreach(object_sources IN LISTS lua_sources)
  list(GET object_sources 0 object)
  list(GET object_sources 1 source_file)
  list(SUBLIST object_sources 2 -1 header_file_list)
  list(FIND lua_objects "${object}" found)

  if(found GREATER -1)
    list(APPEND source_files "${source_file}")
    list(APPEND header_files ${header_file_list})
  endif()
endforeach()

list(REMOVE_DUPLICATES header_files)

list(TRANSFORM source_files PREPEND "${lua_SOURCE_DIR}/src/")
list(TRANSFORM header_files PREPEND "${lua_SOURCE_DIR}/src/")

foreach(file IN LISTS source_files header_files)
  set_property(
    SOURCE "${file}"
    PROPERTY LANGUAGE CXX
  )

  # This is necessary as CMake doesn't automatically pass this flag for
  # whatever reason
  set_property(
    SOURCE "${file}"
    PROPERTY COMPILE_OPTIONS
      "$<$<CXX_COMPILER_ID:AppleClang>:--language=c++>"
      "$<$<CXX_COMPILER_ID:Clang>:--language=c++>"
      "$<$<CXX_COMPILER_ID:GNU>:--language=c++>"
  )
endforeach()

add_library(lua ${source_files})
add_library(lua::lua ALIAS lua)
set_target_properties(lua
  PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    OUTPUT_NAME lua-$<CONFIG>
    VERSION 5.5.0
)
target_include_directories(lua
  SYSTEM INTERFACE
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:$<BUILD_INTERFACE:${lua_SOURCE_DIR}/src>>
)

target_compile_definitions(lua
  PUBLIC
    $<$<PLATFORM_ID:Windows>:LUA_USE_WINDOWS>
    $<$<PLATFORM_ID:Linux>:LUA_USE_LINUX>
    $<$<PLATFORM_ID:Darwin>:LUA_USE_MACOSX>
    $<$<PLATFORM_ID:iOS>:LUA_USE_IOS>
)

target_compile_options(lua
  INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:/experimental:external>
    $<$<CXX_COMPILER_ID:MSVC>:/external:I$<BUILD_INTERFACE:${lua_SOURCE_DIR}/src>>
    $<$<CXX_COMPILER_ID:MSVC>:/external:W0>
    $<$<CXX_COMPILER_ID:MSVC>:/external:templates->
  PRIVATE
    $<$<CXX_COMPILER_ID:AppleClang>:-Wno-empty-body>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-empty-body>
    $<$<CXX_COMPILER_ID:GNU>:-Wno-empty-body>
    $<$<CXX_COMPILER_ID:MSVC>:/wd4390> # empty control statement found

    $<$<CXX_COMPILER_ID:AppleClang>:-Wno-unused-const-variable>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-unused-const-variable>
    $<$<CXX_COMPILER_ID:GNU>:-Wno-unused-const-variable>
    # $<$<CXX_COMPILER_ID:MSVC>:/wd4390> # no msvc error for this?

    $<$<CXX_COMPILER_ID:AppleClang>:-Wno-misleading-indentation>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-misleading-indentation>
    $<$<CXX_COMPILER_ID:GNU>:-Wno-misleading-indentation>
    # $<$<CXX_COMPILER_ID:MSVC>:/wd4390> # no msvc error for this?

    $<$<CXX_COMPILER_ID:AppleClang>:-Wno-conversion>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-conversion>
    $<$<CXX_COMPILER_ID:GNU>:-Wno-conversion>
    $<$<CXX_COMPILER_ID:MSVC>:/wd4365> # conversion from 'a' to 'b', signed/unsigned mismatch

    $<$<CXX_COMPILER_ID:MSVC>:/wd4820> # bytes padding added after data member
    $<$<CXX_COMPILER_ID:MSVC>:/wd4061> # enum values are not explicitly handled
    $<$<CXX_COMPILER_ID:MSVC>:/D_CRT_SECURE_NO_WARNINGS /D_SCL_NO_WARNINGS> # function or variable may be unsafe
    $<$<CXX_COMPILER_ID:MSVC>:/wd5220> # non-static data member with a volatile qualified type
    $<$<CXX_COMPILER_ID:MSVC>:/wd5045> # compiler will insert spectre mitigation for memory load
    $<$<CXX_COMPILER_ID:MSVC>:/wd4334> # result of 32-bit shift implicitly converted to 64-bits
    $<$<CXX_COMPILER_ID:MSVC>:/wd4774> # format string expected in argument 2 is not a string literal
)

install(
  TARGETS lua
  EXPORT lua
  LIBRARY DESTINATION lib
)

install(
  EXPORT lua
  NAMESPACE lua::
  DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/lib"
)
