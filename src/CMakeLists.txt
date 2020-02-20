if (NOVELRT_SUPPORT_DOTNET)
  add_subdirectory(NovelRT.DotNet)
endif()

add_subdirectory(Resources)

add_subdirectory(NovelRT)

# NovelRT Package

include(CMakePackageConfigHelpers)
set(NOVELRT_CONFIG_DIR "lib/cmake")
set(NOVELRT_VERSION_CONFIG "${CMAKE_CURRENT_BINARY_DIR}/NovelRTConfigVersion.cmake")
write_basic_package_version_file("${NOVELRT_VERSION_CONFIG}" COMPATIBILITY SameMajorVersion)
set(NOVELRT_PROJECT_CONFIG "${CMAKE_CURRENT_BINARY_DIR}/NovelRTConfig.cmake")
configure_package_config_file("Config.cmake.in" "${NOVELRT_PROJECT_CONFIG}" INSTALL_DESTINATION "${NOVELRT_CONFIG_DIR}")

# NovelRT Installation

install(FILES "${NOVELRT_VERSION_CONFIG}" "${NOVELRT_PROJECT_CONFIG}"
        DESTINATION "${NOVELRT_CONFIG_DIR}")
install(EXPORT NovelRTRuntime
        DESTINATION "${NOVELRT_CONFIG_DIR}")
