include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(BUILD_CXXLIBS OFF)
set(BUILD_PROGRAMS OFF)
set(BUILD_EXAMPLES OFF)
set(BUILD_TESTING OFF)
set(BUILD_DOCS OFF)
set(INSTALL_MANPAGES OFF)
set(INSTALL_PKGCONFIG_MODULES OFF)
set(INSTALL_CMAKE_CONFIG_MODULE ON)

FetchContent_MakeAvailable(flac)

set_target_properties(FLAC
  PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

set(all_options
  $<$<CXX_COMPILER_ID:GNU>:-Wno-bad-function-cast>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-bad-function-cast>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-bad-function-cast>

  $<$<CXX_COMPILER_ID:GNU>:-Wno-cast-align>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-cast-align>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-cast-align>

  $<$<CXX_COMPILER_ID:GNU>:-Wno-cast-qual>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-cast-qual>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-cast-qual>

  $<$<CXX_COMPILER_ID:GNU>:-Wno-declaration-after-statement>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-declaration-after-statement>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-declaration-after-statement>

  $<$<CXX_COMPILER_ID:GNU>:-Wno-deprecated-non-prototype>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-deprecated-non-prototype>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-deprecated-non-prototype>

  $<$<CXX_COMPILER_ID:GNU>:-Wno-cast-function-type-strict>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-cast-function-type-strict>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-cast-function-type-strict>

  $<$<CXX_COMPILER_ID:GNU>:-Wno-covered-switch-default>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-covered-switch-default>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-covered-switch-default>

  $<$<CXX_COMPILER_ID:GNU>:-Wno-documentation-unknown-command>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-documentation-unknown-command>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-documentation-unknown-command>

  $<$<CXX_COMPILER_ID:GNU>:-Wno-double-promotion>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-double-promotion>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-double-promotion>

  $<$<CXX_COMPILER_ID:GNU>:-Wno-empty-translation-unit>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-empty-translation-unit>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-empty-translation-unit>

  $<$<CXX_COMPILER_ID:GNU>:-Wno-extra-semi-stmt>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-extra-semi-stmt>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-extra-semi-stmt>

  $<$<CXX_COMPILER_ID:GNU>:-Wno-implicit-fallthrough>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-implicit-fallthrough>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-implicit-fallthrough>

  $<$<CXX_COMPILER_ID:GNU>:-Wno-implicit-int-conversion>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-implicit-int-conversion>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-implicit-int-conversion>

  $<$<CXX_COMPILER_ID:GNU>:-Wno-implicit-int-float-conversion>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-implicit-int-float-conversion>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-implicit-int-float-conversion>

  $<$<CXX_COMPILER_ID:GNU>:-Wno-implicit-float-conversion>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-implicit-float-conversion>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-implicit-float-conversion>

  $<$<CXX_COMPILER_ID:GNU>:-Wno-incompatible-pointer-types>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-incompatible-pointer-types>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-incompatible-pointer-types>

  $<$<CXX_COMPILER_ID:GNU>:-Wno-knr-promoted-parameter>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-knr-promoted-parameter>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-knr-promoted-parameter>

  $<$<CXX_COMPILER_ID:GNU>:-Wno-language-extension-token>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-language-extension-token>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-language-extension-token>

  $<$<CXX_COMPILER_ID:GNU>:-Wno-missing-variable-declarations>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-missing-variable-declarations>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-missing-variable-declarations>

  $<$<CXX_COMPILER_ID:GNU>:-Wno-nonportable-system-include-path>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-nonportable-system-include-path>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-nonportable-system-include-path>

  $<$<CXX_COMPILER_ID:GNU>:-Wno-reserved-macro-identifier>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-reserved-macro-identifier>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-reserved-macro-identifier>

  $<$<CXX_COMPILER_ID:GNU>:-Wno-sign-conversion>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-sign-conversion>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-sign-conversion>

  $<$<CXX_COMPILER_ID:GNU>:-Wno-static-in-inline>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-static-in-inline>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-static-in-inline>

  $<$<CXX_COMPILER_ID:GNU>:-Wno-switch-default>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-switch-default>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-switch-default>

  $<$<CXX_COMPILER_ID:GNU>:-Wno-switch-enum>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-switch-enum>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-switch-enum>

  $<$<CXX_COMPILER_ID:GNU>:-Wno-unreachable-code-loop-increment>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-unreachable-code-loop-increment>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-unreachable-code-loop-increment>

  $<$<CXX_COMPILER_ID:GNU>:-Wno-unsafe-buffer-usage>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-unsafe-buffer-usage>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-unsafe-buffer-usage>

  $<$<CXX_COMPILER_ID:GNU>:-Wno-unused-macros>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-unused-macros>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wno-unused-macros>)

target_compile_options(FLAC PRIVATE ${all_options})

target_compile_options(getopt PRIVATE ${all_options})

if(TARGET benchmark_residual)
  target_compile_options(benchmark_residual PRIVATE ${all_options})
endif()

if(TARGET grabbag)
  target_compile_options(grabbag PRIVATE ${all_options})
endif()

if(TARGET replaygain_analysis)
 target_compile_options(replaygain_analysis PRIVATE ${all_options})
endif()

if(TARGET replaygain_synthesis)
  target_compile_options(replaygain_synthesis PRIVATE ${all_options})
endif()

if(TARGET utf8)
  target_compile_options(utf8 PRIVATE ${all_options})
endif()
