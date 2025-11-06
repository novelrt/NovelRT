include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Exceptions
  SOURCES
    PUBLIC
      Public/Exceptions.cpp
      Public/DuplicateKeyException.cpp
      Public/FileNotFoundException.cpp
      Public/InitialisationFailureException.cpp
      Public/InvalidOperationException.cpp
      Public/KeyNotFoundException.cpp
      Public/NotSupportedException.cpp
      Public/NullPointerException.cpp
      Public/OutOfMemoryException.cpp
      Public/TimeoutException.cpp)
