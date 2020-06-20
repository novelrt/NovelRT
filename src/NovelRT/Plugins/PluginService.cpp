// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Plugins {
  PluginInfo PluginService::getPluginInfo(const std::filesystem::path& path) const {
    Json::Value root;
    std::ifstream streamReader;
    streamReader.open(path);
    Json::CharReaderBuilder builder;
    builder["collectComments"] = true;
    Json::String errs;

    if (!parseFromStream(builder, streamReader, &root, &errs)) {
      std::cout << errs << std::endl;
      throw std::runtime_error("Unable to parse plugin config file specified at " + path.string() + "!");
    }
    return PluginInfo(Atom::getNextPluginId(), root["name"].asString(), static_cast<PluginKind>(root["kind"].as<uint32_t>()), std::filesystem::path(root["location"].asString()), root["engineVersion"].asString(), root["pluginInfoVersion"].asString());
  }

  bool PluginService::tryGetPluginInfo(const std::filesystem::path& location, PluginInfo& info, bool isRelative) const {
    std::filesystem::path finalLocation = location;

    if (isRelative) {
      finalLocation = Utilities::Misc::getExecutableDirPath() / "Resources" / "Plugins" / location;
    }

    if (!std::filesystem::exists(finalLocation)) {
      return false;
    }

    info = getPluginInfo(finalLocation);

    return true;
  }

  std::vector<PluginInfo> PluginService::getAllAvailablePluginInfo(const std::filesystem::path& location, bool isRelative, bool shouldRecurse) const {
    std::filesystem::path finalLocation = location;

    std::vector<PluginInfo> plugins;

    if (isRelative) {
      finalLocation = Utilities::Misc::getExecutableDirPath() / "Resources" / location;
    }

    if (shouldRecurse) {
      std::filesystem::recursive_directory_iterator it = std::filesystem::recursive_directory_iterator(finalLocation);
      for (const auto& file : it) {
        if (file.path().string().find(".json") == std::string::npos) {
          continue;
        }

        plugins.emplace_back(getPluginInfo(file.path()));
      }
    }
    else {
      std::filesystem::directory_iterator it = std::filesystem::directory_iterator(finalLocation);
      for (const auto& file : it) {
        if (file.path().string().find(".json") == std::string::npos) {
          continue;
        }

        plugins.emplace_back(getPluginInfo(file.path()));
      }
    }

    return plugins;
  }
}
