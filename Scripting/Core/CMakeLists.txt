include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Scripting::Core
  DEPENDS
    NovelRT::Exceptions
    NovelRT::Maths
    lua::lua

  SOURCES
    Bindings/Bindings.hpp

    Bindings/Fabulist.cpp
    Bindings/Actions/Choice.cpp
    Bindings/Actions/Cue.cpp
    Bindings/Actions/Speaker.cpp
    Bindings/Cues/Compound.cpp
    Bindings/Cues/SetPoseCue.cpp
    Bindings/Cues/SoundEffectCue.cpp
    Bindings/Util.cpp

    Cues/CompoundCue.cpp
    Cues/PlaySoundEffectCue.cpp
    Cues/SetPoseCue.cpp

    Statuses/Branch.cpp
    Statuses/SpokenLine.cpp
    Statuses/TriggerCue.cpp

    DecisionTree.cpp
    DecisionTreeStatus.cpp
    ScriptManager.cpp

  HEADERS
    include/NovelRT/Scripting/Cues/CompoundCue.hpp
    include/NovelRT/Scripting/Cues/PlaySoundEffectCue.hpp

    include/NovelRT/Scripting/Statuses/TriggerCue.hpp
    include/NovelRT/Scripting/Statuses/Branch.hpp
    include/NovelRT/Scripting/Statuses/SpokenLine.hpp

    include/NovelRT/Scripting/ScriptManager.hpp
    include/NovelRT/Scripting/DecisionTree.hpp
    include/NovelRT/Scripting/DecisionTreeCue.hpp
    include/NovelRT/Scripting/DecisionTreeStatus.hpp
)
