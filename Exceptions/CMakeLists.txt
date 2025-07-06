include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Exceptions
  SOURCES
    PRIVATE
      empty.cpp

  HEADERS
    PUBLIC
      include/NovelRT/Exceptions/DuplicateKeyException.hpp
      include/NovelRT/Exceptions/FileNotFoundException.hpp
      include/NovelRT/Exceptions/InitialisationFailureException.hpp
      include/NovelRT/Exceptions/InvalidOperationException.hpp
      include/NovelRT/Exceptions/KeyNotFoundException.hpp
      include/NovelRT/Exceptions/NotSupportedException.hpp
      include/NovelRT/Exceptions/NullPointerException.hpp
      include/NovelRT/Exceptions/OutOfMemoryException.hpp
      include/NovelRT/Exceptions/TimeoutException.hpp)
