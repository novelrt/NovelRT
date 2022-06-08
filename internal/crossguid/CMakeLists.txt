include(FetchContent)

FetchContent_Declare(CrossGuid
        URL https://github.com/novelrt/crossguid/archive/refs/tags/v0.2.5-alpha.zip
        URL_HASH SHA512=8328a130b71a3f305959318421d607b24b07a4f61340675785d9728d45a89afdc7e989ffc08ed558cbb3073c35954aa35be428f791e4c0b3eba4413b32b63ddb

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

FetchContent_MakeAvailable(CrossGuid)
