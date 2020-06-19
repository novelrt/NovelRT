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

  bool PluginService::tryGetPluginInfo(const std::filesystem::path& path, PluginInfo& info, bool isRelative) const {
    std::filesystem::path finalPath = path;

    if (isRelative) {
      finalPath = Utilities::Misc::getExecutableDirPath() / path;
    }

    if (!std::filesystem::exists(finalPath)) {
      return false;
    }

    info = getPluginInfo(finalPath);

    return true;
  }
}
