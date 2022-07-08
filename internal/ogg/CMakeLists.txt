include(FetchContent)
message(STATUS "Fetching Ogg...")

FetchContent_Declare(ogg
        URL https://github.com/xiph/ogg/releases/download/v1.3.5/libogg-1.3.5.tar.gz
        URL_HASH SHA256=0eb4b4b9420a0f51db142ba3f9c64b333f826532dc0f48c6410ae51f4799b664

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

FetchContent_MakeAvailable(ogg)
set(OGG_LIBRARY "ogg" CACHE STRING "Set OGG libraries" FORCE)
set(OGG_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src/include" CACHE STRING "Set OGG include dirs" FORCE)
