include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Ecs::Core
  DEPENDS
    NovelRT::Maths
    NovelRT::Timing
    NovelRT::Utilities

  SOURCES
    PRIVATE
      Catalogue.cpp
      ComponentBufferMemoryContainer.cpp
      ComponentCache.cpp
      EcsUtils.cpp
      EntityCache.cpp
      EntityGraphView.cpp
      LinkedEntityListView.cpp
      SparseSetMemoryContainer.cpp
      SystemScheduler.cpp
      UnsafeComponentView.cpp

  HEADERS
    PUBLIC
      include/NovelRT/Ecs/Catalogue.hpp
      include/NovelRT/Ecs/ComponentBuffer.hpp
      include/NovelRT/Ecs/ComponentBufferMemoryContainer.hpp
      include/NovelRT/Ecs/ComponentCache.hpp
      include/NovelRT/Ecs/ComponentView.hpp
      include/NovelRT/Ecs/DefaultComponentTypes.hpp
      include/NovelRT/Ecs/EcsUtils.hpp
      include/NovelRT/Ecs/EntityCache.hpp
      include/NovelRT/Ecs/EntityGraphView.hpp
      include/NovelRT/Ecs/IEcsSystem.hpp
      include/NovelRT/Ecs/LinkedEntityListView.hpp
      include/NovelRT/Ecs/SparseSet.hpp
      include/NovelRT/Ecs/SparseSetMemoryContainer.hpp
      include/NovelRT/Ecs/SystemScheduler.hpp
      include/NovelRT/Ecs/UnsafeComponentView.hpp
)
