include(FetchContent)

FetchContent_Declare(Fabulist
        URL https://github.com/novelrt/Fabulist/archive/refs/heads/feature/runtime.zip
        URL_HASH SHA512=aaeb559d1344ff0508980d2927eead8aa2656f283e0f1dd941a3a956a19657da1638722a39ade02d262d0991f97648a5a9f729643181d0af31e3d48af46de0f1

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