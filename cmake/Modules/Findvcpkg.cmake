set(_vcpkg_install_parameters "")

if(WIN32)
  set(_vcpkg_toolchain "${CMAKE_BINARY_DIR}\\vcpkg\\src\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake")
  if(${CMAKE_SIZEOF_VOID_P} EQUAL "8")
    set(_vcpkg_install_command "${CMAKE_BINARY_DIR}\\vcpkg\\src\\vcpkg\\vcpkg.exe")
    set(_vcpkg_install_parameters --triplet x64-windows)
  else()
    set(_vcpkg_install_command "${CMAKE_BINARY_DIR}\\vcpkg\\src\\vcpkg\\vcpkg.exe")
  endif()
else()
  set(_vcpkg_toolchain "${CMAKE_BINARY_DIR}/vcpkg/src/vcpkg/scripts/buildsystems/vcpkg.cmake")
  set(_vcpkg_install_command "${CMAKE_BINARY_DIR}/vcpkg/src/vcpkg/vcpkg")
endif()

mark_as_advanced(_vcpkg_install_command _vcpkg_toolchain _vcpkg_install_parameters)

if(NOT EXISTS ${_vcpkg_install_command})
  make_directory(${CMAKE_BINARY_DIR}/vcpkg)

  execute_process(
    COMMAND ${CMAKE_COMMAND} -S ${CMAKE_SOURCE_DIR}/cmake/vcpkg
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/vcpkg)

  execute_process(
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/vcpkg
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/vcpkg)
endif()

execute_process(
  COMMAND ${_vcpkg_install_command} install ${vcpkg_FIND_COMPONENTS} ${_vcpkg_install_parameters})

include(${_vcpkg_toolchain})

set(vcpkg_FOUND TRUE)
