include(FetchContent)
message(STATUS "Fetching Fabulist")

set(FABULIST_THIRDPARTY_JSON OFF)

FetchContent_Declare(Fabulist
        URL https://github.com/novelrt/Fabulist/archive/refs/heads/feature/runtime.zip
        URL_HASH SHA512=028433c21807906bf56c430a20573b643c648ec44aee65395aa46b7e34b77de53c37e17184a2516a2ff3ec3ba614d1be86f95e53ec730b1e2e97453991ff9638

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

# Appears to be a bug, doing this until established and/or resolved
install(FILES
  ${fabulist_SOURCE_DIR}/runtime/include/fabulist/runtime/runtime.hpp
  ${fabulist_SOURCE_DIR}/runtime/include/fabulist/runtime/decoder.hpp
  DESTINATION include/fabulist/runtime)
