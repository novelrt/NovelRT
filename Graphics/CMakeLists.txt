include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Graphics
  DEPENDS
    NovelRT::Graphics::Core

  OPTIONAL_DEPENDS
    NovelRT::Graphics::Vulkan)

add_subdirectory(Core)

find_package(Vulkan "1.2" OPTIONAL_COMPONENTS MoltenVK)
if(APPLE AND Vulkan_FOUND AND Vulkan_MoltenVK_FOUND)
  add_subdirectory(Vulkan)
elseif(Vulkan_FOUND)
  add_subdirectory(Vulkan)
endif()
