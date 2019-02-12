cmake_minimum_required(VERSION 3.13)
project(lua VERSION 5.3 LANGUAGES C)

set(LIB_SOURCE lapi.c lauxlib.c lbaselib.c
        lcode.c lcorolib.c lctype.c ldblib.c
        ldebug.c ldo.c ldump.c lfunc.c lgc.c
        linit.c liolib.c llex.c lmathlib.c lmem.c
        loadlib.c lobject.c lopcodes.c loslib.c
        lparser.c lstate.c lstring.c lstrlib.c
        ltable.c ltablib.c ltm.c lundump.c
        lutf8lib.c lvm.c lzio.c)

set(LIB_HEADERS lapi.h lauxlib.h lcode.h lctype.h ldebug.h
        ldo.h lfunc.h lgc.h llex.h llimits.h
        lmem.h lobject.h lopcodes.h lparser.h
        lprefix.h lstate.h lstring.h ltable.h ltm.h
        lua.h luaconf.h lualib.h lundump.h lvm.h
        lzio.h lua.h)
add_library(liblua STATIC ${LIB_SOURCE} ${LIB_HEADERS})
set_property(TARGET liblua PROPERTY OUTPUT_NAME lua)

add_executable(lua-bin lua.c)
set_property(TARGET lua-bin PROPERTY OUTPUT_NAME lua)
target_link_libraries(lua-bin liblua)

enable_testing()
add_test(NAME version COMMAND lua-bin -v)

install(TARGETS liblua lua-bin
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(FILES lua.h luaconf.h lualib.h lauxlib.h lua.h
        DESTINATION include)

set(CPACK_PACKAGE_VERSION "${lua_VERSION}")
set(CPACK_GENERATOR 7Z)
include(CPack)
