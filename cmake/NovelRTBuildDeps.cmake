#
# Generate and Locate NovelRT's Dependencies
#
include(ProcessorCount)
ProcessorCount(CORES)
if(CORES EQUAL 0)
  set(CORES_AMT 1)
else()
  math(EXPR CORES_AMT "${CORES} / 2")
  if(CORES_AMT LESS 1)
    set(CORES_AMT 1)
  endif()
endif()

if(NOVELRT_FETCH_DEPENDENCIES)
  if(NOT NOVELRT_DEPS_INSTALLED)
    if(${CMAKE_GENERATOR} MATCHES "Visual Studio")
      set(GENERATOR_ARCH_PARAM -A ${CMAKE_VS_PLATFORM_TOOLSET_HOST_ARCHITECTURE})
    endif()

    execute_process(
      COMMAND ${CMAKE_COMMAND} -S ${CMAKE_CURRENT_SOURCE_DIR}/internal -B ${CMAKE_CURRENT_BINARY_DIR}/depbuild -DCMAKE_BUILD_TYPE=Release -G ${CMAKE_GENERATOR} ${GENERATOR_ARCH_PARAM} -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/dist -DNOVELRT_TARGET=${NOVELRT_TARGET}
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      COMMAND_ERROR_IS_FATAL LAST
    )

    if(NOVELRT_BUILD_DEPS_WITH_MAX_CPU)
      set(NOVELRT_DEPENDENCY_CORE_COUNT ${CORES})
    else()
      set(NOVELRT_DEPENDENCY_CORE_COUNT ${CORES_AMT})
    endif()

    execute_process(
      COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/depbuild --config Release -j${NOVELRT_DEPENDENCY_CORE_COUNT}
      COMMAND_ERROR_IS_FATAL LAST
    )
    execute_process(
      COMMAND ${CMAKE_COMMAND} --install ${CMAKE_CURRENT_BINARY_DIR}/depbuild --config Release
      COMMAND_ERROR_IS_FATAL LAST
    )

    set(NOVELRT_DEPS_PATH "${CMAKE_CURRENT_BINARY_DIR}/dist" CACHE FILEPATH "Path where NovelRT's Dependencies were previously installed")
    set(NOVELRT_DEPS_INSTALLED TRUE CACHE BOOL "Indicates if NovelRT's Dependencies have been installed locally via FetchContent")
  endif()
  list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR}/dist)
  list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR}/dist/share)
  list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR}/dist/lib/cmake)
endif()
