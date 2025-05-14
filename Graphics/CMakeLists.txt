add_subdirectory(Core)
add_subdirectory(Vulkan)

file(GENERATE OUTPUT empty.cpp CONTENT "")
add_library(NovelRT-Graphics STATIC empty.cpp)

set_target_properties(NovelRT-Graphics
  PROPERTIES
    EXPORT_NAME Graphics
)

target_link_libraries(NovelRT-Graphics
  PUBLIC
    NovelRT-Graphics-Core
    NovelRT-Graphics-Vulkan
)

install(
  TARGETS NovelRT-Graphics
  EXPORT NovelRTConfig
  LIBRARY DESTINATION lib
)
