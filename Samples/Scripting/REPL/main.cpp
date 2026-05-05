// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/FileNotFoundException.hpp>

//#include <NovelRT/ResourceManagement/Desktop/DesktopResourceLoader.hpp>

#include <NovelRT/Scripting/ScriptManager.hpp>
#include <NovelRT/Scripting/DecisionTree.hpp>
#include <NovelRT/Scripting/DecisionTreeStatus.hpp>
#include <NovelRT/Scripting/Statuses/SpokenLine.hpp>

#include <NovelRT/Utilities/Paths.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

//using namespace NovelRT::ResourceManagement::Desktop;
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
    //std::shared_ptr<DesktopResourceLoader> resourceLoader = std::make_shared<DesktopResourceLoader>();
    std::shared_ptr<ScriptManager> manager = std::make_shared<ScriptManager>();

    std::vector<uint8_t> data = LoadData(NovelRT::Utilities::GetExecutableDirPath() / "Resources" / "sample.lua");
    std::cout << "Read " << data.size() << " bytes\n";
    auto tree = manager->LoadDecisionTree(data);
    std::cout << "Loaded decision tree.\n";

    auto state = tree->Begin();
    while (state != nullptr)
    {
        if (auto* spokenLine = static_cast<NovelRT::Scripting::Statuses::SpokenLine*>(state.get()))
        {
            std::cout << spokenLine->GetSpeaker() << ": " << spokenLine->GetText();
            std::cin.get();
            state = spokenLine->Continue();
        }
    }

    return 0;
}
