include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Scripting::Core
  DEPENDS
    NovelRT::Exceptions
    lua::lua

  SOURCES
    PRIVATE
      Bindings/Init.cpp
      Bindings/Fabulist.cpp
      Bindings/Fabulist/Choice.cpp
      Bindings/Fabulist/Speaker.cpp
      Statuses/Branch.cpp
      Statuses/SpokenLine.cpp
      Bindings.hpp
      DecisionTree.cpp
      DecisionTreeStatus.cpp
      ScriptManager.cpp

  HEADERS
    PUBLIC
      include/NovelRT/Scripting/Statuses/Branch.hpp
      include/NovelRT/Scripting/Statuses/SpokenLine.hpp
      include/NovelRT/Scripting/ScriptManager.hpp
      include/NovelRT/Scripting/DecisionTree.hpp
      include/NovelRT/Scripting/DecisionTreeStatus.hpp
)
