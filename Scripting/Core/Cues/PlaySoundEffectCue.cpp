#include <NovelRT/Scripting/Cues/PlaySoundEffectCue.hpp>

NovelRT::Scripting::Cues::PlaySoundEffectCue::PlaySoundEffectCue(std::string sound, double pitch)
    : _sound(sound), _pitch(pitch)
{
}

const std::string NovelRT::Scripting::Cues::PlaySoundEffectCue::GetSound() const
{
    return _sound;
}

double NovelRT::Scripting::Cues::PlaySoundEffectCue::GetPitch() const
{
    return _pitch;
}

auto NovelRT::Scripting::Cues::PlaySoundEffectCue::Clone() const -> std::unique_ptr<DecisionTreeCue>
{
    return std::make_unique<PlaySoundEffectCue>(_sound, _pitch);
}
