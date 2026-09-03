#include <NovelRT/Scripting/Cues/CompoundCue.hpp>

#include <algorithm>

NovelRT::Scripting::Cues::CompoundCue::CompoundCue(std::vector<std::unique_ptr<DecisionTreeCue>>&& cues)
    : _cues(std::move(cues))
{
}

auto NovelRT::Scripting::Cues::CompoundCue::Clone() const -> std::unique_ptr<DecisionTreeCue>
{
    std::vector<std::unique_ptr<DecisionTreeCue>> values(_cues.size());

    std::transform(_cues.begin(), _cues.end(), values.begin(), [](const auto& it)
    {
        return it->Clone();
    });

    return std::make_unique<CompoundCue>(std::move(values));
}
