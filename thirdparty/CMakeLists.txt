include(FetchContent)

macro(thirdparty_module name)
  FetchContent_Declare(${name}
    ${ARGN}
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}/${name}"
    TMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/${name}/tmp"
    STAMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/${name}/stamp"
    DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/${name}/dl"
    SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/${name}/src"
    SUBBUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/${name}/build"
    BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/${name}/bin"
    INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/${name}/inst"
    LOG_DIR "${CMAKE_CURRENT_BINARY_DIR}/${name}/log"
  )
  list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/cmake/${name}")
endmacro()

# N.B. Names here must match xConfig.cmake as produced by installation
thirdparty_module(Fabulist
  URL https://github.com/novelrt/Fabulist/archive/refs/heads/feature/runtime.zip
  URL_HASH SHA512=876f781279ecc55a309a7b5a9bae29017f6817893f81f5b943d317aa9f0ec626b264d8cf10c65189722ed612275fc849aa94c1c7553979334f960c2de23a78d9
)
thirdparty_module(FLAC
  URL https://github.com/xiph/flac/releases/download/1.3.4/flac-1.3.4.tar.xz
  URL_HASH SHA256=8ff0607e75a322dd7cd6ec48f4f225471404ae2730d0ea945127b1355155e737
  OVERRIDE_FIND_PACKAGE
)
thirdparty_module(fmt
  URL https://github.com/fmtlib/fmt/releases/download/10.2.1/fmt-10.2.1.zip
  URL_HASH SHA512=1cf0e3dd09c7d87e0890b8743559159d3be2a8f33c135516962d17c4eeb7b00659e6acd74518bd5566ee4e83ddaba155fecb4c229f90cd258b3b832e72ad82cd
)
thirdparty_module(glfw3
  URL https://github.com/glfw/glfw/archive/refs/tags/3.3.7.zip
  URL_HASH SHA512=0ee020ddbbed783b5f0d271ee0a98b37fe489b633e0a8407821f12b2bcfc3b80645751076192b5224bfe1d26d6092c27af9a9bcd7953a419dcec0182e3716341
)
thirdparty_module(glm
  URL https://github.com/novelrt/glm/archive/refs/heads/master.zip
  URL_HASH SHA512=c87d14dfd240633227bdf5e4b43dd5567e522a72a09cd888a34c8fa3d696ffac91d8d7f16abb5f3a4326d69bca69c4f33e8f9be54a32aedf3ffb32d14a6bf322
)
thirdparty_module(GSL
  URL https://github.com/microsoft/GSL/archive/refs/tags/v4.0.0.zip
  URL_HASH SHA512=710ab8b06b24dbca2cd1a8abb2eca2282548644224519784d04b1c7b70e3639f3b3e8d8f993f7f8c3dce3fcfe9ff0f3757b8d2625b676df36c84caa6f684133e
)
thirdparty_module(GTest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  URL_HASH SHA512=16cc8f5b03b862e2937d1b926ca6dc291234ac5670050dc4fc2752ec98497330ebcd46f292317cd2bbb111ce33bbdcfd088ddf6a7fe273e2442963908732d589
  OVERRIDE_FIND_PACKAGE
)
thirdparty_module(nlohmann_json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
  URL_HASH SHA512=1aa94cdc3378a1fe0e3048ee73293e34bfa5ed9b46c6db0993e58e289ef818f7b7a472c0dc9c920114312e2e3ae1ff346ca797407ff48143744592adfd0a41ad
  OVERRIDE_FIND_PACKAGE
)
thirdparty_module(Ogg
  URL https://github.com/xiph/ogg/releases/download/v1.3.5/libogg-1.3.5.tar.gz
  URL_HASH SHA256=0eb4b4b9420a0f51db142ba3f9c64b333f826532dc0f48c6410ae51f4799b664
  OVERRIDE_FIND_PACKAGE
)
thirdparty_module(OpenAL
  URL https://github.com/kcat/openal-soft/archive/1318bea2e0f0af9430335708e65ae2ff920d98c6.zip
  URL_HASH SHA512=a561b962ecfc6135cb6f5e4d9ba7b9719b8e6dce85112ca0dd4fe3efd05d86308a4076e0cba9e628b1a4ee2f984efabe517c1aa1399809ca848bae90b449ba4f
  OVERRIDE_FIND_PACKAGE
)
thirdparty_module(Opus
  URL https://github.com/xiph/opus/archive/refs/tags/v1.3.1.zip
  URL_HASH SHA512=574382c898fcc644d6cfd061841b4e9fb24162ff680ec82620a9bd29d7ac3c3fcefac25bd45fa7f7310b7461bafeda9ca05f473c791fdbb4ee446e50a7a889a0
  OVERRIDE_FIND_PACKAGE
)
thirdparty_module(PNG
  URL https://github.com/glennrp/libpng/archive/refs/tags/v1.6.35.zip
  URL_HASH SHA512=65df0c2befa06d0b9ec0c6395a73987fb071754610d328b94ce01a6b8f7161c71ce97ddf0e0a8e28c2e50019a103368c4b4f0b63bd8cd75e168b32f940922d96
  OVERRIDE_FIND_PACKAGE
)

