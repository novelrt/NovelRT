#include <NovelRT/Scripting/Cues/SetPoseCue.hpp>

NovelRT::Scripting::Cues::SetPoseCue::SetPoseCue(std::string character, std::string pose)
    : _character(character), _pose(pose)
{
}

const std::string NovelRT::Scripting::Cues::SetPoseCue::GetCharacter() const
{
    return _character;
}

const std::string NovelRT::Scripting::Cues::SetPoseCue::GetPose() const
{
    return _pose;
}

auto NovelRT::Scripting::Cues::SetPoseCue::Clone() const -> std::unique_ptr<DecisionTreeCue>
{
    return std::make_unique<SetPoseCue>(_character, _pose);
}
