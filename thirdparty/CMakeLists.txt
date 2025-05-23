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
  URL https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip
  URL_HASH SHA512=03de56a0599275ff57759ca19e8f69176058252b5e9976193cc3d9bb7b7b78b6a8dac6ed91de483d03c1b4807d21e1302e5e47c2f0c21e63becb4aba9d5affdc
)
thirdparty_module(glm
  URL https://github.com/g-truc/glm/archive/2d4c4b4dd31fde06cfffad7915c2b3006402322f.zip
  URL_HASH SHA512=770cb1ab820f8b32e6abc650c254364ae9bf820fe278ad0b082ee4aadcaf084d66da700ee6d18202fc99fe360fc8756ed837e3d9c71dba9ebd6f502bd8011561
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
thirdparty_module(imgui
  URL https://github.com/ocornut/imgui/archive/refs/tags/v1.91.9b.zip
  URL_HASH SHA512=d99bc25165f814dda952e0f4a4cd6c028c1217c1b482e089c3ab04fa460d6fb1062beff7561c8d75998be63c1b514fa25b2ac514881f240d5e62f67f1b097b5e
)
thirdparty_module(nlohmann_json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
  URL_HASH SHA512=1aa94cdc3378a1fe0e3048ee73293e34bfa5ed9b46c6db0993e58e289ef818f7b7a472c0dc9c920114312e2e3ae1ff346ca797407ff48143744592adfd0a41ad
  OVERRIDE_FIND_PACKAGE
)
thirdparty_module(Ogg
  URL https://github.com/xiph/ogg/archive/fa80aae9d50096160f2b56ada35527d7aee3f746.zip
  URL_HASH SHA512=48eb2dd03c6368ba6067bcb1339023e258edaad2669de7095fc93ab6b0ae5f10a19c0727695aca2c9091ebe2f2e18585aea9989f71f0d356152dd1fc1f715971
  OVERRIDE_FIND_PACKAGE
)
thirdparty_module(OpenAL
  URL https://github.com/kcat/openal-soft/archive/ef44737658313cc0a6394eed7878ad28d36fdca5.zip
  URL_HASH SHA512=66b1e5a373ab6f5414220b7b22c46a0e0eba7d83e004088be75bb5ec808e4d4e2152fc14989ba182475c4d1d020332bbd9b3deb1b26f8506d40112f995e02206
  OVERRIDE_FIND_PACKAGE
)
thirdparty_module(Opus
  URL https://github.com/xiph/opus/archive/refs/tags/v1.5.2.zip
  URL_HASH SHA512=67b6830903a82017825848384e5b2e3b70b834507d818f0dfa06a4a48766f38151927e875745e2f254b3aad4222deea3549c1e6c981427f8284b2a28a9c036cd
  OVERRIDE_FIND_PACKAGE
)
thirdparty_module(PNG
  URL https://github.com/glennrp/libpng/archive/refs/tags/v1.6.35.zip
  URL_HASH SHA512=65df0c2befa06d0b9ec0c6395a73987fb071754610d328b94ce01a6b8f7161c71ce97ddf0e0a8e28c2e50019a103368c4b4f0b63bd8cd75e168b32f940922d96
  OVERRIDE_FIND_PACKAGE
)

thirdparty_module(samplerate
  URL https://github.com/libsndfile/libsamplerate/archive/15c392d47e71b9395a759544b3818a1235fe1a1d.zip
  URL_HASH SHA512=496600418b2058b7fa7611208e7c5eb8996b294bf96ce7d3e9107a99803583e593518b0d7a29534ffb4f6d4201efe56aff25386e7262dd211471054641f573e9
)
thirdparty_module(SndFile
  URL https://github.com/novelrt/libsndfile/archive/f76d63813c810c2ed09bdb3821bb807498a7558e.zip
  URL_HASH SHA512=7e650af94068277246e4ccaf3b5dc20d0f93d2a2e0ecdf0f24f0be79196f879c21ec692ad48d39454f22dd01d9a4864d21458daa8d7b8f5ea4568c9551b345c1
)
thirdparty_module(spdlog
  URL https://github.com/gabime/spdlog/archive/refs/tags/v1.15.1.zip
  URL_HASH SHA512=67b82452e046cb8d77082edeaf163460f2b171b3555c7feb32f5e0296921de2f3ebf279224509a8f0821947b274dd0b7f40ef01f1b8f612c80ba93cbc3e156cc
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
  URL https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator/archive/refs/tags/v3.3.0.zip
  URL_HASH SHA512=1d3aa42a788e40666e7078f0141d02728a3a6696ffe65de6da4638f3d06a28ea6673ac45f4aa9cfdb283831f8888f61f53b292b71e3292d8c43ba634d0f3274b
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
  imgui
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