thirdparty_module(samplerate
  URL https://github.com/libsndfile/libsamplerate/archive/refs/tags/0.2.2.zip
  URL_HASH SHA512=dedd072bc83ccebfe1a33e8a3fb3f72559bfd36282b958b1d5463b786f2325f684137580db38d91f0f4f5345a1da3e9e1c4a1695e303182e57d542c085db829f
)

thirdparty_module(SndFile
  URL https://github.com/novelrt/libsndfile/archive/f76d63813c810c2ed09bdb3821bb807498a7558e.zip
  URL_HASH SHA512=7e650af94068277246e4ccaf3b5dc20d0f93d2a2e0ecdf0f24f0be79196f879c21ec692ad48d39454f22dd01d9a4864d21458daa8d7b8f5ea4568c9551b345c1
)
thirdparty_module(spdlog
  URL https://github.com/gabime/spdlog/archive/refs/tags/v1.13.0.zip
  URL_HASH SHA512=851febf19949006a17ead8b6392f12ae81e626926268829478d4d0d28a1dfe7682ef57a6c4f151031cf4cc60f1486cf8453999ee7ce40a1f0d3f545c4d7f8555
)
thirdparty_module(stduuid
  URL https://github.com/mariusbancila/stduuid/archive/3afe7193facd5d674de709fccc44d5055e144d7a.zip
  URL_HASH SHA512=a0e1c4b889919b43290ab8c978e96c2f51782a1c7972780351c80b4a860f1c4a488a957bf832b3e38eea97a8efa1dcce632c04fbb083331e2b83f54b16e87a67
)
thirdparty_module(TBB
  URL https://github.com/oneapi-src/oneTBB/archive/refs/tags/v2021.5.0.zip
  URL_HASH SHA512=fde7eb56b46fa86b619eb60e587728d19f31639ec06dfd5d7af0dab00ffba38606d7a89dcf050c4cdfa8896560a7424a3431619108f395348dadf60ad6b67a1b
)
thirdparty_module(Vorbis
  URL https://github.com/xiph/vorbis/releases/download/v1.3.7/libvorbis-1.3.7.tar.gz
  URL_HASH SHA256=0e982409a9c3fc82ee06e08205b1355e5c6aa4c36bca58146ef399621b0ce5ab
  OVERRIDE_FIND_PACKAGE
)
thirdparty_module(VulkanMemoryAllocator
  URL https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator/archive/0aa3989b8f382f185fdf646cc83a1d16fa31d6ab.zip
  URL_HASH SHA512=e9eeed2f5cc1130613b9440bf375e5574b58e800f4615cc771176644951eadc9e49cff91c5d303e63831fbdc76f354d2ad9a9da11826588ede76a7252c7a636a
)
thirdparty_module(ZLIB
  URL https://github.com/zlib-ng/zlib-ng/archive/refs/tags/2.0.6.tar.gz
  URL_HASH SHA512=4888f17160d0a87a9b349704047ae0d0dc57237a10e11adae09ace957afa9743cce5191db67cb082991421fc961ce68011199621034d2369c0e7724fad58b4c5
  OVERRIDE_FIND_PACKAGE
)

# N.B. Order matters here, for dependency searching!
foreach(module
  nlohmann_json
  Fabulist
  glfw3
  glm
  GSL
  GTest
  Opus Ogg FLAC Vorbis SndFile samplerate
  OpenAL
  ZLIB PNG
  fmt spdlog
  stduuid
  TBB
  VulkanMemoryAllocator)
  message(STATUS "Fetching ${module}...")
  add_subdirectory(${module})
endforeach()
