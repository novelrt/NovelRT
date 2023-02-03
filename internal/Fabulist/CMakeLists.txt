include(FetchContent)
message(STATUS "Fetching Fabulist")

set(FABULIST_THIRDPARTY_JSON OFF)

FetchContent_Declare(Fabulist
        URL https://github.com/novelrt/Fabulist/archive/refs/heads/feature/runtime.zip
        URL_HASH SHA512=876f781279ecc55a309a7b5a9bae29017f6817893f81f5b943d317aa9f0ec626b264d8cf10c65189722ed612275fc849aa94c1c7553979334f960c2de23a78d9

        PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
        TMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/tmp"
        STAMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/stamp"
        DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/dl"
        SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src"
        SUBBUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/build"
        BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/bin"
        INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/inst"
        LOG_DIR "${CMAKE_CURRENT_BINARY_DIR}/log"
)

# Until this is changed, always build Fabulist as Static
set(BUILD_SHARED_LIBS OFF)
set(FABULIST_THIRDPARTY_JSON OFF)
FetchContent_MakeAvailable(Fabulist)
add_dependencies(compiler runtime)

if(APPLE)
  set_target_properties(runtime PROPERTIES NO_SONAME TRUE)
endif()

# Appears to be a bug, doing this until established and/or resolved
install(DIRECTORY
      ${fabulist_SOURCE_DIR}/runtime/include/fabulist/runtime/
   DESTINATION include/fabulist/runtime
)

install(FILES
      ${fabulist_BINARY_DIR}/runtime/fabulist_runtime_export.hpp
   DESTINATION include/fabulist/runtime/actions
)
