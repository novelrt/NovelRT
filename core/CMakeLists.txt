add_library(NovelRT-Core OBJECT
  Atom.cpp
)

target_sources(NovelRT-Core
  PUBLIC
    FILE_SET public_headers
    TYPE HEADERS
    BASE_DIRS include
    FILES
      include/NovelRT/Core/Atom.hpp
      include/NovelRT/Core/Exceptions/CharacterNotFoundException.hpp
      include/NovelRT/Core/Exceptions/CompilationErrorException.hpp
      include/NovelRT/Core/Exceptions/DuplicateKeyException.hpp
      include/NovelRT/Core/Exceptions/FileNotFoundException.hpp
      include/NovelRT/Core/Exceptions/FunctionNotFoundException.hpp
      include/NovelRT/Core/Exceptions/InitialisationFailureException.hpp
      include/NovelRT/Core/Exceptions/InvalidOperationException.hpp
      include/NovelRT/Core/Exceptions/IOException.hpp
      include/NovelRT/Core/Exceptions/KeyNotFoundException.hpp
      include/NovelRT/Core/Exceptions/NotInitialisedException.hpp
      include/NovelRT/Core/Exceptions/NotSupportedException.hpp
      include/NovelRT/Core/Exceptions/NullPointerException.hpp
      include/NovelRT/Core/Exceptions/OpenGLLinkageFailureException.hpp
      include/NovelRT/Core/Exceptions/OutOfMemoryException.hpp
      include/NovelRT/Core/Exceptions/RuntimeNotFoundException.hpp
      include/NovelRT/Core/Exceptions/TimeoutException.hpp
)

set_target_properties(NovelRT-Core
  PROPERTIES
    EXPORT_NAME Core
    POSITION_INDEPENDENT_CODE ON
)

target_compile_features(NovelRT-Core
  PUBLIC
    cxx_std_17
)

target_compile_options(NovelRT-Core
  PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-Wall>
    $<$<CXX_COMPILER_ID:GNU>:-Wabi>
    $<$<CXX_COMPILER_ID:GNU>:-Werror>
    $<$<CXX_COMPILER_ID:GNU>:-Wextra>
    $<$<CXX_COMPILER_ID:GNU>:-Wpedantic>
    $<$<CXX_COMPILER_ID:GNU>:-pedantic-errors>

    $<$<CXX_COMPILER_ID:Clang>:-Wall>
    $<$<CXX_COMPILER_ID:Clang>:-Werror>
    $<$<CXX_COMPILER_ID:Clang>:-Wextra>
    $<$<CXX_COMPILER_ID:Clang>:-Wpedantic>
    $<$<CXX_COMPILER_ID:Clang>:-pedantic-errors>

    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<CXX_COMPILER_ID:MSVC>:/WX>
    $<$<CXX_COMPILER_ID:MSVC>:/permissive->
)

install(
  TARGETS NovelRT-Core
  EXPORT NovelRTConfig
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  FILE_SET public_headers DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
