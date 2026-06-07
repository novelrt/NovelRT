// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/FileNotFoundException.hpp>
#include <NovelRT/Exceptions/InvalidOperationException.hpp>

#include <NovelRT/Scripting/DecisionTree.hpp>
#include <NovelRT/Scripting/DecisionTreeStatus.hpp>
#include <NovelRT/Scripting/ScriptManager.hpp>
#include <NovelRT/Scripting/Statuses/Branch.hpp>
#include <NovelRT/Scripting/Statuses/SpokenLine.hpp>

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

    auto filesize = file.tellg();
    std::vector<uint8_t> data(filesize);
    file.seekg(0);
    file.read(reinterpret_cast<char*>(data.data()), filesize);
    file.close();

    return data;
}

int main()
{
    std::shared_ptr<ScriptManager> manager = std::make_shared<ScriptManager>();

    std::vector<uint8_t> data = LoadData(NovelRT::Utilities::GetExecutableDirPath() / "Resources" / "sample.lua");
    std::cout << "Read " << data.size() << " bytes\n";
    auto tree = manager->LoadDecisionTree(data);
    std::cout << "Loaded decision tree.\n";

    auto state = tree->Begin();
    while (state != nullptr)
    {
        if (auto* spokenLine = dynamic_cast<NovelRT::Scripting::Statuses::SpokenLine*>(state.get()))
        {
            if (spokenLine->GetPose().has_value())
            {
                auto pose = spokenLine->GetPose().value();
                std::cout << spokenLine->GetSpeaker() << " [" << pose.Name << " - " << pose.Sprite << "]: " << spokenLine->GetText();
            }
            else
            {
                std::cout << spokenLine->GetSpeaker() << ": " << spokenLine->GetText();
            }
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
        else
        {
            throw NovelRT::Exceptions::InvalidOperationException(
                std::format("Unknown status result {}", typeid(state.get()).name()));
        }
    }

    return 0;
}
