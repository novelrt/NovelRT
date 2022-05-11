include(FetchContent)

FetchContent_Declare(Fabulist
        URL https://github.com/novelrt/Fabulist/archive/refs/heads/feature/runtime.zip
        URL_HASH SHA512=1dab11a62b9720eb82ab9f816c8f8c26c778338f6fe39a7d9df0444e74cf4e50a53ea77b1e52cd5ee02676d8bf841a94bfa3b98a49e9c743038045f53e76997a

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

FetchContent_MakeAvailable(Fabulist)