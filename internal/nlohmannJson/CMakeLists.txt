include(FetchContent)
message(STATUS "Fetching nlohmann json")

FetchContent_Declare(json
    URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
    URL_HASH SHA256=8c4b26bf4b422252e13f332bc5e388ec0ab5c3443d24399acb675e68278d341f

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

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
endif()

add_library(nlohmann_json::nlohmann_json INTERFACE IMPORTED GLOBAL)

target_include_directories(nlohmann_json::nlohmann_json
    INTERFACE
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:$<BUILD_INTERFACE:${json_SOURCE_DIR}/include>>
)

target_compile_options(nlohmann_json::nlohmann_json
    INTERFACE
        $<BUILD_INTERFACE:$<$<CXX_COMPILER_ID:MSVC>:/external:I${json_SOURCE_DIR}/include>>
        $<$<CXX_COMPILER_ID:MSVC>:/external:W0>
        $<$<CXX_COMPILER_ID:MSVC>:/external:templates->
)
