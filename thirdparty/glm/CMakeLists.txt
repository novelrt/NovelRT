include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

FetchContent_MakeAvailable(GLM)


# Needed to manually re-add GLM's install
# as it's necessary for an "installed"
# version of NovelRT to compile
include(CPack)
install(DIRECTORY ${glm_SOURCE_DIR}/glm 
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    PATTERN "CMakeLists.txt" EXCLUDE
)
install(EXPORT glm 
    FILE glmConfig.cmake 
    DESTINATION lib/cmake/glm 
    NAMESPACE glm::
)
include(CMakePackageConfigHelpers)
write_basic_package_version_file("glmConfigVersion.cmake" COMPATIBILITY AnyNewerVersion)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/glmConfigVersion.cmake 
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/glm
)
