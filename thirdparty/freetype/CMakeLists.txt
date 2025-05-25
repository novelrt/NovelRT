include(FetchContent)

set(FT_DISABLE_BZIP2 TRUE CACHE BOOL "Disable BZip2 dependency" FORCE)
set(FT_DISABLE_HARFBUZZ TRUE CACHE BOOL "Disable Harfbuzz dependency" FORCE)
set(FT_DISABLE_BROTLI TRUE CACHE BOOL "Disable Brotli dependency" FORCE)
FetchContent_MakeAvailable(freetype)
