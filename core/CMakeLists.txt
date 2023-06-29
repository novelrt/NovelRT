add_library(NovelRT-Core STATIC
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

install(
  TARGETS NovelRT-Core
  EXPORT NovelRTConfig
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  FILE_SET public_headers DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
