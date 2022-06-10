include(FetchContent)

FetchContent_Declare(Freetype
        URL https://download.savannah.gnu.org/releases/freetype/freetype-2.12.1.tar.gz
        URL_HASH SHA512=4f923c82121940e866022c1ee6afb97f447b83ab8b54188df169029f37589e3bad0768a3bfb3095982804db1eec582f05aa846dfb32639697e231af8d52676cc

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

FetchContent_MakeAvailable(Freetype)
