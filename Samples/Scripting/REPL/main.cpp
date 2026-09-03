// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/FileNotFoundException.hpp>
#include <NovelRT/Exceptions/InvalidOperationException.hpp>

#include <NovelRT/Scripting/Cues/CompoundCue.hpp>
#include <NovelRT/Scripting/Cues/PlaySoundEffectCue.hpp>
#include <NovelRT/Scripting/Cues/SetPoseCue.hpp>
#include <NovelRT/Scripting/DecisionTree.hpp>
#include <NovelRT/Scripting/DecisionTreeStatus.hpp>
#include <NovelRT/Scripting/ScriptManager.hpp>
#include <NovelRT/Scripting/Statuses/Branch.hpp>
#include <NovelRT/Scripting/Statuses/SpokenLine.hpp>
#include <NovelRT/Scripting/Statuses/TriggerCue.hpp>

#include <NovelRT/Utilities/Paths.hpp>

#include <algorithm>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <vector>

using namespace NovelRT::Scripting;

std::vector<uint8_t> LoadData(std::filesystem::path filePath)
{
    std::ifstream file(filePath.string(), std::ios::ate | std::ios::binary);

    if (!file.is_open())
    {
        throw NovelRT::Exceptions::FileNotFoundException(filePath.string());
    }

    auto size = static_cast<std::streamoff>(file.tellg());
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> data(static_cast<size_t>(size));
    file.read(reinterpret_cast<char*>(data.data()), static_cast<std::streamsize>(size));
    file.close();

    return data;
}

void LogCue(const NovelRT::Scripting::DecisionTreeCue* cue, size_t depth = 0)
{
    std::string indent(depth, ' ');
    if (const auto* compound = dynamic_cast<const NovelRT::Scripting::Cues::CompoundCue*>(cue))
    {
        std::cout << indent << "- Compound cue:\n";
        for (const auto* member : compound->children())
        {
            LogCue(member, depth + 2);
        }
    }
    else if (const auto* sfx = dynamic_cast<const NovelRT::Scripting::Cues::PlaySoundEffectCue*>(cue))
    {
        std::cout << indent << "- SFX: " << sfx->GetSound() << " (" << sfx->GetPitch() << "x)\n";
    }
    else if (const auto* pose = dynamic_cast<const NovelRT::Scripting::Cues::SetPoseCue*>(cue))
    {
        std::cout << indent << "- " << pose->GetCharacter() << " to pose " << pose->GetPose() << '\n';
    }
}

int main()
{
    std::shared_ptr<ScriptManager> manager = std::make_shared<ScriptManager>();

    auto path = NovelRT::Utilities::GetExecutableDirPath() / "Resources" / "sample.lua";
    std::vector<uint8_t> data = LoadData(path);
    std::cout << "Read " << data.size() << " bytes\n";
    auto tree = manager->LoadDecisionTree(data, path.lexically_proximate(NovelRT::Utilities::GetExecutableDirPath()).string());
    std::cout << "Loaded decision tree.\n";

    auto state = tree->Begin();
    while (state != nullptr)
    {
        if (auto* spokenLine = dynamic_cast<NovelRT::Scripting::Statuses::SpokenLine*>(state.get()))
        {
            std::cout << spokenLine->GetSpeaker() << ": " << spokenLine->GetText();
            std::cin.get();
            state = spokenLine->Continue();
        }
        else if (auto* branch = dynamic_cast<NovelRT::Scripting::Statuses::Branch*>(state.get()))
        {
            std::cout << branch->GetPrompt() << '\n';
            std::for_each(branch->GetOptions().begin(), branch->GetOptions().end(),
                          [n = 0](auto& it) mutable { std::cout << ++n << ". " << it << '\n'; });

            std::cout << "> ";
            size_t index;
            std::cin >> index;
            std::cin.get();

            state = branch->Continue(index - 1);
        }
        else if (auto* cue = dynamic_cast<NovelRT::Scripting::Statuses::TriggerCue*>(state.get()))
        {
            LogCue(cue->GetCue());
            state = cue->Continue();
        }
        else
        {
            throw NovelRT::Exceptions::InvalidOperationException(
                std::format("Unknown status result {}", typeid(state.get()).name()));
        }
    }

    return 0;
}
