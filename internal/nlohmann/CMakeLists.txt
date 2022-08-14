include(FetchContent)
message(STATUS "Fetching nlohmann_json...")

FetchContent_Declare(json
    URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz
    URL_HASH SHA512=feb7dbdd1f1b6318131821f55d1411f0435262601c65eca368ccf3418750fd6348a37a3cd9d0694b31ccacfc91d02fbbecf94af52429005f8898490a5233c37d

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
set(JSON_BuildTests OFF)
set(JSON_Install ON)

FetchContent_MakeAvailable(json)
