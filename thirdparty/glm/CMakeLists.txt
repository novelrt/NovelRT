include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

FetchContent_MakeAvailable(GLM)

#include(CPack)
#install(
#  DIRECTORY ${glm_SOURCE_DIR}/glm/
#  DESTINATION include/glm
#  PATTERN "CMakeLists.txt" EXCLUDE
#)
#install(EXPORT glm FILE glmConfig.cmake DESTINATION lib/cmake/glm NAMESPACE glm::)
#include(CMakePackageConfigHelpers)
#write_basic_package_version_file("${glm_BINARY_DIR}/glmConfigVersion.cmake" COMPATIBILITY AnyNewerVersion)
#install(FILES ${glm_BINARY_DIR}/glmConfigVersion.cmake DESTINATION lib/cmake/glm)
