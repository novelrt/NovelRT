cmake_minimum_required(VERSION 3.13)
project(nanovg)

set(LIB_SOURCE nanovg.c)
set(LIB_HEADERS nanovg.h nanovg_gl.h nanovg_gl_utils.h stb_image.h stb_truetype.h fontstash.h)
add_library(nanovg STATIC ${LIB_SOURCE} ${LIB_HEADERS})
