include(FetchContent)
message(STATUS "Fetching SDL2")

FetchContent_Declare(SDL2
  URL https://github.com/libsdl-org/SDL/archive/refs/tags/release-2.26.0.zip
  URL_HASH SHA512=2e53af5aa3d3ca7e2b8653f999379bf424b2190aad32a7997350fc058624818cca3a780907af74c8f72305ca18a83a2aa15839e1dbc94107128125a7df9cd7fd

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

set(SDL2_DISABLE_INSTALL OFF CACHE BOOL "Tell SDL2 to provide install targets" FORCE)
FetchContent_MakeAvailable(SDL2)
