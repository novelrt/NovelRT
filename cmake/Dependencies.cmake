include(FetchContent)
include(functions/NovelRTDeps_Options)
include(functions/NovelRTDeps_Populate)

#Make an exception for Fabulist as we want it static all the time
set(NOVELRT_STATIC_FABULIST ON)
NovelRTDeps_Options("Fabulist" NOVELRT_SYSTEM_FABULIST ON NOVELRT_STATIC_FABULIST NOVELRT_SHARED_FABULIST)
add_subdirectory(internal/Fabulist)


#Freetype Dependencies - maintaining a specific order on purpose to prevent build issues.
NovelRTDeps_Options("zlib" NOVELRT_SYSTEM_ZLIB ON NOVELRT_STATIC_ZLIB NOVELRT_SHARED_ZLIB)
if(NOT NOVELRT_SYSTEM_ZLIB)
  add_subdirectory(internal/zlib-ng)
endif()

NovelRTDeps_Options("libpng" NOVELRT_SYSTEM_PNG ON NOVELRT_STATIC_PNG NOVELRT_SHARED_PNG)
if(NOVELRT_SYSTEM_PNG)
  find_package(PNG REQUIRED)
else()
  add_subdirectory(internal/libpng)
endif()

NovelRTDeps_Options("freetype" NOVELRT_SYSTEM_FREETYPE ON NOVELRT_STATIC_FREETYPE NOVELRT_SHARED FREETYPE)
if(NOT NOVELRT_SYSTEM_FREETYPE)
  add_subdirectory(internal/freetype)
endif()

# #Audio Dependencies - These must maintain a specific order as well.
NovelRTDeps_Options("Ogg" NOVELRT_SYSTEM_OGG ON NOVELRT_STATIC_OGG NOVELRT_SHARED_OGG)
if(NOT NOVELRT_SYSTEM_OGG)
  add_subdirectory(internal/ogg)
endif()

NovelRTDeps_Options("Opus" NOVELRT_SYSTEM_OPUS ON NOVELRT_STATIC_OPUS NOVELRT_SHARED_OPUS)
if(NOT NOVELRT_SYSTEM_OPUS)
  add_subdirectory(internal/opus)
endif()

NovelRTDeps_Options("Vorbis" NOVELRT_SYSTEM_VORBIS ON NOVELRT_STATIC_VORBIS NOVELRT_SHARED_VORBIS)
if(NOT NOVELRT_SYSTEM_VORBIS)
  add_subdirectory(internal/vorbis)
endif()

NovelRTDeps_Options("FLAC" NOVELRT_SYSTEM_FLAC ON NOVELRT_STATIC_FLAC NOVELRT_SHARED_FLAC)
if(NOT NOVELRT_SYSTEM_FLAC)
  add_subdirectory(internal/flac)
endif()

NovelRTDeps_Options("Sndfile" NOVELRT_SYSTEM_SNDFILE ON NOVELRT_STATIC_SNDFILE NOVELRT_SHARED_SNDFILE)
if(NOT NOVELRT_SYSTEM_SNDFILE)
  add_subdirectory(internal/libsndfile)
endif()

NovelRTDeps_Options("OpenAL" NOVELRT_SYSTEM_OPENAL ON NOVELRT_STATIC_OPENAL NOVELRT_SHARED_OPENAL)
if(NOT NOVELRT_SYSTEM_OPENAL)
  add_subdirectory(internal/openal)
endif()

# Graphics dependencies
NovelRTDeps_Options("Vulkan" NOVELRT_SYSTEM_VULKAN ON NOVELRT_STATIC_VULKAN NOVELRT_SHARED_VULKAN)
if(NOVELRT_SYSTEM_VULKAN)
  if(APPLE)
    find_package(Vulkan ${NOVELRT_VULKAN_VERSION} COMPONENTS MoltenVK REQUIRED)
  else()
    find_package(Vulkan ${NOVELRT_VULKAN_VERSION} REQUIRED)
  endif()
else()
  add_subdirectory(internal/vulkan/vulkan-headers)
  add_subdirectory(internal/vulkan/vulkan-loader)
  if(APPLE)
    add_subdirectory(internal/moltenvk)
  endif()
endif()

#Other dependencies
NovelRTDeps_Options("GSL" NOVELRT_SYSTEM_GSL ON NOVELRT_STATIC_GSL NOVELRT_SHARED_GSL)
if(NOVELRT_SYSTEM_GSL)
  find_package(GSL REQUIRED)
else()
  add_subdirectory(internal/GSL)
endif()

if(NOVELRT_BUILD_TESTS)
  NovelRTDeps_Options("GoogleTest" NOVELRT_SYSTEM_GTEST ON NOVELRT_STATIC_GTEST NOVELRT_SHARED_GTEST)
  set(NOVELRT_SHARED_GTEST ${NOVELRT_BUILD_SHARED_LIBS})
  add_subdirectory(internal/gtest)
endif()

# #Add libraries that are not typically system libraries
set(NOVELRT_SHARED_GLFW ${NOVELRT_BUILD_SHARED_LIBS})
NovelRTDeps_Options("glfw" NOVELRT_SYSTEM_GLFW ON NOVELRT_STATIC_GLFW NOVELRT_SHARED_GLFW)
add_subdirectory(internal/glfw)

set(NOVELRT_SHARED_GLM ${NOVELRT_BUILD_SHARED_LIBS})
NovelRTDeps_Options("GLM" NOVELRT_SYSTEM_GLM ON NOVELRT_STATIC_GLM NOVELRT_SHARED_GLM)
add_subdirectory(internal/glm)

set(NOVELRT_SHARED_GLFW ${NOVELRT_BUILD_SHARED_LIBS})
NovelRTDeps_Options("jsoncons" NOVELRT_SYSTEM_JSONCONS ON NOVELRT_STATIC_JSONCONS NOVELRT_SHARED_JSONCONS)
add_subdirectory(internal/jsoncons)

set(NOVELRT_SHARED_TBB ${NOVELRT_BUILD_SHARED_LIBS})
NovelRTDeps_Options("oneTBB" NOVELRT_SYSTEM_TBB ON NOVELRT_STATIC_TBB NOVELRT_SHARED_TBB)
add_subdirectory(internal/oneTBB)

set(NOVELRT_SHARED_SPDLOG ${NOVELRT_BUILD_SHARED_LIBS})
NovelRTDeps_Options("spdlog" NOVELRT_SYSTEM_SPDLOG ON NOVELRT_STATIC_SPDLOG NOVELRT_SHARED_SPDLOG)
add_subdirectory(internal/spdlog)

set(NOVELRT_SHARED_STDUUID ${NOVELRT_BUILD_SHARED_LIBS})
NovelRTDeps_Options("stduuid" NOVELRT_SYSTEM_STDUUID ON NOVELRT_STATIC_STDUUID NOVELRT_SHARED_STDUUID)
add_subdirectory(internal/stduuid)
