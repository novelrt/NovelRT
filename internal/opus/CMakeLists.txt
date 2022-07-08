include(FetchContent)
message(STATUS "Fetching Opus...")

FetchContent_Declare(opus
        URL https://github.com/xiph/opus/archive/refs/tags/v1.3.1.zip
        URL_HASH SHA512=574382c898fcc644d6cfd061841b4e9fb24162ff680ec82620a9bd29d7ac3c3fcefac25bd45fa7f7310b7461bafeda9ca05f473c791fdbb4ee446e50a7a889a0

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

set(OPUS_INSTALL_PKG_CONFIG_MODULE OFF CACHE BOOL "" FORCE)
set(OPUS_INSTALL_CMAKE_CONFIG_MODULE OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(opus)
set(OPUS_LIBRARY "opus" CACHE STRING "Set Opus libraries" FORCE)
set(OPUS_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src/include" CACHE STRING "Set Opus include dirs" FORCE)
set_property(TARGET opus PROPERTY POSITION_INDEPENDENT_CODE ON)
