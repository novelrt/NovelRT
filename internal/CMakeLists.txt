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
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
  URL_HASH SHA512=1479ea2f3172c622c0ca305f5b2bc45a42941221ec0ac7865e6d6d020ec4d008d952fc64e01a4c5138d7bed4148cf75596f25bb9e9044a98bbbf5662053ea11c
)
thirdparty_module(nlohmann_json
  URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz
  URL_HASH SHA512=feb7dbdd1f1b6318131821f55d1411f0435262601c65eca368ccf3418750fd6348a37a3cd9d0694b31ccacfc91d02fbbecf94af52429005f8898490a5233c37d
)
thirdparty_module(Ogg
  URL https://github.com/xiph/ogg/releases/download/v1.3.5/libogg-1.3.5.tar.gz
  URL_HASH SHA256=0eb4b4b9420a0f51db142ba3f9c64b333f826532dc0f48c6410ae51f4799b664
  OVERRIDE_FIND_PACKAGE
)
thirdparty_module(OpenAL
  URL https://github.com/kcat/openal-soft/archive/refs/tags/1.21.1.zip
  URL_HASH SHA512=bc17d628548e59d0db3996917d207a4af0bbbf615ba3ba10ae8e99b28213e845e967a0510c8aad74e551aa66ddfb11499fe26082725af82160ac5d2db4e7e69d
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
thirdparty_module(SndFile
  URL https://github.com/libsndfile/libsndfile/archive/refs/tags/1.1.0.tar.gz
  URL_HASH SHA512=5e530c33165a2d2be1c22d3a4bd96f0f1817dded3a45d24bad0e3f2c7908ccc1f19327a91d5040c3ea4d591845876019180747a125bf2a6f8bd49a6f67eadacd
)
thirdparty_module(spdlog
  URL https://github.com/gabime/spdlog/archive/refs/tags/v1.10.0.zip
  URL_HASH SHA512=9f1c778482446f52fb6e35f752226715412011f608bdcbfc87be5ae4a246d6733179a910fce09c2609e4dc1ba50664a6b0c3421749a7a12d8648dcf2b61c0b99
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
  nlohmann_json Fabulist
  glfw3
  glm
  GSL
  GTest
  Opus Ogg FLAC Vorbis SndFile OpenAL
  ZLIB PNG
  spdlog
  stduuid
  TBB
  VulkanMemoryAllocator)
  message(STATUS "Fetching ${module}...")
  add_subdirectory(${module})
endforeach()
