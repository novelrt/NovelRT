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
)

set_target_properties(NovelRT-Core
  PROPERTIES
    EXPORT_NAME Core
    POSITION_INDEPENDENT_CODE ON
)

install(
  TARGETS NovelRT-Core
  EXPORT NovelRTConfig
  LIBRARY DESTINATION lib
  FILE_SET public_headers
)
