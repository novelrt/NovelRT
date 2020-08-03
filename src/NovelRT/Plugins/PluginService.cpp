// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>
#include "LoadLibHelper.h"
#include "jsoncpp/json/json.h"

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

  NRTPluginPointer PluginService::loadPlugin(const std::filesystem::path& location) {
    std::filesystem::path theRealLocation(location);

    //TODO: This is dumb. Call the ambulance.
#if defined (__linux__)
    theRealLocation.replace_filename("lib" + theRealLocation.filename().string());
#endif
    theRealLocation.replace_extension(getLibraryExtension());
    
    return loadPluginLibrary((Utilities::Misc::getExecutableDirPath() / "Resources" / "Plugins" / theRealLocation).string());
  }

  PluginService::PluginService() noexcept {}


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

  std::shared_ptr<Graphics::IRenderingService> PluginService::createRenderingService(const PluginInfo& info) noexcept {
    NRTPluginPointer lib = loadPlugin(info.location());
    _loadedPlugins.emplace(info.pluginId(), lib);
    auto creator = getSymbolForFunctionPtr<NRTRenderingServiceFactoryCreatorPtr>(lib, "createRenderingServiceFactory");
    return creator()->create();
  }

  PluginService::~PluginService() {
    for(auto& ptr : _loadedPlugins) {
      freePluginLibrary(ptr.second);
    }
  }
}
