include(FetchContent)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(PNG_TOOLS OFF)
set(PNG_TESTS OFF)

# Libpng evaluates these include dirs outside of the context of a generator, so we have to strip them out.
# ZLIB_INCLUDE_DIRS is used while generating pnglibconf.out, and it is written in such a way that it cannot
# directly use the ZLIB::zlib target.
get_target_property(incl ZLIB::zlib INTERFACE_INCLUDE_DIRECTORIES)
string(REGEX MATCH [[\$<BUILD_INTERFACE:([^>]+)>?]] incl "${incl}")
string(REGEX REPLACE [[\$<BUILD_INTERFACE:([^>]+)>?]] [[\1]] incl "${incl}")
set(ZLIB_INCLUDE_DIRS "${incl}")

FetchContent_MakeAvailable(PNG)
