include(FetchContent)
message(STATUS "Fetching Fabulist")

FetchContent_Declare(Fabulist
        URL https://github.com/novelrt/Fabulist/archive/refs/heads/feature/runtime.zip
        URL_HASH SHA512=ae6d21988825097bf312e38bd5ed3cbe075cc9e9655637caa25dd63218927c167ee6b55af9bf62c246a41a44d6f5483a27b769bc2f846ac2fb96ae32e9db7c05

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
FetchContent_MakeAvailable(Fabulist)
add_dependencies(compiler runtime)
