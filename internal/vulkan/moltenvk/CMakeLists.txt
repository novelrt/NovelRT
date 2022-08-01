include(ExternalProject)
message(STATUS "Fetching MoltenVK...")
message(WARNING
        "NovelRT is set to build MoltenVK which can take upwards "
        "of 30+ minutes on certain devices. Also, building MoltenVK "
        "requires that 'xcodebuild' is set as the default tool in xcode-select, "
        "and that the XCode Licence Agreements have been accepted. Otherwise, "
        "building MoltenVK will fail. Please make any changes prior to building "
        "NovelRT to ensure a smoother experience."
)

ExternalProject_Add(moltenvk
        URL https://github.com/KhronosGroup/MoltenVK/archive/refs/tags/v1.1.9.tar.gz
        URL_HASH SHA512=d672ef6a6ba72dfeb9c3990067e7b99c9aa5743b581a33df37e866783e3af027d47d80292a351b86b663efb2d115695e951a552ff4efe2ea965b1abac471e1e2

        PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
        TMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/tmp"
        STAMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/stamp"
        DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/dl"
        SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src"
        INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/inst"
        LOG_DIR "${CMAKE_CURRENT_BINARY_DIR}/log"

        BUILD_IN_SOURCE ON
        CONFIGURE_COMMAND ""
        INSTALL_COMMAND ""
        BUILD_COMMAND <SOURCE_DIR>/fetchDependencies "--macos" COMMAND xcodebuild build -quiet -project MoltenVKPackaging.xcodeproj -scheme "MoltenVK Package (macOS only)"
)

set(NOVELRT_MOLTENVK_DYLIB_PATH "${CMAKE_CURRENT_BINARY_DIR}/src/MoltenVK/dylib/macOS" CACHE STRING "Path to MoltenVK directory for generated ICD and Loader")
set(NOVELRT_MOLTENVK_LIB "${NOVELRT_MOLTENVK_DYLIB_PATH}/libMoltenVK.dylib" CACHE STRING "File path to MoltenVK library for NovelRT" FORCE)
set(NOVELRT_MOLTENVK_ICDPATH "${NOVELRT_MOLTENVK_DYLIB_PATH}/MoltenVK_icd.json" CACHE STRING "Path to MoltenVK_icd.json" FORCE)
set(NOVELRT_MOLTENVK_VENDORED ON CACHE BOOL "MoltenVK is being vendored by the NovelRT project" FORCE)
