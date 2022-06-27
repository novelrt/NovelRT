include(FetchContent)
message(STATUS "Fetching Freetype")

FetchContent_Declare(freetype
        URL https://gitlab.freedesktop.org/freetype/freetype/-/archive/VER-2-12-1/freetype-VER-2-12-1.tar.gz
        URL_HASH SHA512=d2c6e8af7f25fef12222405c0825fa9d96d724d4633435a736da53b74ef9ea9079ec64c08172f908e2a6af23305cb8743636fa5ca51b36d7a839c89c780e33e0

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
        
set(FT_DISABLE_BZIP2 TRUE CACHE BOOL "Disable BZip2 dependency" FORCE)
set(FT_DISABLE_HARFBUZZ TRUE CACHE BOOL "Disable Harfbuzz dependency" FORCE)
set(FT_DISABLE_BROTLI TRUE CACHE BOOL "Disable Brotli dependency" FORCE)
FetchContent_MakeAvailable(freetype)
